#include <stdio.h>
#include <x86intrin.h>
#include<stdlib.h>
#include <time.h>
#define M 100000
int main()
{
	float __attribute__((aligned(32))) a[M];
	int s,s0,s1,s2,s3,s4;
	srand((unsigned)time(NULL));
	for (int i = 0; i < M; i++)
    {
        a[i] = rand() % 100+ 1;
    }
    clock_t start,stop;
    double duration;
    __m128 m=_mm_setzero_ps();
    __m128 A;
    start = clock();
    for(int j=0;j<M;j++){
    for(int i=0; i<M; i++)  
    {  
        s0 += a[i];  
    }}
    stop = clock();
    /*start = clock();
    for(int j=0;j<M;j++){
    for(int i=0;i<M;i+=4)
    {
    	A=_mm_load_ps(a+i);
    	m=_mm_add_ps(m,A);
	}
	const float *q=(const float*)&m;
	s=q[0]+q[1]+q[2]+q[3];
    }
	stop = clock();*/
	duration = ((double)(stop-start))/CLK_TCK;
	printf("%f ",duration);
    return 0;
}

