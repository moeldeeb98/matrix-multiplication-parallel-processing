#include <stdio.h>
#include <stdlib.h>

void autoGenerateMatrix(int row, int col, int** matrix){
    int i,j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            matrix[i][j] = rand()%20;
        }
    }

}

void readMatrixFromUser(int row, int col, int** matrix){
    int i,j;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(int row, int col, int** matrix){
    int i,j;
    printf("\n==================================\n");
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("==================================\n");

}

int main(){

    int** mat1;
    int** mat2;
    int** mat3;
    int r1, c1, r2, c2;
    int i, j, k;

    // read the details of the first matrix
    printf("Enter the Dimention of the first Matrix\n");
    printf("Row : ");
    scanf("%d", &r1);
    printf("Col : ");
    scanf("%d", &c1);
    // build the first matrix
    mat1 = malloc(r1 * sizeof(int*));
    for(i = 0; i< r1; i++){
        mat1[i] = malloc(c1 * sizeof(int));
    }
    // read the values of the first matrix
    int status = 1;
    printf("(1) auto genertate\n");
    printf("(2) Enter the value of the matrix:\n");
    scanf("%d", &status);

    if(status == 1){
        autoGenerateMatrix(r1, c1, mat1);
    }else{
        readMatrixFromUser(r1, c1, mat1);
    }

    printMatrix(r1, c1, mat1);

//=================================================================

    // read the details of the second matrix
    printf("Enter the Dimention of the Second Matrix\n");
    printf("Row : ");
    scanf("%d", &r2);
    printf("Col : ");
    scanf("%d", &c2);

    if(c1 != r2){
        printf("incompatible Matrices\n");
        return 0;
    }
    // build the second matrix
    mat2 = malloc(r2 * sizeof(int*));
    for(i = 0; i< r2; i++){
        mat2[i] = malloc(c2 * sizeof(int));
    }
    // read the values of the second matrix
    printf("(1) auto genertate\n");
    printf("(2) Enter the value of the matrix:\n");
    scanf("%d", &status);

    if(status == 1){
        autoGenerateMatrix(r2, c2, mat2);
    }else{
        readMatrixFromUser(r2, c2, mat2);
    }

    printMatrix(r2, c2, mat2);
//======================================================================

    // build the result matrix
    mat3 = malloc(r1 * sizeof(int*));
    for(i = 0; i< r1; i++){
        mat3[i] = malloc(c2 * sizeof(int));
    }
    
    // multiplication process
    for(i = 0; i < r1; i++){
        for(j = 0; j < c2; j++){
            mat3[i][j] = 0;
            for(k = 0; k < c1; k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    // print the result matrix
    printf("\nThe Result Matrix\n");
    printMatrix(r1, c2, mat3);
 
    return 0;
}