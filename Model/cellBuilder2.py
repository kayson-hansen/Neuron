from neuron import h
from neuron.units import ms, mV
import matplotlib.pyplot as plt
import numpy as np

h.load_file('stdrun.hoc')
h.cvode_active(True)

soma = h.Section(name='soma')
prim = []
for i in range(0, 6):
    prim.append(h.Section(name='prim{0}'.format(i)))
sec = []
for i in range(0, 4):
    sec.append(h.Section(name='sec{0}'.format(i)))
tert = []
for i in range(0, 8):
    tert.append(h.Section(name='tert{0}'.format(i)))

allSections = [soma] + prim + sec + tert
dendrites = prim + sec + tert
proximal = [soma, prim[0], prim[1], prim[2], prim[4]]
primary1 = [prim[0], prim[1]]
primary2 = [prim[2], prim[4]]
primary3 = [prim[3], prim[5]]

def topol():
    prim[0].connect(soma(0))
    prim[1].connect(soma(1))
    prim[2].connect(prim[0](1))
    prim[3].connect(prim[2](1))
    prim[4].connect(prim[1](1))
    prim[5].connect(prim[4](1))
    
    for i in range(0, 2): sec[i].connect(prim[3](1))
    for i in range(2, 4): sec[i].connect(prim[5](1))
    for i in range(0, 2): tert[i].connect(sec[0](1))
    for i in range(2, 4): tert[i].connect(sec[1](1))
    for i in range(4, 6): tert[i].connect(sec[2](1))
    for i in range(6, 8): tert[i].connect(sec[3](1))

def geom(sec, tert, primary1, primary2, primary3, soma):
    for section in sec:
        section.L = 20
        section.diam = 1
    for section in tert:
        section.L = 140
        section.diam = 0.8
    for section in primary1:
        section.L = 40
        section.diam = 2.5
    for section in primary2:
        section.L = 10
        section.diam = 2
    for section in primary3:
        section.L = 30
        section.diam = 2
    soma.L = 25
    soma.diam = 25

def geom_nseg(sec, tert, primary1, primary2, primary3, soma):
    for section in sec: section.nseg = 1
    for section in tert: section.nseg = 5
    for section in primary1: section.nseg = 3
    for section in primary2: section.nseg = 1
    for section in primary3: section.nseg = 3
    soma.nseg = 3

def biophys(allSections, dendrites, proximal, soma):
    for section in allSections:
        section.Ra = 400
        section.cm = 1
        section.insert('bk')
        section.insert('cal')
        section.insert('can')
        section.insert('car')
        section.insert('pmp')
        section.insert('ih')
        section.insert('kdr')
        section.insert('naf')
        section.insert('nal')
        section.insert('nap')
        section.insert('sk')
        section.insert('lk')
        
        for seg in section:
            seg.bk.gbar = 500
            seg.cal.pbar12 = 10**(-7)
            seg.cal.pbar13 = 5 * 10**(-9)
            seg.can.pbar = 1.2 * 10**(-6)
            seg.car.pbar = 5 * 10**(-7)
            seg.pmp.kb = 200
            seg.ih.gbar = 0.5
            seg.kdr.gbar = 20
            seg.naf.gbar = 250
            seg.nal.gbar = 0.135
            seg.nap.gbar = 0.07
            seg.sk.gbar = 3
            seg.lk.g = 0.2
            seg.lk.e = -60
            
        section.cao = 2.0
        section.ek = -90
        
        
    for section in dendrites:
        section.insert('cat')
        for seg in section:
            #seg.pmp.kb = 96
            seg.cat.pbar = 10**(-7)
    
    for section in proximal:
        section.insert('ka')
        for seg in section:
            seg.ka.gbar = 24.5
            
    for seg in soma:
        seg.ka.gbar = 32
        seg.nap.gbar = 0.1
        seg.pmp.taucl = 20
        seg.pmp.kb = 45

    
topol()
geom(sec, tert, primary1, primary2, primary3, soma)
biophys(allSections, dendrites, proximal, soma)
geom_nseg(sec, tert, primary1, primary2, primary3, soma)

h.celsius = 35

# h.finitialize(-55 * mV)
# h.continuerun(50 * ms)

# record membrane potential
v = h.Vector().record(soma(0.5)._ref_v)

# record currents
inaf = h.Vector().record(soma(0.5)._ref_ina_naf)
ikdr = h.Vector().record(soma(0.5)._ref_ik_kdr)
isk = h.Vector().record(soma(0.5)._ref_ik_sk)
inal = h.Vector().record(soma(0.5)._ref_ina_nal)
ika = h.Vector().record(soma(0.5)._ref_ik_ka)
ibk = h.Vector().record(soma(0.5)._ref_ik_bk)
iih = h.Vector().record(soma(0.5)._ref_ih_ih)
ican = h.Vector().record(soma(0.5)._ref_ica_can)
icar = h.Vector().record(soma(0.5)._ref_ica_car)
ical = h.Vector().record(soma(0.5)._ref_ica_cal)

# record calcium
caDat = h.Vector().record(soma(0.5)._ref_cai)

# record time
t = h.Vector().record(h._ref_t)

# set initial conditions
h.v_init = -55 * mV
h.tstop = 5000 * ms
h.run()

# plots
plt.subplot(3, 1, 1)
plt.plot(t, v)
plt.ylabel('Vm (mV)')
axes = plt.gca()
axes.set_ylim([-80, 40])

plt.subplot(3, 1, 2)
plt.plot(t, inaf, label="inaf")
plt.plot(t, ikdr, label="ikdr")
plt.plot(t, isk, label="isk")
plt.plot(t, inal, label="inal")
plt.plot(t, ika, label="ika")
plt.plot(t, ibk, label="ibk")
plt.plot(t, iih, label="iih")
plt.plot(t, ican, label="ican")
plt.plot(t, icar, label="icar")
plt.plot(t, ical, label="ical")
plt.ylabel('Current (mA/cm2)')
axes = plt.gca()
axes.set_ylim([-0.0015, 0.0015])
plt.legend(bbox_to_anchor=(1, 0.5), prop={'size':7.8}, loc='center left', borderaxespad=0.)

plt.subplot(3, 1, 3)
plt.plot(t, caDat)
plt.ylabel('[Ca]i (mM)')
axes = plt.gca()
axes.set_ylim([0, 0.0006])

plt.show()

# writing data to file
import csv

with open('data.csv', 'w') as f:
    csv.writer(f).writerow(['t', 'v', 'inaf', 'ikdr', 'isk', 'inal', 'ika', 'ibk', 'iih', 'ican', 'icar', 'ical', 'caDat'])
    csv.writer(f).writerows(zip(t, v, inaf, ikdr, isk, inal, ika, ibk, iih, ican, icar, ical, caDat))