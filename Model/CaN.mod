COMMENT

can.mod

N-type calcium channel w/ GHK permeability

based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
	(mM) = (milli/liter)
}

NEURON {
	SUFFIX can
	USEION ca READ cai, cao WRITE ica
	RANGE pbar, ica, pca
}

UNITS {
	:FARADAY = 96520 (coul)
	:R = 8.3134 (joule/degC)
	FARADAY = (faraday) (coulomb)
	R = (k-mole) (joule/degC)
}

PARAMETER {
	pbar = 12E-7	(m/s)
	htau = 70	(ms)
}

STATE {
	m h
}

ASSIGNED {
	v	(mV)
	celsius	(degC)
	cai	(mM)
	cao	(mM)
	ica	(mA/cm2)
	minf hinf
	mtau	(ms)
	pca	(cm/s)
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	pca = pbar*m*m*h*(100)
	ica = pca*ghk(v, cai, cao)
}

INITIAL {
	rates(v)
	m = minf
	h = hinf
}

DERIVATIVE states {
	rates(v)
	m' = (minf - m)/mtau
	h' = (hinf - h)/htau
}

PROCEDURE rates( v (mV) ) {
	LOCAL ma, mb
	
	UNITSOFF
	ma = 39800*(v + 17.19)/(exp((v + 17.19)/15.22) - 1)
	mb = 384.2*exp(v/23.82)
	mtau = 1000/(ma + mb)
	
	minf = 1/(1 + exp((v + 3)/-8))
	
	hinf = 0.21*1/(1 + exp((v + 74.8)/6.5)) + 0.79
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