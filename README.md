
<!-- README.md is generated from README.Rmd. Please edit that file -->

# deftly

<!-- badges: start -->

![](https://img.shields.io/badge/cool-useless-green.svg)
<!-- badges: end -->

`{deftly}` is a demonstration package showing how you can use the C code
in the [`{deft}`](https://github.com/coolbutuseless/deft) package.

The [`{deft}`](https://github.com/coolbutuseless/deft) package provides
functions in C for creating and extending data.frames within C - before
handing them over for access by the user.

For any package which wants to link to the `{deft}` package.

- In `DESCRIPTION`:
  - `LinkingTo: deft`
  - `Depends: deft`
- Add `#include <deft.h>` somewhere in your code
- Use the following functions:
  - `SEXP df_create(int ncol, char **names, int *types)` - creates a
    data.frame
  - `void df_add_row(SEXP df, ...)` - adds a row to the data.frame.
    - The `...` **must** match the number and type of values expected by
      the data.frame.
  - `void df_truncate_to_data_length(df)` - the final call to prepare
    the data.frame to return to R.

## Installation

You can install from [GitHub](https://github.com/coolbutuseless/deftly)
with:

``` r
# install.package('remotes')
remotes::install_github('coolbutuseless/deft')
remotes::install_github('coolbutuseless/deftly')
```

## C code in this package

``` c
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DEMO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP deftly_benchmark_(SEXP n_) {
  
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
```

## Acknowledgements

- R Core for developing and maintaining the language.
- CRAN maintainers, for patiently shepherding packages onto CRAN and
  maintaining the repository
