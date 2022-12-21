#include<x86intrin.h>
const char* dgemm_desc = "blocked 2 dgemm.";
#define BLOCK_SIZE 112
#define DOUBLE_PER_AVX 4
#define UNROLL 4
#define min(a,b) (((a)<(b))?(a):(b))
static void do_block (int lda, int I, int J, int K, double* A, double* B, double* C){
 int t = J - J%(DOUBLE_PER_AVX*UNROLL);

 for(int j=0; j<t; j+=DOUBLE_PER_AVX*UNROLL){
     for(int i=0; i<I; ++i){
         __m256d cij[UNROLL];
         for(int x=0; x<UNROLL; ++x){
             cij[x] = _mm256_load_pd(C+i*lda+j+DOUBLE_PER_AVX*x);
            }
         for(int k=0; k<K; ++k){
             __m256d a = _mm256_broadcastsd_pd(_mm_loaddup_pd(A+i*lda+k));
             for(int x=0; x<UNROLL; ++x){
             cij[x] = _mm256_add_pd(cij[x], _mm256_mul_pd(_mm256_load_pd(B+k*lda+j+DOUBLE_PER_AVX*x), a));
                }
            }
         for(int x=0; x<UNROLL; ++x){
             _mm256_store_pd(C+i*lda+j+DOUBLE_PER_AVX*x, cij[x]);
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
void square_dgemm (int lda, double* B, double* A, double* C){
 for (int i = 0; i < lda; i += BLOCK_SIZE){
   for (int j = 0; j < lda; j += BLOCK_SIZE){
     for (int k = 0; k < lda; k += BLOCK_SIZE){
       int I = min (BLOCK_SIZE, lda-i);
       int J = min (BLOCK_SIZE, lda-j);
       int K = min (BLOCK_SIZE, lda-k);
       do_block(lda, I, J, K, A + i*lda + k, B + k*lda + j, C + i*lda + j);
            }
        }
    }
}
