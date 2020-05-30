#include <stdio.h>

int main(){

    // int** mat1, mat2, mat3;
    int r1, c1, r2, c2;

    r1 = 2;
    r2 = 3;
    c1 = 3;
    c2 = 2;
    int mat1[2][3] = {{2, 3, 1},
                    {1, 2, 0}};

    int mat2[3][2] = {{3, 1},
                    {2, 5},
                    {2, 4}};


    int mat3[2][2];

    // multiplication process
    int i, j, k, sum;
    for(i = 0; i < r1; i++){
        for(j = 0; j < c2; j++){
            mat3[i][j] = 0;
            for(k = 0; k < c1; k++){
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }


    // print the result matrix
    for(i=0; i<r1; i++){
        for(j=0; j<c2; j++){
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }

    return 0;
}