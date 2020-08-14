COMMENT

capmp.mod

Calcium handling and pump-mediated clearance

based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(A) = (amp)
	(S) = (siemens)
	(mM) = (milli/liter)
	(L) = (liter)
	(um) = (micrometer)
}

UNITS {
	:FARADAY = 96494 (coul)
	:R = 8.3134 (joule/degC)
	FARADAY = (faraday) (coulomb)
	R = (k-mole) (joule/degC)
}

NEURON {
	SUFFIX pmp
	USEION ca READ ica, cai WRITE cai
	RANGE taucl, kb, caiInit
}

PARAMETER {
	taucl = 25	(ms)
	caiInit = 0.00005	(mM)
	shDepth = 100	(nm)	: 0.1E-6 m
	kb = 200	: represents calcium buffering
}

ASSIGNED {
	diam	(um)
	L	(um)
	area	(um2)
	ica	(mA/cm2)
	surf	(cm2)
}

STATE {
	cai	(mM) <0.0001>
}

INITIAL {	
	cai = caiInit
}

BREAKPOINT {
	SOLVE states METHOD cnexp
}

DERIVATIVE states {	
	cai' = -ica/((1+kb)*shDepth*FARADAY*2)*(1e7) + (caiInit-cai)/taucl 
}

