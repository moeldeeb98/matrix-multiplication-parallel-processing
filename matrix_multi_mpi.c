#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc , char * argv[])
{ 
	int rows1 , col1 , rows2 ,col2,i ,j,k,fromWhere ,part_sum;
	int *Mat1;
	int *Mat2;
	int *Mat3;
	int *part_Mat;
	int numberForEachProcess;
	int remiderFrom;
	int my_rank;		
	int p;			
	int source;		
	int dest;		
	int tag = 0;
	MPI_Status status;	

	MPI_Init( &argc , &argv );

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if( my_rank != 0)
	{
		//printf("hello from fucken process %d",my_rank);
		
		source=0;
		MPI_Recv( &numberForEachProcess,1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );//recv the # of rows for first-sub matrix
		MPI_Recv( &rows2,1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );//recv the cols for first matrix and rows for 2nd matrix. bec (rows2==col1)
		MPI_Recv( &col2,1, MPI_INT, source, tag, MPI_COMM_WORLD, &status );//recv the cols for the 2nd matrix
		//printf("\nRows for first partial Matrix 1 from process %d : %d \n" ,my_rank,numberForEachProcess);
		//printf("Rows for the 2nd matrix from process %d : %d \n",my_rank,rows2);
		//printf("cols for the 2nd matrix from process %d : %d \n",my_rank,col2);
		//////////////////create dynamic 3 matrices and init them with Zero////////////////
		Mat1 = (int*)malloc((numberForEachProcess * rows2)* sizeof(int));
		for (i=0 ;i < numberForEachProcess ;i++){
			for(j=0;j<rows2;j++)
			{
				Mat1[(i* rows2)+j]=0;	///////////sub-first-matrix	
			}
		}
		Mat2 = (int* )malloc((rows2 * col2) * sizeof(int));
		for (i=0 ;i < rows2 ;i++){
			for(j=0;j<col2;j++)
			{
				Mat2[(i* col2)+j]=0;   //////////second-matrix
			}
		}
		Mat3 = (int* )malloc((numberForEachProcess * col2) * sizeof(int));
		for (i=0 ;i < numberForEachProcess ;i++){
			for(j=0;j<col2;j++)
			{
				Mat3[(i* col2)+j]=0;  ///////////thired Matrix (will allocate result in it)
			}
		}
		///////////////recv sub-first-matrix and the whole 2nd matrix from the Master///////
		MPI_Recv( Mat1,numberForEachProcess*rows2, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		MPI_Recv( Mat2,rows2*col2, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
		//////////////calculate partial matrix mutliplucation//////////////////////////////
		part_sum=0;
		for (i = 0; i < numberForEachProcess; i++) {
		  for (j = 0; j < col2; j++) {
			for (k = 0; k < rows2; k++) {
			  part_sum = part_sum + Mat1[(i* rows2)+k]*Mat2[(k*col2)+j];
			}
			Mat3[(i*col2)+j] = part_sum;
			part_sum = 0;
		  }
		}
		//////////////send the output from the slave to the mastar/////////////////////////
		dest=0;
		MPI_Send( Mat3, numberForEachProcess*col2, MPI_INT, dest, tag, MPI_COMM_WORLD);
		
		/*
		for(i=0;i< numberForEachProcess;i++){
			for(j=0;j<rows2;j++)
			{
				printf("%d ",Mat1[(i* rows2)+j]);
			}
			printf("\n");
		}
		printf("Mat2 from proccess %d \n",my_rank);
		for(i=0;i< rows2;i++){
			for(j=0;j<col2;j++)
			{
				printf("%d ",Mat2[(i* col2)+j]);
			}
			printf("\n");
		}
		
		printf("res Mat 3 from proccess %d \n",my_rank);
		for(i=0;i< numberForEachProcess;i++){
			for(j=0;j<col2;j++)
			{
				printf("%d ",Mat3[(i* col2)+j]);
			}
			printf("\n");
		}*/
		
	}else
	{
		//reading the 2 matrix from user to appaly muliplication on theme
		printf("Welcome to Matrix multiplication program!\n");
		printf("Please enter dimensions of the first matrix:");
		scanf("%d %d", &rows1,&col1);
		printf("Please enter its elements:\n");
		Mat1 =(int*) malloc((rows1*col1) * sizeof(int));
		for(i=0;i< rows1;i++){
			for(j=0;j<col1;j++)
			{
				scanf("%d",&Mat1[(i* col1)+j]);
			}
		}
		
		printf("\nPlease enter dimensions of the second matrix:");
		scanf("%d %d", &rows2,&col2);
		printf("Please enter its elements:\n");
		Mat2 =(int*) malloc((rows2 * col2) * sizeof(int));
		for(i=0;i< rows2;i++){
			for(j=0;j<col2;j++)
			{
				scanf("%d",&Mat2[(i* col1)+j]);
			}
		}
		
		/*for(i=0;i< rows1;i++){
			for(j=0;j<col1;j++)
			{
				printf("%d ",Mat1[(i* col1)+j]);
			}
			printf("\n");
		}
		for(i=0;i< rows2;i++){
			for(j=0;j<col2;j++)
			{
				printf("%d ",Mat2[(i* col1)+j]);
			}
			printf("\n");
		}*/
		/////////////create result Matrix (Mat3) to put result submatrix into it////////////////////////
		Mat3 =(int*)malloc((rows1 * col2)* sizeof(int));
		////////////////////////////////////////////////////////////////////////////////////////////
		if(p>1)// mean we run it parallel
		{
			numberForEachProcess=(rows1/(p-1));
			remiderFrom=(rows1%(p-1));
			
			fromWhere=0;
			for( dest = 1; dest < p ;dest++)
			{
				MPI_Send( &numberForEachProcess, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
				MPI_Send( &rows2, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
				MPI_Send( &col2, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
				MPI_Send( &(Mat1[fromWhere]), numberForEachProcess*col1, MPI_INT, dest, tag, MPI_COMM_WORLD);//send sub-first-matrix to slaves
				MPI_Send( Mat2, rows2*col2, MPI_INT, dest, tag, MPI_COMM_WORLD);//send the second matrix to slaves
				fromWhere=fromWhere+(numberForEachProcess*col1);
			}
			fromWhere=0;
			for( source=1; source < p ;source++)
			{
				part_Mat=(int*)malloc((numberForEachProcess * col2)* sizeof(int));
				MPI_Recv( part_Mat,numberForEachProcess*col2, MPI_INT, source, tag, MPI_COMM_WORLD, &status );
				j=0;
				for(i=fromWhere;i<(fromWhere+(numberForEachProcess*col2));i++)
				{
					if(j<numberForEachProcess*col2)
					{
						Mat3[i]=part_Mat[j];
						j++;
					}
				}
				fromWhere=fromWhere+(numberForEachProcess*col2);	
			}
		}
		else if(p==1) //mean we have a sign process
		{
			remiderFrom=rows1;	//handel singel core issuse
		}
		//////////////handling the remider from the first matrix if exist/////////////////////
		part_sum=0;
		for (i = (rows1-remiderFrom); i < rows1; i++) {
		  for (j = 0; j < col2; j++) {
			for (k = 0; k < rows2; k++) {
			  part_sum = part_sum + Mat1[(i* rows2)+k]*Mat2[(k*col2)+j];
			}
			Mat3[(i*col2)+j] = part_sum;
			part_sum = 0;
		  }
		}
		///////////////Print result matrix (Mat3)////////////////////////////////////////////
		printf("res Mat 3 from proccess %d \n",my_rank);
		for(i=0;i< rows1;i++){
			for(j=0;j<col2;j++)
			{
				printf("%d ",Mat3[(i* col2)+j]);
			}
			printf("\n");
		}	
	}
	MPI_Finalize();
	return 0;
}
