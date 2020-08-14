COMMENT

ih.mod

Hyperpolarization-activated non-specific cation channel

Based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX ih
	NONSPECIFIC_CURRENT ih
	RANGE gbar, gih, ih
}

PARAMETER {
	gbar = 3	(S/m2)
	vh = -80	(mV)
	vs = 6.5	(mV)
	erev = -35	(mV)
}

STATE {
	m
}

ASSIGNED {
	v	(mV)
	gih	(S/cm2)
	ih	(mA/cm2)
	minf
	tau	(ms)
	alpha	(/ms)
	beta	(/ms)
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	gih = gbar*m*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ih = gih*(v - erev)
}

INITIAL {
	rates(v)
	m = minf
}

DERIVATIVE states {
	rates(v)
	m' = (minf - m)/tau
}

PROCEDURE rates( v (mV) ) {
	UNITSOFF
	alpha = 2e-5*exp(-v/-10.2)
	beta = 7.6/(exp((v - 10)/-100) + 1)
	UNITSON
	
	tau = 1000/(alpha + beta)	: convert sec to ms
	minf = 1/(1 + exp((v - vh)/vs))
}