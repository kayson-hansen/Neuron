COMMENT

leak.mod

passive non-specific leak current

Based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX lk
	NONSPECIFIC_CURRENT i
	RANGE g, e
}

PARAMETER {
	g = 0.2	(S/m2)
	e = -60	(mV)
}

ASSIGNED {
	v	(mV)
	i	(mA/cm2)
}

BREAKPOINT {
	i = g*(v - e)*(0.0001)	: convert S/m2 (gbar) to S/cm2
}