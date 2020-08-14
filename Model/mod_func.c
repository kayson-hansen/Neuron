#include <stdio.h>
#include "hocdec.h"
#define IMPORT extern __declspec(dllimport)
IMPORT int nrnmpi_myid, nrn_nobanner_;

extern void _BK_reg();
extern void _CaL_reg();
extern void _CaN_reg();
extern void _CaR_reg();
extern void _CaT_reg();
extern void _Capmp_reg();
extern void _Ih_reg();
extern void _Ka_reg();
extern void _Kdr_reg();
extern void _Naf_reg();
extern void _Nal_reg();
extern void _Nap_reg();
extern void _SK_reg();
extern void _leak_reg();

void modl_reg(){
	//nrn_mswindll_stdio(stdin, stdout, stderr);
    if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
	fprintf(stderr, "Additional mechanisms from files\n");

fprintf(stderr," BK.mod");
fprintf(stderr," CaL.mod");
fprintf(stderr," CaN.mod");
fprintf(stderr," CaR.mod");
fprintf(stderr," CaT.mod");
fprintf(stderr," Capmp.mod");
fprintf(stderr," Ih.mod");
fprintf(stderr," Ka.mod");
fprintf(stderr," Kdr.mod");
fprintf(stderr," Naf.mod");
fprintf(stderr," Nal.mod");
fprintf(stderr," Nap.mod");
fprintf(stderr," SK.mod");
fprintf(stderr," leak.mod");
fprintf(stderr, "\n");
    }
_BK_reg();
_CaL_reg();
_CaN_reg();
_CaR_reg();
_CaT_reg();
_Capmp_reg();
_Ih_reg();
_Ka_reg();
_Kdr_reg();
_Naf_reg();
_Nal_reg();
_Nap_reg();
_SK_reg();
_leak_reg();
}
