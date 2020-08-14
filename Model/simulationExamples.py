"""
This is a file with several examples on how to use the cellGenerator.py and cellNetwork.py files. 
"""

from neuron import h
from neuron.units import ms, mV
import numpy as np
import random
from cellGenerator import Cell, params
from cellNetwork import Network
import matplotlib.pyplot as plt

# sets some conditions for the simulation
h.load_file('stdrun.hoc')
h.cvode_active(True)

# set initial conditions (they'll be the same for each example)
h.celsius = 35
h.v_init = -55 * mV
h.tstop = 5000 * ms


# Example 1: graphing membrane voltage, currents, and intracellular calcium of a cell

test_cell = Cell(params)

# record time
t = h.Vector().record(h._ref_t)

# record membrane potential
test_cell.record_voltage()

# record currents
inaf = h.Vector().record(test_cell.soma(0.5)._ref_ina_naf)
ikdr = h.Vector().record(test_cell.soma(0.5)._ref_ik_kdr)
isk = h.Vector().record(test_cell.soma(0.5)._ref_ik_sk)
inal = h.Vector().record(test_cell.soma(0.5)._ref_ina_nal)
ika = h.Vector().record(test_cell.soma(0.5)._ref_ik_ka)
ibk = h.Vector().record(test_cell.soma(0.5)._ref_ik_bk)
iih = h.Vector().record(test_cell.soma(0.5)._ref_ih_ih)
ican = h.Vector().record(test_cell.soma(0.5)._ref_ica_can)
icar = h.Vector().record(test_cell.soma(0.5)._ref_ica_car)
ical = h.Vector().record(test_cell.soma(0.5)._ref_ica_cal)

# record calcium
caDat = h.Vector().record(test_cell.soma(0.5)._ref_cai)

h.run()

plt.subplot(3, 1, 1)
plt.plot(t, test_cell.v)
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


# Example 2: graphing membrane voltage of each cell in a network with 9 cells (there are 3 graphs per image)

test_network = Network(9, False)

# record time
t = h.Vector().record(h._ref_t)

# record voltage
for cell in test_network.cells:
    cell.record_voltage()

h.run()

for i in range(0, len(test_network.cells), 3): 
    plt.subplot(3, 1, 1)
    plt.plot(t, test_network.cells[i].v)
    plt.ylabel('Vm (mV)')
    axes = plt.gca()
    axes.set_ylim([-80, 40])
    plt.subplot(3, 1, 2)
    plt.plot(t, test_network.cells[i+1].v)
    plt.ylabel('Vm (mV)')
    axes = plt.gca()
    axes.set_ylim([-80, 40])
    plt.subplot(3, 1, 3)
    plt.plot(t, test_network.cells[i+2].v)
    plt.ylabel('Vm (mV)')
    axes = plt.gca()
    axes.set_ylim([-80, 40])
    plt.show()


# Example 3: graphing raster plots from a network with 10 cells

test_network2 = Network(10, True, 5)

# record time
t = h.Vector().record(h._ref_t)

# record spikes
for cell in test_network2.cells:
    cell.record_spikes()

h.run()

positions = [[]]
for cell in test_network2.cells:
    positions.append(cell.spike_times)

plt.eventplot(positions, linelengths=0.5)
plt.title('Spike raster plot')
plt.xlabel('Time (ms)')
plt.ylabel('Neuron')
axes = plt.gca()
axes.set_xlim([0, 5000])
axes.set_ylim([0, len(test_network2.cells) + 1])
plt.locator_params(axis='y', nbins=11)
plt.show()