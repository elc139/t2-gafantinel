#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

typedef struct 
 {
   double *a;
   double *b;
   // double c; 
   int wsize;
   int repeat; 
 } dotdata_t;

// Variaveis globais, acessiveis por todas threads
dotdata_t dotdata;
double c;

/*
 * Funcao executada por uma thread
 */
void dotprod_worker(int number_of_threads)
{
   omp_set_num_threads(number_of_threads);
   long offset;
   #pragma omp parallel for reduction (+: c)
   for (offset=0;offset<number_of_threads;offset++) {
      int i, k;
      // long offset = (long) arg;
      double *a = dotdata.a;
      double *b = dotdata.b;     
      int wsize = dotdata.wsize;
      int start = offset*wsize;
      int end = start + wsize;
      double mysum = 0.0;

      for (k = 0; k < dotdata.repeat; k++) {
         mysum = 0.0;
         for (i = start; i < end ; i++)  {
            mysum += (a[i] * b[i]);
         }
      }

      c += mysum;
   }

}
/*
 * Tempo (wallclock) em microssegundos
 */ 
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

/*
 * Preenche vetor
 */ 
void fill(double *a, int size, double value)
{  
   int i;
   for (i = 0; i < size; i++) {
      a[i] = value;
   }
}

/*
 * Funcao principal
 */ 
int main(int argc, char **argv)
{
   int nthreads, wsize, repeat;
   long start_time, end_time;

   if ((argc != 4)) {
      printf("Uso: %s <nthreads> <worksize> <repetitions>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   nthreads = atoi(argv[1]); 
   wsize = atoi(argv[2]);  // worksize = tamanho do vetor de cada thread
   repeat = atoi(argv[3]); // numero de repeticoes dos calculos (para aumentar carga)

   // Cria vetores
   dotdata.a = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.a, wsize*nthreads, 0.01);
   dotdata.b = (double *) malloc(wsize*nthreads*sizeof(double));
   fill(dotdata.b, wsize*nthreads, 1.0);
   dotdata.wsize = wsize;
   dotdata.repeat = repeat;
   c = 0.0;

   // Calcula c = a . b em nthreads, medindo o tempo
   start_time = wtime();
   dotprod_worker(nthreads);
   end_time = wtime();

   // Mostra resultado e estatisticas da execucao
   printf("%f\n", c);
   printf("%d thread(s), %ld usec\n", nthreads, (long) (end_time - start_time));
   fflush(stdout);

   free(dotdata.a);
   free(dotdata.b);

   return EXIT_SUCCESS;
}

