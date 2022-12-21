#include<stdio.h>
#include<x86intrin.h>
#include<stdlib.h>
#include<time.h>
#define M 4
int main()
{
	float __attribute__((aligned(16))) a[M],b[M];
    __m128 m=_mm_setzero_ps();
    __m128 C=_mm_setzero_ps();
    float s=0;
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
    	C=_mm_mul_ps(A,B);
    	m=_mm_add_ps(m,C);
	}
	//const float *q=(const float*)&m;
	//s=q[0]+q[1]+q[2]+q[3];
	m=_mm_add_ps(m,m);
	_mm_store_ps(&s,m);
    printf("%d\n",s);
    return 0;
}
