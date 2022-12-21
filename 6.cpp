#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<x86intrin.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define NRA 256
#define NCA 256
#define NCB 256
#define M 4
#define BS 4
int main()
{
	clock_t start,stop;
    double duration;
	float __attribute__((aligned(16))) a[NRA][NCA],b[NCA][NCB],c[NRA][NCB],d[NCB][NCA],e[NRA][NCB],f[NRA][NCB];
	int i, j, k;
	__m128 A,B,C;
	for(i=0;i<NRA;i++)
    {
    	for(j=0;j<NCA;j++)
    	{
    		a[i][j]=i+j*2;
		}
	}
	for(i=0;i<NCA;i++)
    {
    	for(j=0;j<NCB;j++)
    	{
    		b[i][j]=i*2+j;
		}
	}
	for(i=0;i<NRA;i++)
    {
    	for(j=0;j<NCB;j++)
    	{
    		c[i][j]=0.0f;
		}
	}
	for(i=0;i<NRA;i++)
    {
    	for(j=0;j<NCB;j++)
    	{
    		e[i][j]=0.0f;
		}
	}
	for(int i=0;i<NCB;i++)
	{
		for(int j=0;j<NCA;j++)
		{
			d[i][j]=b[j][i];
		}
	}
	int si,sj,sk,sum;
	int en=BS*(M/BS);
	__m128 A1,B1,C1;
	/*for(si=0;si<en;si+=BS)
		for(sj=0;sj<en;sj+=BS)
			for(k=0;k<M;k++){
				for(j=sj;j<sj+BS;j++)
				{
					sum=f[k][j];
					//__m128 m1 = _mm_setzero_ps();
					for(i=si;i<si+BS;i++)
					{
						sum+=a[k][i]*b[i][j];
						//A1=_mm_load_ps(&a[k][i]);
            			//B1=_mm_load_ps(&d[j][i]);
            			//C1=_mm_mul_ps(A1,B1);
                		//m1=_mm_add_ps(m1,C1);
					}
					f[k][j]=sum;
					//f[k][j]=m1[0]+m1[1]+m1[2]+m1[3];
				}
			}
	/*for(i=0;i<NRA;i++)
    {
    	for(j=0;j<NCB;j++)
    	{
    		printf("%f ",f[i][j]);
		}
		printf("\n");
	}*/
	start = clock();
    for (i=0; i<NRA; i++)
    {
        for(j=0; j<NCB; j++)
		{	
			__m128 m = _mm_setzero_ps();
            for (k=0; k<NCA; k+=4)
            {
            	A=_mm_load_ps(&a[i][k]);
            	B=_mm_load_ps(&d[j][k]);
            	C=_mm_mul_ps(A,B);
                m=_mm_add_ps(m,C);
            }
            c[i][j]=m[0]+m[1]+m[2]+m[3];
        }
    }
    stop = clock();
    duration = ((double)(stop-start))/CLK_TCK;
	printf("%f ",duration);
    /*for(i=0;i<NRA;i++)
    {
    	for(j=0;j<NCB;j++)
    	{
    		printf("%f ",c[i][j]);
		}
		printf("\n");
	} */
    for (k=0; k<NCB; k++)
        for(i=0; i<NRA; i++)
        {
            e[i][k] = 0.0;
            for (j=0; j<NCA; j++)
                e[i][k] = e[i][k] + a[i][j] * b[j][k];
        }
	stop = clock();
    duration = ((double)(stop-start))/CLK_TCK;
	printf("%f ",duration);
   /* for(i=0;i<NRA;i++)
    {
    	for(j=0;j<NCB;j++)
    	{
    		printf("%f ",e[i][j]);
		}
		printf("\n");
	}*/
	return 0;
}
