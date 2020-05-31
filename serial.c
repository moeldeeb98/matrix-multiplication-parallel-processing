#include <stdio.h>
#include <stdlib.h>

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
    printf("Enter the value of the matrix:\n");
    for(i=0; i<r1; i++){
        for(j=0; j<c1; j++){
            scanf("%d", &mat1[i][j]);
        }
    }

//=================================================================

    // read the details of the second matrix
    printf("Enter the Dimention of the Second Matrix\n");
    printf("Row : ");
    scanf("%d", &r2);
    printf("Col : ");
    scanf("%d", &c2);
    // build the second matrix
    mat2 = malloc(r2 * sizeof(int*));
    for(i = 0; i< r2; i++){
        mat2[i] = malloc(c2 * sizeof(int));
    }
    // read the values of the second matrix
    printf("Enter the value of the matrix:\n");
    for(i=0; i<r2; i++){
        for(j=0; j<c2; j++){
            scanf("%d", &mat2[i][j]);
            // printf("\n %d \n", mat2[i][j]);
        }
    }

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
    printf("\n==================================\n");
    for(i=0; i<r1; i++){
        for(j=0; j<c2; j++){
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }
    printf("==================================\n");

 
    return 0;
}