#ifndef RECURSIVOS
#define RECURSIVOS

//#include <thread>
#include <iostream>
#include "comunes.hpp"
//#include <vector>
#include <omp.h>

int n_base = (1 << 5);

// ------------------------------------------
// Basic Functions:
// ------------------------------------------

void submat(int** A, int** B, int n, int n_row, int n_col){
	for (int i = 0; i < n; i++) 
		B[i] = &A[n_row+i][n_col];
}

int **mat_sum(int** A, int** B, int** C, int n){
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}

int **mat_sub(int** A, int** B, int** C, int n){
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}

// ------------------------------------------
// Recursive Multiplication Functions:
// ------------------------------------------

void traditional_mult(int** A, int** B, int** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    // if (n==2){
    //     C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    //     C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    //     C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
    //     C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
    //     return;
    // }

    if (n==n_base){
        base_mult(A, B, C, n);
        return;
    }

    int **A_11 = new int*[n/2];
    int **A_12 = new int*[n/2];
    int **A_21 = new int*[n/2];
    int **A_22 = new int*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    int **B_11 = new int*[n/2];
    int **B_12 = new int*[n/2];
    int **B_21 = new int*[n/2];
    int **B_22 = new int*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    int **C_11 = new int*[n/2];
    int **C_12 = new int*[n/2];
    int **C_21 = new int*[n/2];
    int **C_22 = new int*[n/2];

    submat(C, C_11, n/2, 0, 0);
    submat(C, C_12, n/2, 0, n/2);
    submat(C, C_21, n/2, n/2, 0);
    submat(C, C_22, n/2, n/2, n/2);

    int **Aux_1 = empty_mat(n/2);
    int **Aux_2 = empty_mat(n/2);


    traditional_mult(A_11, B_11, Aux_1, n/2);
    traditional_mult(A_12, B_21, Aux_2, n/2);
    mat_sum(Aux_1, Aux_2, C_11, n/2);

    traditional_mult(A_11, B_12, Aux_1, n/2);
    traditional_mult(A_12, B_22, Aux_2, n/2);
    mat_sum(Aux_1, Aux_2, C_12, n/2);

    traditional_mult(A_21, B_11, Aux_1, n/2);
    traditional_mult(A_22, B_21, Aux_2, n/2);
    mat_sum(Aux_1, Aux_2, C_21, n/2);

    traditional_mult(A_21, B_12, Aux_1, n/2);
    traditional_mult(A_22, B_22, Aux_2, n/2);
    mat_sum(Aux_1, Aux_2, C_22, n/2);

    delete[] A_11;
    delete[] A_12;
    delete[] A_21;
    delete[] A_22;

    delete[] B_11;
    delete[] B_12;
    delete[] B_21;
    delete[] B_22;

    delete[] C_11;
    delete[] C_12;
    delete[] C_21;
    delete[] C_22;

    for (int i=0; i<n/2; i++){
        delete Aux_1[i];
        delete Aux_2[i];
    }
}


void strassen_mult(int** A, int** B, int** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    // if (n==2){
    //     C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    //     C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    //     C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
    //     C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
    //     return;
    // }

    if (n==n_base){
        base_mult(A, B, C, n);
        return;
    }

    int **A_11 = new int*[n/2];
    int **A_12 = new int*[n/2];
    int **A_21 = new int*[n/2];
    int **A_22 = new int*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    int **B_11 = new int*[n/2];
    int **B_12 = new int*[n/2];
    int **B_21 = new int*[n/2];
    int **B_22 = new int*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    int **M_1 = empty_mat(n/2);
    int **M_2 = empty_mat(n/2);
    int **M_3 = empty_mat(n/2);
    int **M_4 = empty_mat(n/2);
    int **M_5 = empty_mat(n/2);
    int **M_6 = empty_mat(n/2);
    int **M_7 = empty_mat(n/2);

    int **Aux_1 = empty_mat(n/2);
    int **Aux_2 = empty_mat(n/2);


    // M1 = (A11 + A22)*(B11 + B22)
    mat_sum(A_11, A_22, Aux_1, n/2);
    mat_sum(B_11, B_22, Aux_2, n/2);
    strassen_mult(Aux_1, Aux_2, M_1, n/2);

    //M2 = (A21 + A22)*B11
    mat_sum(A_21, A_22, Aux_1, n/2);
    strassen_mult(Aux_1, B_11, M_2, n/2);

    //M3 = A11*(B12 - B22)
    mat_sub(B_12, B_22, Aux_1, n/2);
    strassen_mult(A_11, Aux_1, M_3, n/2);

    //M4 = A22*(B21 - B11)
    mat_sub(B_21, B_11, Aux_1, n/2);
    strassen_mult(A_22, Aux_1, M_4, n/2);

    //M5 = (A11 + A12)*B22
    mat_sum(A_11, A_12, Aux_1, n/2);
    strassen_mult(Aux_1, B_22, M_5, n/2);

    //M6 = (A21 - A11)*(B11 + B12)
    mat_sub(A_21, A_11, Aux_1, n/2);
    mat_sum(B_11, B_12, Aux_2, n/2);
    strassen_mult(Aux_1, Aux_2, M_6, n/2);

    //M7 = (A12 - A22)*(B21 + B22)
    mat_sub(A_12, A_22, Aux_1, n/2);
    mat_sum(B_21, B_22, Aux_2, n/2);
    strassen_mult(Aux_1, Aux_2, M_7, n/2);

    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            C[i][j] = M_1[i][j] + M_4[i][j] - M_5[i][j] + M_7[i][j];
            C[i][j+n/2] = M_3[i][j] + M_5[i][j];
            C[i+n/2][j] = M_2[i][j] + M_4[i][j];
            C[i+n/2][j+n/2] = M_1[i][j] - M_2[i][j] + M_3[i][j] + M_6[i][j];
        }
    }

    delete[] A_11;
    delete[] A_12;
    delete[] A_21;
    delete[] A_22;

    delete[] B_11;
    delete[] B_12;
    delete[] B_21;
    delete[] B_22;

    for (int i=0; i<n/2; i++){
        delete M_1[i];
        delete M_2[i];
        delete M_3[i];
        delete M_4[i];
        delete M_5[i];
        delete M_6[i];
        delete M_7[i];

        delete Aux_1[i];
        delete Aux_2[i];
    }
}


// void strassen_par_mult(int** A, int** B, int** C, int n){
//     // Matriz A, B y C de nxn
//     // con n potencia de 2.

//     if (n==2){
//         C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
//         C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
//         C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
//         C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
//         return;
//     }

//     int **A_11 = submat_upper_left(A, n);
//     int **A_12 = submat_upper_right(A, n);
//     int **A_21 = submat_lower_left(A, n);
//     int **A_22 = submat_lower_right(A, n);

//     int **B_11 = submat_upper_left(B, n);
//     int **B_12 = submat_upper_right(B, n);
//     int **B_21 = submat_lower_left(B, n);
//     int **B_22 = submat_lower_right(B, n);

//     int **M_1 = empty_mat(n/2);
//     int **M_2 = empty_mat(n/2);
//     int **M_3 = empty_mat(n/2);
//     int **M_4 = empty_mat(n/2);
//     int **M_5 = empty_mat(n/2);
//     int **M_6 = empty_mat(n/2);
//     int **M_7 = empty_mat(n/2);

//     int **Aux_1 = empty_mat(n/2);
//     int **Aux_2 = empty_mat(n/2);

// #pragma omp task
//     {
//     // M1 = (A11 + A22)*(B11 + B22)
//     mat_sum(A_11, A_22, Aux_1, n/2);
//     mat_sum(B_11, B_22, Aux_2, n/2);
//     strassen_mult(Aux_1, Aux_2, M_1, n/2);
//     }
// #pragma omp task
//     {
//     //M2 = (A21 + A22)*B11
//     mat_sum(A_21, A_22, Aux_1, n/2);
//     strassen_mult(Aux_1, B_11, M_2, n/2);
//     }
// #pragma omp task
//     {
//     //M3 = A11*(B12 - B22)
//     mat_sub(B_12, B_22, Aux_1, n/2);
//     strassen_mult(A_11, Aux_1, M_3, n/2);
//     }
// #pragma omp task
//     {
//     //M4 = A22*(B21 - B11)
//     mat_sub(B_21, B_11, Aux_1, n/2);
//     strassen_mult(A_22, Aux_1, M_4, n/2);
//     }
// #pragma omp task
//     {
//     //M5 = (A11 + A12)*B22
//     mat_sum(A_11, A_12, Aux_1, n/2);
//     strassen_mult(Aux_1, B_22, M_5, n/2);
//     }
// #pragma omp task
//     {
//     //M6 = (A21 - A11)*(B11 + B12)
//     mat_sub(A_21, A_11, Aux_1, n/2);
//     mat_sum(B_11, B_12, Aux_2, n/2);
//     strassen_mult(Aux_1, Aux_2, M_6, n/2);
//     }
// #pragma omp task
//     {
//     //M7 = (A12 - A22)*(B21 + B22)
//     mat_sub(A_12, A_22, Aux_1, n/2);
//     mat_sum(B_21, B_22, Aux_2, n/2);
//     strassen_mult(Aux_1, Aux_2, M_7, n/2);
//     }

//     for(int i=0; i<n/2; i++){
//         for(int j=0; j<n/2; j++){
//             C[i][j] = M_1[i][j] + M_4[i][j] - M_5[i][j] + M_7[i][j];
//             C[i][j+n/2] = M_3[i][j] + M_5[i][j];
//             C[i+n/2][j] = M_2[i][j] + M_4[i][j];
//             C[i+n/2][j+n/2] = M_1[i][j] - M_2[i][j] + M_3[i][j] + M_6[i][j];
//         }
//     }

//     for (int i=0; i<n/2; i++){
//         delete A_11[i];
//         delete A_12[i];
//         delete A_21[i];
//         delete A_22[i];
//         delete B_11[i];
//         delete B_12[i];
//         delete B_21[i];
//         delete B_22[i];

//         delete M_1[i];
//         delete M_2[i];
//         delete M_3[i];
//         delete M_4[i];
//         delete M_5[i];
//         delete M_6[i];
//         delete M_7[i];

//         delete Aux_1[i];
//         delete Aux_2[i];
//     }
// }


/*
void strassen_mult(int** A, int** B, int** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==2){
        C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
        C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
        C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
        C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
        return;
    }

    int **A_11 = submat_upper_left(A, n);
    int **A_12 = submat_upper_right(A, n);
    int **A_21 = submat_lower_left(A, n);
    int **A_22 = submat_lower_right(A, n);

    int **B_11 = submat_upper_left(B, n);
    int **B_12 = submat_upper_right(B, n);
    int **B_21 = submat_lower_left(B, n);
    int **B_22 = submat_lower_right(B, n);

    int **M_1 = empty_mat(n/2);
    int **M_2 = empty_mat(n/2);
    int **M_3 = empty_mat(n/2);
    int **M_4 = empty_mat(n/2);
    int **M_5 = empty_mat(n/2);
    int **M_6 = empty_mat(n/2);
    int **M_7 = empty_mat(n/2);

    int **Aux_1 = empty_mat(n/2);
    int **Aux_2 = empty_mat(n/2);


    // M1 = (A11 + A22)*(B11 + B22)
    mat_sum(A_11, A_22, Aux_1, n/2);
    mat_sum(B_11, B_22, Aux_2, n/2);
    strassen_mult(Aux_1, Aux_2, M_1, n/2);

    //M2 = (A21 + A22)*B11
    mat_sum(A_21, A_22, Aux_1, n/2);
    strassen_mult(Aux_1, B_11, M_2, n/2);

    //M3 = A11*(B12 - B22)
    mat_sub(B_12, B_22, Aux_1, n/2);
    strassen_mult(A_11, Aux_1, M_3, n/2);

    //M4 = A22*(B21 - B11)
    mat_sub(B_21, B_11, Aux_1, n/2);
    strassen_mult(A_22, Aux_1, M_4, n/2);

    //M5 = (A11 + A12)*B22
    mat_sum(A_11, A_12, Aux_1, n/2);
    strassen_mult(Aux_1, B_22, M_5, n/2);

    //M6 = (A21 - A11)*(B11 + B12)
    mat_sub(A_21, A_11, Aux_1, n/2);
    mat_sum(B_11, B_12, Aux_2, n/2);
    strassen_mult(Aux_1, Aux_2, M_6, n/2);

    //M7 = (A12 - A22)*(B21 + B22)
    mat_sub(A_12, A_22, Aux_1, n/2);
    mat_sum(B_21, B_22, Aux_2, n/2);
    strassen_mult(Aux_1, Aux_2, M_7, n/2);

    for(int i=0; i<n/2; i++){
        for(int j=0; j<n/2; j++){
            C[i][j] = M_1[i][j] + M_4[i][j] - M_5[i][j] + M_7[i][j];
            C[i][j+n/2] = M_3[i][j] + M_5[i][j];
            C[i+n/2][j] = M_2[i][j] + M_4[i][j];
            C[i+n/2][j+n/2] = M_1[i][j] - M_2[i][j] + M_3[i][j] + M_6[i][j];
        }
    }

    for (int i=0; i<n/2; i++){
        delete A_11[i];
        delete A_12[i];
        delete A_21[i];
        delete A_22[i];
        delete B_11[i];
        delete B_12[i];
        delete B_21[i];
        delete B_22[i];

        delete M_1[i];
        delete M_2[i];
        delete M_3[i];
        delete M_4[i];
        delete M_5[i];
        delete M_6[i];
        delete M_7[i];

        delete Aux_1[i];
        delete Aux_2[i];
    }
}
*/

#endif