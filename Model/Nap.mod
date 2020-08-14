COMMENT

nap.mod

Sub-threshold voltage-dependent sodium channel

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX nap
	USEION na READ ena WRITE ina
	RANGE gbar, gna, ina, vh, vs
}

PARAMETER {
	gbar = 1.35	(S/m2)
	vh = -50	(mV)
	vs = 3	(mV)
}

ASSIGNED {
	v	(mV)
	ena	(mV)
	gna	(S/cm2)
	ina	(mA/cm2)
}

BREAKPOINT {
	gna = gbar*boltz(v, vh, vs)*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ina = gna*(v - ena)
}

FUNCTION boltz( v (mV), vh (mV), vs (mV) ) {
	boltz = 1/(1 + exp(-(v - vh)/vs))
}