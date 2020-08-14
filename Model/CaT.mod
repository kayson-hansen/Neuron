COMMENT

cat.mod

T-type calcium channel w/ GHK permeability

based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
	(mM) = (milli/liter)
}

NEURON {
	SUFFIX cat
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
	pbar = 0.1E-6	(m/s)
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
	htau	(ms)
	pca	(cm/s)
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	pca = pbar*m*m*m*h*(100)
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
	LOCAL ma, mb, ha, hb
	
	UNITSOFF
	ma = 14552*(v + 84.5)/(exp((v + 84.5)/7.12)-1)
	mb = 4984.2*exp(v/13)
	mtau = ((1000/(ma + mb))+0.0022)/2
	
	minf = 1/(1 + exp((v - 9 + 72)/-8))
	
	ha = 2652*(v + 94.5)/(exp((v + 94.5)/5.12)-1)
	hb = 684.2*exp(v/13)
	htau = (1000/(ha + hb) + 0.1)/2
	
	hinf = 1/(1 + exp((v  - 7 + 93)/5))
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