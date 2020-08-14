COMMENT

sk.mod

small-conductance calcium-activated potassium channel

based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
	(mM) = (milli/liter)
}

NEURON {
	SUFFIX sk
	USEION k READ ek WRITE ik
	USEION ca READ cai
	RANGE gbar, gsk, ik
}

PARAMETER {
	gbar = 3	(S/m2)
	tau = 4.9	(ms)
	kd = 0.57e-3	(mM)
}

STATE {
	skact
}

ASSIGNED {
	v	(mV)
	ek	(mV)
	gsk	(S/cm2)
	ik	(mA/cm2)
	skact_inf
	cai	(mM)
	theta
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	gsk = gbar*skact*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ik = gsk*(v - ek)
}

INITIAL {
	rates(cai)
	skact = skact_inf
}

DERIVATIVE states {
	rates(cai)
	skact' = (skact_inf - skact)/tau
}

PROCEDURE rates( cai (mM) ) {
	theta = cai/kd
	skact_inf = pow(theta,5.2)/(1 + pow(theta,5.2))
}