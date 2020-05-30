// OpenMp1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>


#define N 1000
#define CHUNKSIZE 2

int main()
{
	int i, chunk;
	int r1, c1, r2, c2;
	printf("please enter row 1 and col 1 and col 2\n");
	scanf("%d %d %d", &r1, &c1, &c2);
	r2 = c1;
	int* mat1 = (int*)malloc(r1*c1 * sizeof(int));
	int* mat2 = (int*)malloc(r2*c2 * sizeof(int));
	printf("please enter mat1\n");
	for (i = 0; i < r1*c1; i++)
		scanf("%d", &mat1[i]);

	printf("please enter mat2\n");
	for (i = 0; i < r2*c2; i++)
		scanf("%d", &mat2[i]);
	int* result = (int*)malloc(r1*c2 * sizeof(int));
	int* doneby = (int*)malloc(r1*c2 * sizeof(int));

	omp_set_num_threads(2);
	#pragma omp parallel shared(r1,c1,r2,c2,mat1,mat2),private(i)
	{
		int j, k;
		#pragma omp for schedule(static,1)
		for (i = 0; i < r1; i++)
		{
			for (j = 0; j < c2; j++)
			{
				result[i*c2 + j] = 0;
				doneby[i*c2 + j] = omp_get_thread_num();
				for (k = 0; k < c1; k++)
				{
					result[i*c2 + j] += mat1[i*c1 + k] * mat2[k*c2 + j];
				}
			}
		}

	}
	printf("Matrix result \n");
	for (i = 0; i < r1; i++)
	{
		int k;
		for (k = 0; k < c2; k++)
			printf("%d ", result[i*c2 + k]);
		printf("\n");
	}
	printf("Done By \n");
	for (i = 0; i < r1; i++)
	{
		int k;
		for (k = 0; k < c2; k++)
			printf("%d ", doneby[i*c2 + k]);
		printf("\n");
	}


    return 0;
}
	

/*
if (my_rank==0)
	{

	int i = 0, k = 0;
	int szOfRes = (portion / col1) * col2;
	result = malloc(szOfRes * sizeof(int));

	for (dest = 1; dest < p; i++)
	{
		MPI_Recv(result,szOfRes, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
		printf("recv from %d",dest );
		int j;
		for (i = 0; i < szOfRes; i++)
			mulmatrix[k++] = result[i];
	}
}


*/