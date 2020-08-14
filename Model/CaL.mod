COMMENT

cal.mod

L-type calcium channel isoforms 1.2 & 1.3 with GHK permeability

based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
	(mM) = (milli/liter)
}

NEURON {
	SUFFIX cal
	USEION ca READ cai, cao WRITE ica
	RANGE pbar12, pbar13, pca12, pca13, ica, ical12, ical13
}

UNITS {
	:FARADAY = 96520 (coul)
	:R = 8.3134 (joule/degC)
	FARADAY = (faraday) (coulomb)
	R = (k-mole) (joule/degC)
}

PARAMETER {
	pbar12 = 0.1E-6	(m/s)
	pbar13 = 5E-9	(m/s)
	htau12 = 44.3	(ms)
	htau13 = 44.3	(ms)
}

STATE {
	m12
	h12
	m13
	h13
}

ASSIGNED {
	v	(mV)
	celsius	(degC)
	cai	(mM)
	cao	(mM)
	ica	(mA/cm2)
	ical12	(mA/cm2)
	ical13	(mA/cm2)
	minf12
	hinf12
	mtau12	(ms)
	minf13
	hinf13
	mtau13	(ms)
	pca12	(cm/s)
	pca13	(cm/s)
}


BREAKPOINT {
	SOLVE states METHOD cnexp
	pca12 = pbar12*m12*h12*(100)
	ical12 = pca12*ghk(v, cai, cao)
	pca13 = pbar13*m13*h13*(100)
	ical13 = pca13*ghk(v, cai, cao)
	ica = ical12 + ical13
}

INITIAL {
	rates12(v)
	rates13(v)
	m12 = minf12
	h12 = hinf12
	m13 = minf13
	h13 = hinf13
}

DERIVATIVE states {
	rates12(v)
	rates13(v)
	m12' = (minf12 - m12)/mtau12
	h12' = (hinf12 - h12)/htau12
	m13' = (minf13 - m13)/mtau13
	h13' = ((hinf13 - h13)/htau13)/0.5
}

PROCEDURE rates12( v (mV) ) {
	LOCAL a, b
	
	UNITSOFF
	a = 0.0398e6*(v + 8.124)/(exp((v + 8.124)/9.005) - 1)
	b = 0.99e3*exp(v/31.4)
	mtau12 = 1000/(a + b)
	
	minf12 = 1/(1 + exp((v + 8.9)/-6.7))
	
	hinf12 = 0.17*1/(1 + exp((v + 55)/8)) + 0.83
	UNITSON
}

PROCEDURE rates13( v (mV) ) {
	LOCAL a, b
	
	UNITSOFF
	a = 39800*(v + 67.24)/(exp((v + 67.24)/15.005) - 1)
	b = 3500*exp(v/31.4)
	mtau13 = 1000/(a + b)/0.5
	
	minf13 = 1/(1 + exp((v + 40.0)/-5))
	
	hinf13 = 1/(1 + exp((v + 37)/5))
	UNITSON	
}

COMMENT

The following two functions are from NEURON example file cachan.mod

ENDCOMMENT

FUNCTION ghk(v(mV), ci(mM), co(mM)) (.001 coul/cm3) {
	LOCAL z, eci, eco
	z = (1e-3)*2*FARADAY*v/(R*(celsius+273.15))
	eco = co*efun(z)
	eci = ci*efun(-z)
	:high cao charge moves inward
	:negative potential charge moves inward
	ghk = (.001)*2*FARADAY*(eci - eco)
}

FUNCTION efun(z) {
	if (fabs(z) < 1e-4) {
		efun = 1 - z/2
	}else{
		efun = z/(exp(z) - 1)
	}
}