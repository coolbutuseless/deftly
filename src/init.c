
#include <R.h>
#include <Rinternals.h>

extern SEXP deftly_demo_();


static const R_CallMethodDef CEntries[] = {
  {"deftly_demo_", (DL_FUNC) &deftly_demo_, 1},
  {NULL , NULL, 0}
};


void R_init_deftly(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}
