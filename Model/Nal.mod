COMMENT

nal.mod

Sodium leak current w/ constant conductance

Based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX nal
	USEION na READ ena WRITE ina
	RANGE gbar, erev, ina
}

PARAMETER {
	gbar = 0.135	(S/m2)
	erev = 0	(mV)
}

ASSIGNED {
	v (mV)
	ena (mV)
	ina (mA/cm2)
}

BREAKPOINT {
	ina = gbar*(v - erev)*(0.0001)	: convert S/m2 (gbar) to S/cm2
}