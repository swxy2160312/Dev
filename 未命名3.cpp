#include<stdio.h>
#include<x86intrin.h>
#include<stdlib.h>
#include<time.h>
#define M 100
int main()
{
	float __attribute__((aligned(16))) a[M],b[M],C[M];
    __m128 m=_mm_setzero_ps();
	srand((unsigned)time(NULL));
	for (int i = 0; i < M; i++)
    {
        a[i] = rand() % 1000+ 1;
    }
    for (int i = 0; i < M; i++)
    {
        b[i] = rand() % 1000+ 1;
    }
    __m128 A;
    __m128 B;
    for(int i=0;i< M;i++)
        printf("%f ",a[i]);
    printf("\n");
    for(int i=0;i< M;i++)
        printf("%f ",b[i]);
    printf("\n");
    for(int i=0;i<=M;i+=4)
    {
    	A=_mm_load_ps(a+i);
    	B=_mm_load_ps(b+i);
    	m=_mm_mul_ps(A,B);
    	_mm_store_ps(C+i,m);
	}

    for(int i=0;i<M;i++)
        printf("%f ",C[i]);
    printf("\n");
    return 0;
}

