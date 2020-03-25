#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) 
{
  // #pragma omp parallel
  int nthreads = atoi(argv[1]);
  omp_set_num_threads(nthreads);
  printf("%i\n",nthreads);
  return 0;
}

