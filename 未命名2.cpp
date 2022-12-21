#include <stdio.h>
#include <x86intrin.h>
#include<stdlib.h>
#include <time.h>
#define M 1000
int main()
{
	float __attribute__((aligned(16))) a[M];
	int s1,s2;
	int W=M%16;
	int w=M-W;
    __m128 m1=_mm_setzero_ps();
    __m128 m2=_mm_setzero_ps();
    __m128 m3=_mm_setzero_ps();
    __m128 m4=_mm_setzero_ps();
	srand((unsigned)time(NULL));
	for (int i = 0; i < M; i++)
    {
        a[i] = rand() % 10+ 1;
    }
    __m128 A1,A2,A3,A4;
    for(int i=0;i< M;i++)
        printf("%f ",a[i]);
    printf("\n");
    for(int i=0; i<M; i++)  
    {  
        s1 += a[i];  
    }
    printf("%d\n",s1);
    for(int i=0;i<w;i+=16)
    {
    	A1=_mm_load_ps(a+i);
    	A2=_mm_load_ps(a+i+4);
    	A3=_mm_load_ps(a+i+8);
    	A4=_mm_load_ps(a+i+12);
    	m1=_mm_add_ps(m1,A1);
    	m2=_mm_add_ps(m2,A2);
    	m3=_mm_add_ps(m3,A3);
    	m4=_mm_add_ps(m4,A4);
	}
	m1=_mm_add_ps(m1,m2);
	m3=_mm_add_ps(m3,m4);
	m1=_mm_add_ps(m1,m3);
	const float *q=(const float*)&m1;
	s2=q[0]+q[1]+q[2]+q[3];
	for(int i=w;i<M;i++)
	{
		s2+=a[i];
	}
	printf("%d ",s2);
    return 0;
}
