#include "util.h"
//------------------------------------------------------------------------------
int get_errno (void) {
  return errno;
}
//------------------------------------------------------------------------------
void clr_errno (void) {
  errno = 0;
}
//------------------------------------------------------------------------------
void __attribute__ ((constructor)) initLibrary(void) {
 //
 // Function that is called when the library is loaded.
 //
}
void __attribute__ ((destructor)) termLibrary(void) {
 //
 // Function that is called when the library is closed.
 //
}
