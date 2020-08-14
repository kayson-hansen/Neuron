COMMENT

bk.mod

big-conductance calcium-activated potassium channel w/ voltage dependence

based on Tarfa et al 2017

ENDCOMMENT

UNITS {
	(mV) = (millivolt)
	(mA) = (milliamp)
	(S) = (siemens)
	(mM) = (milli/liter)
}

NEURON {
	SUFFIX bk
	USEION k READ ek WRITE ik
	USEION ca READ cai
	RANGE gbar, gsk, ik
}

PARAMETER {
	gbar = 500	(S/m2)
}

STATE {
	bkact
}

ASSIGNED {
	v	(mV)
	ek	(mV)
	gbk	(S/cm2)
	ik	(mA/cm2)
	bkinf
	pretau (ms)
	bktau	(ms)
	cai	(mM)
}

BREAKPOINT {
	SOLVE states METHOD cnexp
	gbk = gbar*bkact*(0.0001)	: convert S/m2 (gbar) to S/cm2
	ik = gbk*(v - ek)
}

INITIAL {
	rates(v, cai)
	bkact = bkinf
}

DERIVATIVE states {
	rates(v, cai)
	bkact' = (bkinf - bkact)/bktau
}

PROCEDURE rates( v (mV), cai (mM) ) {
	UNITSOFF
	:bkinf = 1/(1 + exp((-56.449 + 104.52*exp(-0.22964*cai*1e3) + 295*exp(-2.1571*cai*1e3) - v)/25/1.6))
	bkinf = 1/(1 + exp(((-56.449 + 104.52*exp(-0.22964*cai*1000) + 295.68*exp(-2.1571*cai*1000)) - v)/(25/1.6)))
	pretau = 1/(10*(exp(-(v + 100 - (25 - 55.7 + 136.9*exp(-0.28*cai)))/63.6)+exp(-(150 - (v + 100 - (25 - 55.7 + 136.9*exp(-0.28*cai))))/63.6))-5.2)
	if( pretau < 0.2 ) { pretau = 0.2 }
	bktau = ((((13.7 + 234*exp(-0.72*cai)) - 1)*((pretau-0.2)/0.8)) + 1)
	UNITSON
}

:float exp1a = (-0.22964*cai*1000)
:float exp1b = {exp {exp1a}} = exp(-0.22964*cai*1000)
:float exp2a = (-2.1571*cai*1000)
:float exp2b = {exp {exp2a}} = exp(-2.1571*cai*1000)

:float preinf = {-56.449 + 104.52 * {exp1b} + 295.68 * {exp2b}} = -56.449 + 104.52*exp(-0.22964*cai*1000) + 295.68*exp(-2.1571*cai*1000)
:float inf = (({preinf}-{v})/(25/1.6)) = ((-56.449 + 104.52*exp(-0.22964*cai*1000) + 295.68*exp(-2.1571*cai*1000)) - v)/(25/1.6)
:float exp3 = {exp {inf}} = exp(((-56.449 + 104.52*exp(-0.22964*cai*1000) + 295.68*exp(-2.1571*cai*1000)) - v)/25/1.6)
:float entry = {1/(1 + {exp3})} = 1/(1 + exp(((-56.449 + 104.52*exp(-0.22964*cai*1000) + 295.68*exp(-2.1571*cai*1000)) - v)/(25/1.6)))


