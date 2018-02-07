/*
  CEC14 Test Function Suite for Single Objective Optimization
  Jane Jing Liang (email: liangjing@zzu.edu.cn; liangjing@pmail.ntu.edu.cn) 
  Dec. 12th 2013
*/

//#include <WINDOWS.H>
#include <stdio.h>
#include <math.h>
#include <malloc.h>


void cec14_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int main()
{
	int i,j,k,n,m,func_num;
	double *f,*x,*y;
	FILE *fpt;
	char FileName[30];
	m=10;
	n=10;

	x=(double *)malloc(m*n*sizeof(double));
	y=(double *)malloc(m*n*sizeof(double));
	f=(double *)malloc(sizeof(double)  *  m);
	for (i = 0; i < 1; i++)
	{
		func_num=i+1;
		sprintf(FileName, "input_data/shift_data_%d.txt", func_num);
		fpt = fopen(FileName,"r");
		if (fpt==NULL)
		{
			printf("\n Error: Cannot open input file for reading \n");
		}
		
		if (x==NULL)
			printf("\nError: there is insufficient memory available!\n");

		for(k=0;k<n*m;k++)
		{
            fscanf(fpt,"%lf",&x[k]);
            y[k] = 0.0;

            printf("%f\n",y[k]);
		}

		fclose(fpt);

        for (j = 0; j < n; j++)
        {
            x[1*n+j]=0.0;
            printf("%lf\n",x[1*n+j]);
        }

		for (k = 0; k < 1; k++)
		{
			cec14_test_func(y, f, n,m,func_num);
			for (j = 0; j < 10; j++)
			{
				printf(" f%d(x[%d]) = %l"
							   "f,",func_num,j+1,f[j]);
			}
			printf("\n");
		}
	
	}

	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);
	return 0;
}


