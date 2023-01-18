#include <string.h>
#include <unistd.h>
#include <libmemcached/memcached.h>
#include <R.h>


void basic(int *n){

  int i;

  for (i=0; i < *n; i++) {
    Rprintf("Hellow world!\n");
  }

}
