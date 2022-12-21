#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <time.h>
void generate_vector(int n,float* & x){
    x=new float[n];
    for(int i=0;i<n;i++)
        x[i]=rand()%10+1;
}
void generate_sparse_matrix(float** & m,int N,double s){
	srand((unsigned)time(NULL));
   m=new float*[N];
   for(int i=0;i<N;i++)
    m[i]=new float[N];
   for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
      {
        int x=rand()%1000+1;
        if(x>=10000*s)
        m[i][j]=0;
        else
        m[i][j]=x+10;
      }
   return;
}
int matrix_to_coo(float **M,int N,float* &value,int* & row,int* & col){
   int i,j;
   int a=0;
   for(i=0;i<N;i++)
      for(j=0;j<N;j++)
          if(M[i][j]!=0)
              a++;
   value=new float[a];
   col=new int[a];
   row=new int[a];
   int k=0;
   for(i=0;i<N;i++)
   {
      for(j=0;j<N;j++)
      {
          if(M[i][j]!=0)
          {
              row[k]=i;
              col[k]=j;
              value[k++]=M[i][j];
          }
      }
   }
   return a;
}
int main(){
	int N=2000;
	int nonzero=0;
	float *value=NULL;
	int *col=NULL;
	int *row=NULL;
	double s=0.005;
	float **mat=NULL;
	float y[N]={0.00000};
	float *vec=NULL;
	generate_vector(N,vec);
	generate_sparse_matrix(mat,N,s);
    nonzero=matrix_to_coo(mat,N,value,row,col);
    clock_t start,stop;
    double duration;
    __m128 A,B,C;
    start = clock();
    for(int j=0;j<N;j++){
    	//__m128 m = _mm_setzero_ps();
    for(int i=0;i<nonzero;i++){
    	//A=_mm_loadu_ps(vec+col[i]);
    	//B=_mm_loadu_ps(value+i);
    	//C=_mm_mul_ps(A,B);
    	//m=_mm_add_ps(m,C);
    	//y[row[i]]=m[0]+m[1]+m[2]+m[3];
    	y[row[i]] += value[i] * vec[col[i]];
    }}
    stop = clock();
    duration = ((double)(stop-start))/CLK_TCK;
	printf("%f ",duration);
    return 0;
}


