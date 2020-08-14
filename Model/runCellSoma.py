import sys
import matplotlib.pyplot as plt

# to prevent errors caused by accidentally importing twice
if 'neuron' not in sys.modules:
    from neuron import h, rxd, gui
    h.load_file('stdrun.hoc')

# simulation parameters
pumpTau = -25
caiInit = 5E-5
somaSize = 25
runTime = 1000

# window size and placement params
grXCoord = 600
grYCoord = 5
grWidth = 750
grHeight = 200

#cyt = rxd.Region(h.allsec(), name='cyt', nrn_region='i')
#ca = rxd.Species(cyt, name='ca', charge=2, initial=5E-5)
#caPump = rxd.Rate(ca,pumpTau,regions=cyt)   # problem is here


# build sections
soma = h.Section(name='soma')
soma.L = soma.diam = somaSize

# insert mechs
soma.insert('lk')
soma.insert('naf')
soma.insert('nal')
soma.insert('kdr')
soma.insert('ka')
soma.insert('ih')
soma.insert('cal')
soma.insert('can')
soma.insert('car')
soma.insert('cat')
soma.insert('sk')
soma.insert('bk')
soma.insert('pmp')

h.cao0_ca_ion = 2.0 # mM
soma.ena = 50  # mV
soma.ek = -90  # mV

h.celsius = 35
h.tstop = 1000
h.v_init = -60

h.nrncontrolmenu()

vWin = h.Graph(0)
vWin.size(0, runTime, -80, 20)
vWin.view(0, -80, runTime, 100, grXCoord, grYCoord, grWidth, grHeight)
grYCoord = grYCoord + grHeight + 100
vWin.addexpr("v(0.5)")
h.graphList[0].append(vWin)

iWin = h.Graph(0)
iWin.size(0, runTime, -0.005, 0.005)
iWin.view(0, -0.005, runTime, 0.01, grXCoord, grYCoord, grWidth, grHeight)
grYCoord = grYCoord + grHeight + 100
iWin.addvar("naf", soma(0.5)._ref_ina_naf, 2, 1)
iWin.addvar("nal", soma(0.5)._ref_ina_nal, 6, 1)
iWin.addvar("kdr", soma(0.5)._ref_ik_kdr, 3, 1)
iWin.addvar("ka", soma(0.5)._ref_ik_ka, 7, 1)
iWin.addvar("sk", soma(0.5)._ref_ik_sk, 4, 1)
iWin.addvar("bk", soma(0.5)._ref_ik_bk, 4, 2)
iWin.addvar("ih", soma(0.5)._ref_ih_ih, 1, 1)
iWin.addvar("ica", soma(0.5)._ref_ica, 5, 1)
h.graphList[1].append(iWin)

caWin = h.Graph(0)
caWin.size(0, runTime, 0, 1E-4)
caWin.view(0, 0, runTime, 1E-4, grXCoord, grYCoord, grWidth, grHeight)
caWin.addvar("cai", soma(0.5)._ref_cai)
h.graphList[1].append(caWin)


# record time
t = h.Vector().record(h._ref_t)

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
#ica = h.Vector().record(soma(0.5)._ref_ica)
ican = h.Vector().record(soma(0.5)._ref_ica_can)
icar = h.Vector().record(soma(0.5)._ref_ica_car)

# record intracellular ca
#caDat = h.Vector().record(ca.nodes[0]._ref_concentration)

h.finitialize(-55)
h.continuerun(1000)

# plots
plt.subplot(3, 1, 1)
plt.plot(t, v)
plt.ylabel('v (mV)')

plt.subplot(3, 1, 2)
plt.plot(t, inaf)
plt.plot(t, ikdr)
plt.plot(t, isk)
plt.plot(t, inal)
plt.plot(t, ika)
plt.plot(t, ibk)
plt.plot(t, iih)
plt.plot(t, ican)
plt.plot(t, icar)

plt.subplot(3, 1, 3)
#plt.plot(t,caDat)
plt.ylabel('cai (mM)')

plt.show()

import csv

with open('data.csv', 'w') as f:
    csv.writer(f).writerow(['t', 'v', 'inaf', 'ikdr', 'isk', 'inal', 'ika', 'ibk', 'iih', 'ican', 'icar'])
    csv.writer(f).writerows(zip(t, v, inaf, ikdr, isk, inal, ika, ibk, iih, ican, icar))