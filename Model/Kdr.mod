COMMENT

kdr.mod

Delayed-rectifier potassium channel w/ hodgkin-huxley mechanics

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX kdr
	USEION k READ ek WRITE ik
	RANGE gbar, gk, ik, tauMax
}

PARAMETER {
	gbar = 20	(S/m2)
	vh = -5.8	(mV)
	vs = 8.0	(mV)
	tauMax = 20	(ms)
}

STATE {
	n
}

ASSIGNED {
	v	(mV)
	ek	(mV)
	gk	(S/cm2)
	ik	(mA/cm2)
	ninf
	tau (ms)
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	gk = gbar*n*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ik = gk*(v - ek)
}

INITIAL {
	rates(v)
	n = ninf
}

DERIVATIVE states {
	rates(v)
	n' = (ninf - n)/tau
}

PROCEDURE rates( v (mV) ) {
	UNITSOFF
	tau = tauMax*exp(-((22+v)*(22+v))/(17*17)) + 2
	UNITSON
	
	ninf = boltz(v, vh, vs)
}

FUNCTION boltz( v (mV), vh (mV), vs (mV) ) {
	boltz = 1/(1 + exp(-(v - vh)/vs))
}