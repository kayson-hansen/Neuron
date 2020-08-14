COMMENT

ka.mod

A-type potassium current with activation and inactivation

Based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX ka
	USEION k READ ek WRITE ik
	RANGE gbar, gk, ik, tempm, minf, mTauScale
}

PARAMETER {
	gbar = 32	(S/m2)
	mvh = -29.4172	(mV)
	mvs = 8.43839	(mV)
	hvh = -61.1714	(mV)
	hvs = -4.57317	(mV)
	tauh = 200	(ms)
	mTauScale = 1.0
}

STATE {
	m
	h	
}

ASSIGNED {
	v	(mV)
	ek	(mV)
	gk	(S/cm2)
	ik	(mA/cm2)
	minf	hinf
	taum (ms)
	tempm
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	gk = gbar*m*m*m*h*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ik = gk*(v - ek)
}

INITIAL {
	rates(v)
	m = minf
	h = hinf
}

DERIVATIVE states {
	rates(v)
	m' = (minf - m)/taum
	h' = (hinf - h)/tauh
}

PROCEDURE rates( v (mV) ) {
	UNITSOFF
	taum = (2*exp(-(v + 50)*(v + 50)/550) + 1.1)*mTauScale
	UNITSON
	
	tempm = boltz(v,mvh,mvs)
	minf = pow(tempm,0.333)
	hinf = boltz(v,hvh,hvs)
}

FUNCTION boltz( v (mV), vh (mV), vs (mV) ) {
	boltz = 1/(1 + exp(-(v - vh)/vs))
}