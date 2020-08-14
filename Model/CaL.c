/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib_ansi.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__cal
#define _nrn_initial _nrn_initial__cal
#define nrn_cur _nrn_cur__cal
#define _nrn_current _nrn_current__cal
#define nrn_jacob _nrn_jacob__cal
#define nrn_state _nrn_state__cal
#define _net_receive _net_receive__cal 
#define rates13 rates13__cal 
#define rates12 rates12__cal 
#define states states__cal 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define pbar12 _p[0]
#define pbar13 _p[1]
#define ica _p[2]
#define ical12 _p[3]
#define ical13 _p[4]
#define pca12 _p[5]
#define pca13 _p[6]
#define m12 _p[7]
#define h12 _p[8]
#define m13 _p[9]
#define h13 _p[10]
#define Dm12 _p[11]
#define Dh12 _p[12]
#define Dm13 _p[13]
#define Dh13 _p[14]
#define cai _p[15]
#define cao _p[16]
#define minf12 _p[17]
#define hinf12 _p[18]
#define mtau12 _p[19]
#define minf13 _p[20]
#define hinf13 _p[21]
#define mtau13 _p[22]
#define v _p[23]
#define _g _p[24]
#define _ion_cai	*_ppvar[0]._pval
#define _ion_cao	*_ppvar[1]._pval
#define _ion_ica	*_ppvar[2]._pval
#define _ion_dicadv	*_ppvar[3]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static void _hoc_efun(void);
 static void _hoc_ghk(void);
 static void _hoc_rates13(void);
 static void _hoc_rates12(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_cal", _hoc_setdata,
 "efun_cal", _hoc_efun,
 "ghk_cal", _hoc_ghk,
 "rates13_cal", _hoc_rates13,
 "rates12_cal", _hoc_rates12,
 0, 0
};
#define efun efun_cal
#define ghk ghk_cal
 extern double efun( _threadargsprotocomma_ double );
 extern double ghk( _threadargsprotocomma_ double , double , double );
 /* declare global and static user variables */
#define htau13 htau13_cal
 double htau13 = 44.3;
#define htau12 htau12_cal
 double htau12 = 44.3;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "htau12_cal", "ms",
 "htau13_cal", "ms",
 "pbar12_cal", "m/s",
 "pbar13_cal", "m/s",
 "ica_cal", "mA/cm2",
 "ical12_cal", "mA/cm2",
 "ical13_cal", "mA/cm2",
 "pca12_cal", "cm/s",
 "pca13_cal", "cm/s",
 0,0
};
 static double delta_t = 0.01;
 static double h130 = 0;
 static double h120 = 0;
 static double m130 = 0;
 static double m120 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "htau12_cal", &htau12_cal,
 "htau13_cal", &htau13_cal,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(_NrnThread*, _Memb_list*, int);
static void nrn_state(_NrnThread*, _Memb_list*, int);
 static void nrn_cur(_NrnThread*, _Memb_list*, int);
static void  nrn_jacob(_NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(_NrnThread*, _Memb_list*, int);
static void _ode_matsol(_NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[4]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"cal",
 "pbar12_cal",
 "pbar13_cal",
 0,
 "ica_cal",
 "ical12_cal",
 "ical13_cal",
 "pca12_cal",
 "pca13_cal",
 0,
 "m12_cal",
 "h12_cal",
 "m13_cal",
 "h13_cal",
 0,
 0};
 static Symbol* _ca_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 25, _prop);
 	/*initialize range parameters*/
 	pbar12 = 1e-007;
 	pbar13 = 5e-009;
 	_prop->param = _p;
 	_prop->param_size = 25;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 	_ppvar[1]._pval = &prop_ion->param[2]; /* cao */
 	_ppvar[2]._pval = &prop_ion->param[3]; /* ica */
 	_ppvar[3]._pval = &prop_ion->param[4]; /* _ion_dicadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, _NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _CaL_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	_ca_sym = hoc_lookup("ca_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 25, 5);
  hoc_register_dparam_semantics(_mechtype, 0, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "ca_ion");
  hoc_register_dparam_semantics(_mechtype, 4, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 cal D:/DoD Internship/Neuron/Model/CaL.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double FARADAY = 96485.3;
 static double R = 8.3145;
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rates13(_threadargsprotocomma_ double);
static int rates12(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[4], _dlist1[4];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   rates12 ( _threadargscomma_ v ) ;
   rates13 ( _threadargscomma_ v ) ;
   Dm12 = ( minf12 - m12 ) / mtau12 ;
   Dh12 = ( hinf12 - h12 ) / htau12 ;
   Dm13 = ( minf13 - m13 ) / mtau13 ;
   Dh13 = ( ( hinf13 - h13 ) / htau13 ) / 0.5 ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 rates12 ( _threadargscomma_ v ) ;
 rates13 ( _threadargscomma_ v ) ;
 Dm12 = Dm12  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau12 )) ;
 Dh12 = Dh12  / (1. - dt*( ( ( ( - 1.0 ) ) ) / htau12 )) ;
 Dm13 = Dm13  / (1. - dt*( ( ( ( - 1.0 ) ) ) / mtau13 )) ;
 Dh13 = Dh13  / (1. - dt*( ( ( ( ( ( - 1.0 ) ) ) / htau13 ) ) / 0.5 )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   rates12 ( _threadargscomma_ v ) ;
   rates13 ( _threadargscomma_ v ) ;
    m12 = m12 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mtau12)))*(- ( ( ( minf12 ) ) / mtau12 ) / ( ( ( ( - 1.0 ) ) ) / mtau12 ) - m12) ;
    h12 = h12 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / htau12)))*(- ( ( ( hinf12 ) ) / htau12 ) / ( ( ( ( - 1.0 ) ) ) / htau12 ) - h12) ;
    m13 = m13 + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / mtau13)))*(- ( ( ( minf13 ) ) / mtau13 ) / ( ( ( ( - 1.0 ) ) ) / mtau13 ) - m13) ;
    h13 = h13 + (1. - exp(dt*(( ( ( ( ( - 1.0 ) ) ) / htau13 ) ) / 0.5)))*(- ( ( ( ( ( hinf13 ) ) / htau13 ) ) / 0.5 ) / ( ( ( ( ( ( - 1.0 ) ) ) / htau13 ) ) / 0.5 ) - h13) ;
   }
  return 0;
}
 
static int  rates12 ( _threadargsprotocomma_ double _lv ) {
   double _la , _lb ;
  _la = 0.0398e6 * ( _lv + 8.124 ) / ( exp ( ( _lv + 8.124 ) / 9.005 ) - 1.0 ) ;
   _lb = 0.99e3 * exp ( _lv / 31.4 ) ;
   mtau12 = 1000.0 / ( _la + _lb ) ;
   minf12 = 1.0 / ( 1.0 + exp ( ( _lv + 8.9 ) / - 6.7 ) ) ;
   hinf12 = 0.17 * 1.0 / ( 1.0 + exp ( ( _lv + 55.0 ) / 8.0 ) ) + 0.83 ;
     return 0; }
 
static void _hoc_rates12(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates12 ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int  rates13 ( _threadargsprotocomma_ double _lv ) {
   double _la , _lb ;
  _la = 39800.0 * ( _lv + 67.24 ) / ( exp ( ( _lv + 67.24 ) / 15.005 ) - 1.0 ) ;
   _lb = 3500.0 * exp ( _lv / 31.4 ) ;
   mtau13 = 1000.0 / ( _la + _lb ) / 0.5 ;
   minf13 = 1.0 / ( 1.0 + exp ( ( _lv + 40.0 ) / - 5.0 ) ) ;
   hinf13 = 1.0 / ( 1.0 + exp ( ( _lv + 37.0 ) / 5.0 ) ) ;
     return 0; }
 
static void _hoc_rates13(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rates13 ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
double ghk ( _threadargsprotocomma_ double _lv , double _lci , double _lco ) {
   double _lghk;
 double _lz , _leci , _leco ;
 _lz = ( 1e-3 ) * 2.0 * FARADAY * _lv / ( R * ( celsius + 273.15 ) ) ;
   _leco = _lco * efun ( _threadargscomma_ _lz ) ;
   _leci = _lci * efun ( _threadargscomma_ - _lz ) ;
   _lghk = ( .001 ) * 2.0 * FARADAY * ( _leci - _leco ) ;
   
return _lghk;
 }
 
static void _hoc_ghk(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  ghk ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) );
 hoc_retpushx(_r);
}
 
double efun ( _threadargsprotocomma_ double _lz ) {
   double _lefun;
 if ( fabs ( _lz ) < 1e-4 ) {
     _lefun = 1.0 - _lz / 2.0 ;
     }
   else {
     _lefun = _lz / ( exp ( _lz ) - 1.0 ) ;
     }
   
return _lefun;
 }
 
static void _hoc_efun(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r =  efun ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 4;}
 
static void _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  cao = _ion_cao;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 4; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  cao = _ion_cao;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 1, 2);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 2, 3);
   nrn_update_ion_pointer(_ca_sym, _ppvar, 3, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  h13 = h130;
  h12 = h120;
  m13 = m130;
  m12 = m120;
 {
   rates12 ( _threadargscomma_ v ) ;
   rates13 ( _threadargscomma_ v ) ;
   m12 = minf12 ;
   h12 = hinf12 ;
   m13 = minf13 ;
   h13 = hinf13 ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cai = _ion_cai;
  cao = _ion_cao;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   pca12 = pbar12 * m12 * h12 * ( 100.0 ) ;
   ical12 = pca12 * ghk ( _threadargscomma_ v , cai , cao ) ;
   pca13 = pbar13 * m13 * h13 * ( 100.0 ) ;
   ical13 = pca13 * ghk ( _threadargscomma_ v , cai , cao ) ;
   ica = ical12 + ical13 ;
   }
 _current += ica;

} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  cai = _ion_cai;
  cao = _ion_cao;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dica;
  _dica = ica;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicadv += (_dica - ica)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ica += ica ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  cai = _ion_cai;
  cao = _ion_cao;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(m12) - _p;  _dlist1[0] = &(Dm12) - _p;
 _slist1[1] = &(h12) - _p;  _dlist1[1] = &(Dh12) - _p;
 _slist1[2] = &(m13) - _p;  _dlist1[2] = &(Dm13) - _p;
 _slist1[3] = &(h13) - _p;  _dlist1[3] = &(Dh13) - _p;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "CaL.mod";
static const char* nmodl_file_text = 
  "COMMENT\n"
  "\n"
  "cal.mod\n"
  "\n"
  "L-type calcium channel isoforms 1.2 & 1.3 with GHK permeability\n"
  "\n"
  "based on Tarfa et al 2017\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "UNITS {\n"
  "	(mV) = (millivolt)\n"
  "	(mA) = (milliamp)\n"
  "	(S) = (siemens)\n"
  "	(mM) = (milli/liter)\n"
  "}\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX cal\n"
  "	USEION ca READ cai, cao WRITE ica\n"
  "	RANGE pbar12, pbar13, pca12, pca13, ica, ical12, ical13\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	:FARADAY = 96520 (coul)\n"
  "	:R = 8.3134 (joule/degC)\n"
  "	FARADAY = (faraday) (coulomb)\n"
  "	R = (k-mole) (joule/degC)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	pbar12 = 0.1E-6	(m/s)\n"
  "	pbar13 = 5E-9	(m/s)\n"
  "	htau12 = 44.3	(ms)\n"
  "	htau13 = 44.3	(ms)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	m12\n"
  "	h12\n"
  "	m13\n"
  "	h13\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v	(mV)\n"
  "	celsius	(degC)\n"
  "	cai	(mM)\n"
  "	cao	(mM)\n"
  "	ica	(mA/cm2)\n"
  "	ical12	(mA/cm2)\n"
  "	ical13	(mA/cm2)\n"
  "	minf12\n"
  "	hinf12\n"
  "	mtau12	(ms)\n"
  "	minf13\n"
  "	hinf13\n"
  "	mtau13	(ms)\n"
  "	pca12	(cm/s)\n"
  "	pca13	(cm/s)\n"
  "}\n"
  "\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	pca12 = pbar12*m12*h12*(100)\n"
  "	ical12 = pca12*ghk(v, cai, cao)\n"
  "	pca13 = pbar13*m13*h13*(100)\n"
  "	ical13 = pca13*ghk(v, cai, cao)\n"
  "	ica = ical12 + ical13\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rates12(v)\n"
  "	rates13(v)\n"
  "	m12 = minf12\n"
  "	h12 = hinf12\n"
  "	m13 = minf13\n"
  "	h13 = hinf13\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "	rates12(v)\n"
  "	rates13(v)\n"
  "	m12' = (minf12 - m12)/mtau12\n"
  "	h12' = (hinf12 - h12)/htau12\n"
  "	m13' = (minf13 - m13)/mtau13\n"
  "	h13' = ((hinf13 - h13)/htau13)/0.5\n"
  "}\n"
  "\n"
  "PROCEDURE rates12( v (mV) ) {\n"
  "	LOCAL a, b\n"
  "	\n"
  "	UNITSOFF\n"
  "	a = 0.0398e6*(v + 8.124)/(exp((v + 8.124)/9.005) - 1)\n"
  "	b = 0.99e3*exp(v/31.4)\n"
  "	mtau12 = 1000/(a + b)\n"
  "	\n"
  "	minf12 = 1/(1 + exp((v + 8.9)/-6.7))\n"
  "	\n"
  "	hinf12 = 0.17*1/(1 + exp((v + 55)/8)) + 0.83\n"
  "	UNITSON\n"
  "}\n"
  "\n"
  "PROCEDURE rates13( v (mV) ) {\n"
  "	LOCAL a, b\n"
  "	\n"
  "	UNITSOFF\n"
  "	a = 39800*(v + 67.24)/(exp((v + 67.24)/15.005) - 1)\n"
  "	b = 3500*exp(v/31.4)\n"
  "	mtau13 = 1000/(a + b)/0.5\n"
  "	\n"
  "	minf13 = 1/(1 + exp((v + 40.0)/-5))\n"
  "	\n"
  "	hinf13 = 1/(1 + exp((v + 37)/5))\n"
  "	UNITSON	\n"
  "}\n"
  "\n"
  "COMMENT\n"
  "\n"
  "The following two functions are from NEURON example file cachan.mod\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "FUNCTION ghk(v(mV), ci(mM), co(mM)) (.001 coul/cm3) {\n"
  "	LOCAL z, eci, eco\n"
  "	z = (1e-3)*2*FARADAY*v/(R*(celsius+273.15))\n"
  "	eco = co*efun(z)\n"
  "	eci = ci*efun(-z)\n"
  "	:high cao charge moves inward\n"
  "	:negative potential charge moves inward\n"
  "	ghk = (.001)*2*FARADAY*(eci - eco)\n"
  "}\n"
  "\n"
  "FUNCTION efun(z) {\n"
  "	if (fabs(z) < 1e-4) {\n"
  "		efun = 1 - z/2\n"
  "	}else{\n"
  "		efun = z/(exp(z) - 1)\n"
  "	}\n"
  "}\n"
  ;
#endif
