"""
This file contains a Cell class that can be used to generate a cell with given parameters that has a 
soma, as well as primary, secondary, and tertiary dendrites. A set of default parameters can be found
at the end of the file in a dict. To use this class in another Python file, add "from cellGenerator import Cell, params"
at the top of your Python file, then change whichever parameters you want in the params dict (e.g. if you want to change
all_can_pbar, use "params["all_can_pbar"] = x", where x is your new value). Then, decide if you want randomness in your 
parameters or not, and create a cell with "myCell = Cell(params, rand=true, uncertainty=10)" (if rand=false, then you don't
need to specify uncertainty). 
"""

from neuron import h
from neuron.units import ms, mV
import numpy as np
import random

# cell class with soma, primary, secondary, and tertiary dendrites
class Cell:

    def __setup(self):
        self.soma = h.Section(name='soma', cell=self)
        self.prim = []
        self.sec = []
        self.tert = []
        for i in range(0, 6):
            self.prim.append(h.Section(name='prim{0}'.format(i), cell=self))
        for i in range(0, 4):
            self.sec.append(h.Section(name='sec{0}'.format(i), cell=self))
        for i in range(0, 8):
            self.tert.append(h.Section(name='tert{0}'.format(i), cell=self))
        self.allSections = [self.soma] + self.prim + self.sec + self.tert
        self.dendrites = self.prim + self.sec + self.tert
        self.proximal = [self.soma, self.prim[0], self.prim[1], self.prim[2], self.prim[4]]
        self.primary1 = [self.prim[0], self.prim[1]]
        self.primary2 = [self.prim[2], self.prim[4]]
        self.primary3 = [self.prim[3], self.prim[5]]
    
    def __topol(self):
        self.prim[0].connect(self.soma(0))
        self.prim[1].connect(self.soma(1))
        self.prim[2].connect(self.prim[0](1))
        self.prim[3].connect(self.prim[2](1))
        self.prim[4].connect(self.prim[1](1))
        self.prim[5].connect(self.prim[4](1))
    
        for i in range(0, 2): self.sec[i].connect(self.prim[3](1))
        for i in range(2, 4): self.sec[i].connect(self.prim[5](1))
        for i in range(0, 2): self.tert[i].connect(self.sec[0](1))
        for i in range(2, 4): self.tert[i].connect(self.sec[1](1))
        for i in range(4, 6): self.tert[i].connect(self.sec[2](1))
        for i in range(6, 8): self.tert[i].connect(self.sec[3](1))
    
    def __geom(self, sec_l, sec_diam, tert_l, tert_diam, prim1_l, prim1_diam, prim2_l, prim2_diam,
                prim3_l, prim3_diam, soma_l, soma_diam):
                
        for section in self.sec:
            section.L = sec_l
            section.diam = sec_diam
        for section in self.tert:
            section.L = tert_l
            section.diam = tert_diam
        for section in self.primary1:
            section.L = prim1_l
            section.diam = prim1_diam
        for section in self.primary2:
            section.L = prim2_l
            section.diam = prim2_diam
        for section in self.primary3:
            section.L = prim3_l
            section.diam = prim3_diam
        self.soma.L = soma_l
        self.soma.diam = soma_diam
        
    def __geom_nseg(self):
        for section in self.sec: section.nseg = 1
        for section in self.tert: section.nseg = 5
        for section in self.primary1: section.nseg = 3
        for section in self.primary2: section.nseg = 1
        for section in self.primary3: section.nseg = 3
        self.soma.nseg = 3
    
    def __biophys(self, all_ra, all_cm, all_bk_gbar, all_cal_pbar12, all_cal_pbar13, all_can_pbar, 
                    all_car_pbar, all_pmp_kb, all_ih_gbar, all_kdr_gbar, all_naf_gbar, all_nal_gbar, all_nap_gbar, all_sk_gbar,
                    all_lk_g, all_lk_e, cao, ek, dend_cat_pbar, prox_ka_gbar, soma_ka_gbar, soma_nap_gbar, soma_pmp_taucl, soma_pmp_kb):
                    
        for section in self.allSections:
            section.Ra = all_ra
            section.cm = all_cm
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
                seg.bk.gbar = all_bk_gbar
                seg.cal.pbar12 = all_cal_pbar12
                seg.cal.pbar13 = all_cal_pbar13
                seg.can.pbar = all_can_pbar
                seg.car.pbar = all_car_pbar
                seg.pmp.kb = all_pmp_kb
                seg.ih.gbar = all_ih_gbar
                seg.kdr.gbar = all_kdr_gbar
                seg.naf.gbar = all_naf_gbar
                seg.nal.gbar = all_nal_gbar
                seg.nap.gbar = all_nap_gbar
                seg.sk.gbar = all_sk_gbar
                seg.lk.g = all_lk_g
                seg.lk.e = all_lk_e
                
            section.cao = cao
            section.ek = ek
            
            
        for section in self.dendrites:
            section.insert('cat')
            for seg in section:
                #seg.pmp.kb = 96
                seg.cat.pbar = dend_cat_pbar
        
        for section in self.proximal:
            section.insert('ka')
            for seg in section:
                seg.ka.gbar = prox_ka_gbar
                
        for seg in self.soma:
            seg.ka.gbar = soma_ka_gbar
            seg.nap.gbar = soma_nap_gbar
            seg.pmp.taucl = soma_pmp_taucl
            seg.pmp.kb = soma_pmp_kb
    
    # when using this class to create a cell, specify which properties you want, and the rest will default
    # to the values below; also, rand determines whether or not there is a level of uncertainty for the properties
    def __init__(self, params, rand=False, uncertainty=10):
        
        if rand:
            for key, val in params.items():
                params[key] = random.uniform(val - val * uncertainty / 100.0, val + val * uncertainty / 100.0)
                
        self.__setup()
        self.__topol()
        self.__geom(params["sec_l"], params["sec_diam"], params["tert_l"], params["tert_diam"], params["prim1_l"], params["prim1_diam"], 
                        params["prim2_l"], params["prim2_diam"], params["prim3_l"], params["prim3_diam"], params["soma_l"], params["soma_diam"])
        self.__biophys(params["all_ra"], params["all_cm"], params["all_bk_gbar"], params["all_cal_pbar12"], params["all_cal_pbar13"], 
                        params["all_can_pbar"], params["all_car_pbar"], params["all_pmp_kb"], params["all_ih_gbar"], params["all_kdr_gbar"], 
                        params["all_naf_gbar"], params["all_nal_gbar"], params["all_nap_gbar"], params["all_sk_gbar"], params["all_lk_g"], 
                        params["all_lk_e"], params["cao"], params["ek"], params["dend_cat_pbar"], params["prox_ka_gbar"], params["soma_ka_gbar"], 
                        params["soma_nap_gbar"], params["soma_pmp_taucl"], params["soma_pmp_kb"])
        self.__geom_nseg()
        
    # set up spike recording 
    def record_spikes(self):
        self.spike_detector = h.NetCon(self.soma(0.5)._ref_v, None, sec=self.soma)
        self.spike_times = h.Vector()
        self.spike_detector.record(self.spike_times)
    
    def record_voltage(self):
        self.v = h.Vector().record(self.soma(0.5)._ref_v)


params = {"sec_l": 20, "sec_diam": 1, "tert_l": 140, "tert_diam": 0.8, "prim1_l": 40, "prim1_diam": 2.5, "prim2_l": 10, "prim2_diam": 2,
                "prim3_l": 30, "prim3_diam": 2, "soma_l": 25, "soma_diam": 25, "all_ra": 400, "all_cm": 1, "all_bk_gbar": 500, "all_cal_pbar12": 10**-7,
                "all_cal_pbar13": 5*10**-9, "all_can_pbar": 1.2*10**-6, "all_car_pbar": 5*10**-7, "all_pmp_kb": 200, "all_ih_gbar": 0.5, "all_kdr_gbar": 20,
                "all_naf_gbar": 250, "all_nal_gbar": 0.135, "all_nap_gbar": 0.07, "all_sk_gbar": 3, "all_lk_g": 0.2, "all_lk_e": -60, "cao": 2.0, "ek": -90,
                "dend_cat_pbar": 10**-7, "prox_ka_gbar": 24.5, "soma_ka_gbar": 32, "soma_nap_gbar": 0.1, "soma_pmp_taucl": 20, "soma_pmp_kb": 45}