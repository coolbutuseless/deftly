
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Create a data.frame in C using the \code{deft} package
#' 
#' @param n number of rows to return in the demo data.frame
#' @return data.frame created in C and returned to R
#' 
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
deftly_demo <- function(n = 8) {
  .Call(deftly_demo_, n)
}
