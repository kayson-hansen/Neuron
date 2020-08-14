"""
This file contains a Network class that generates a neuronal network using cells generated from the Cell class 
in the cellGenerator.py file. You can specify the number of cells in the network, as well as whether they should
have randomly generated parameters, and what percent uncertainty there should be in that randomness. To create 
a network, first import the Cell class using "from cellGenerator import Cell, params", then import the network 
class using "from cellNetwork import Network". Then, create a network with "myNetwork = Network(n, true, 20)" 
where n is the number of cells in the network, true means randomness is on, and 20 is the percent uncertainty. If
randomness=false, then you don't need to specify uncertainty.
"""

from neuron import h
from neuron.units import ms, mV
import numpy as np
import random
from cellGenerator import Cell, params

# network class made up of cells
class Network:
    
    
    def __create_cells(self, n, _rand, _uncertainty):
        self.cells = []
        if _rand == False:
            for i in range(0, n):
                self.cells.append(Cell(params, rand=_rand))
        else:   
            for i in range(0, n):
                self.cells.append(Cell(params, rand=_rand, uncertainty=_uncertainty))
    
    def __connect_cells(self, n):
        pass
    
    def __init__(self, n, rand, uncertainty=0):
        self.__create_cells(n, rand, uncertainty)