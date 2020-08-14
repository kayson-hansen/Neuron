COMMENT

naf.mod

Fast sodium channel w/ hodgkin-huxley mechanics: activation & fast inactivation

Based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
}

NEURON {
	SUFFIX naf
	USEION na READ ena WRITE ina
	RANGE gbar, gna, ina
}

PARAMETER {
	gbar = 250 	(S/m2)
	mvh = -20.907 	(mV)
	mvs = 9.7264 	(mV)
	hvh = -54.0289	(mV)
	hvs = -10.7665	(mV)
}

STATE {
	m
	h
}

ASSIGNED {
	v (mV)
	ena (mV)
	gna (S/cm2)
	ina (mA/cm2)
	alpham (/ms) betam (/ms)
	minf hinf
	alphah (/ms) betah (/ms)
	taum (ms) tauh (ms)	
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	gna = gbar*m*m*m*h*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ina = gna*(v - ena)
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
	:alpham = -(15.6504 + 0.4043*v)/(exp(-19.565 - 0.50542*v) - 1)
	:betam = 3.0212*exp(-7.4630e-3 * v)
	:if( v > -38.75 && v < -38.65) { taum = 0.217 }
	:else { taum = 0.01 + 1/(alpham + betam) }
	
	taum = 0.2
	
	alphah = 5.0754E-4 * exp(-6.3213e-2 * v)
	betah = 9.7529 * exp(0.13442 * v)
	tauh = 0.4 + 1/(alphah + betah)
	UNITSON
	
	minf = boltz(v, mvh, mvs)
	hinf = boltz(v, hvh, hvs)
}

FUNCTION boltz( v (mV), vh (mV), vs (mV) ) {
	boltz = 1/(1 + exp(-(v - vh)/vs))
}