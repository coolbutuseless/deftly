


#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <deft.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DEMO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP deftly_demo_(SEXP n_) {
  
  int nprotect = 0;
  int n;
  
  n = asInteger(n_);
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Create dataframe
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  char *names[5] = {    "x",    "y",    "z",  "lgl", "list"};
  int   types[5] = {REALSXP, INTSXP, STRSXP, LGLSXP, VECSXP};
  SEXP df = PROTECT(df_create(5, names, types));  nprotect++;
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Add values
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  for (int i = 0; i < n; i++) {
    // It is the caller's responsibility to ensure that the number and type
    // of the values passed to 'dv_add_row' are correct
    //
    //              double  , integer, char*, integer, SEXP
    df_add_row(df, (double)i, i, names[1], i % 2, ScalarInteger(i));
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Truncate to data length just prior to returning to R
  // This function *MUST* be called on any data.frame created by this code.
  // This function:
  //    * Trims the data to the actual data length
  //    * Sets the GROWABLE bit to indicate that it has been truncated
  //    * sets rownames (without which R will complain very very loudly
  //        that the data.frame is corrupt)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  df_truncate_to_data_length(df);
  
  
  UNPROTECT(nprotect);
  return df;
}


