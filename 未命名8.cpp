#include<stdio.h>
#include<stdlib.h>
#include<x86intrin.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define W 1024
#define BLOCK_SI 32
#define BLOCK_SJ 32
#define BLOCK_SK 32
static void do_block (int lda, int I, int J, int K, double* A, double* B, double* C)
{
	
	int t=J-J%(4*UNROLL);
    for (int j = 0; j < t; j+=4*UNROLL){
    for (int i = 0; i < I; ++i) 
    {
      __m256d cij[UNROLL];
      for (int x = 0; x < UNROLL; ++x)
      {
      	cij[x]=_mm256_load_pd(C+i*lda+j+4*x);
      }
      for(int k=0;k<K;++k)
      {
      	__m256d a=_mm256_broadcastsd_pd(_mm_load_pd(A+i*lda+k));
      	for(int x=0;x<UNROLL;++x)
      	{
      		cij[x]=_mm256_add_pd(cij[x],_mm256_mul_pd(_mm256_load_pd(B+k*lda+j+4*x),a));
		}
	}
	for(int x=0;x<UNROLL;++x)
	{
		_mm256_store_pd(C+i*lda+j+4*x,cij[x]);
	}
    }
    }
    for(int i=0; i<I; ++i){
 	for(int k=0; k<K; ++k){
    for(int j=t;j<J;++j){
    C[i*lda+j] += A[i*lda+k] * B[k*lda+j];
            }
        }
    }
}
void square_dgemm (int lda, double* A, double* B, double* C)
{
  for (int i = 0; i < lda; i += BLOCK_SIZE)
    for (int j = 0; j < lda; j += BLOCK_SIZE)
      for (int k = 0; k < lda; k += BLOCK_SIZE)
      {
	int M = min (BLOCK_SI, lda-i);
	int N = min (BLOCK_SJ, lda-j);
	int K = min (BLOCK_SK, lda-k);

	do_block(lda, M, N, K, A + k + i*lda, B + j + k*lda, C + j + i*lda);
      }
}
int main()
{
	double* __attribute__ ((aligned (32))) buf = NULL;
    buf = (double*) malloc (3 * W * W * sizeof(double));
    double* A = buf + 0;
    double* B = A + W*W;
    double* C = B + W*W;
    for(int i=0,j=W*W;i<W*W;i++,j++)
    {
    	A[i]=i+j*2;
	}
	for(int i=0,j=W*W;i<W*W;i++,j++)
    {
    	B[i]=i+j*2;
	}
	for(int i=0,j=W*W;i<W*W;i++,j++)
    {
    	C[i]=0.0f;
	}
    square_dgemm (W, A, B, C);
    for(int i=0;i<W;i++)
    {
    	for(int j=0;j<W;j++)
    	{
    		printf("%f ",C[i*W+j]);
		}
		printf("\n");
	}
    return 0;
}
