from neuron import h
from cellGenerator import Cell, params
from cellNetwork import Network
import random
import matplotlib.pyplot as plt

h.load_file('stdrun.hoc')

pc = h.ParallelContext()
pc.set_maxstep(10)
idhost = int(pc.id())
nhost = int(pc.nhost())

test_network2 = Network(10, True, 5)

# record time
t = h.Vector().record(h._ref_t)

# record spikes
for cell in test_network2.cells:
    cell.record_spikes()

h.stdinit()
h.dt = 0.025
duration = 100.0

pc.psolve(duration)  # actually run the sim in all nodes

if idhost==0:
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

pc.done()