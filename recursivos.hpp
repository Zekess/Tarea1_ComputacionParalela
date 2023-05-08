#ifndef RECURSIVOS
#define RECURSIVOS

#include "comunes.hpp"

int n_base = (1 << 4);

// ------------------------------------------
// Recursive Multiplication Functions:
// ------------------------------------------

// ------------------------------------------------------------------------

void traditional_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==n_base){
        base_mult(A, B, C, n);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **C_11 = new float*[n/2];
    float **C_12 = new float*[n/2];
    float **C_21 = new float*[n/2];
    float **C_22 = new float*[n/2];

    submat(C, C_11, n/2, 0, 0);
    submat(C, C_12, n/2, 0, n/2);
    submat(C, C_21, n/2, n/2, 0);
    submat(C, C_22, n/2, n/2, n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);


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

void par_traditional_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==n_base){
        base_mult(A, B, C, n);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **C_11 = new float*[n/2];
    float **C_12 = new float*[n/2];
    float **C_21 = new float*[n/2];
    float **C_22 = new float*[n/2];

    submat(C, C_11, n/2, 0, 0);
    submat(C, C_12, n/2, 0, n/2);
    submat(C, C_21, n/2, n/2, 0);
    submat(C, C_22, n/2, n/2, n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);

    #pragma omp sections
    {
        #pragma omp section
        {
        traditional_mult(A_11, B_11, Aux_1, n/2);
        traditional_mult(A_12, B_21, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_11, n/2);
        }
        #pragma omp section
        {
        traditional_mult(A_11, B_12, Aux_1, n/2);
        traditional_mult(A_12, B_22, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_12, n/2);
        }
        #pragma omp section
        {
        traditional_mult(A_21, B_11, Aux_1, n/2);
        traditional_mult(A_22, B_21, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_21, n/2);
        }
        #pragma omp section
        {
        traditional_mult(A_21, B_12, Aux_1, n/2);
        traditional_mult(A_22, B_22, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_22, n/2);
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

    delete[] C_11;
    delete[] C_12;
    delete[] C_21;
    delete[] C_22;

    for (int i=0; i<n/2; i++){
        delete Aux_1[i];
        delete Aux_2[i];
    }
}

void strassen_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==n_base){
        base_mult(A, B, C, n);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **M_1 = empty_mat(n/2);
    float **M_2 = empty_mat(n/2);
    float **M_3 = empty_mat(n/2);
    float **M_4 = empty_mat(n/2);
    float **M_5 = empty_mat(n/2);
    float **M_6 = empty_mat(n/2);
    float **M_7 = empty_mat(n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);


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

void par_strassen_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==n_base){
        base_mult(A, B, C, n);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **M_1 = empty_mat(n/2);
    float **M_2 = empty_mat(n/2);
    float **M_3 = empty_mat(n/2);
    float **M_4 = empty_mat(n/2);
    float **M_5 = empty_mat(n/2);
    float **M_6 = empty_mat(n/2);
    float **M_7 = empty_mat(n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // M1 = (A11 + A22)*(B11 + B22)
            mat_sum(A_11, A_22, Aux_1, n/2);
            mat_sum(B_11, B_22, Aux_2, n/2);
            strassen_mult(Aux_1, Aux_2, M_1, n/2);
        }
        #pragma omp section
        {
            //M2 = (A21 + A22)*B11
            mat_sum(A_21, A_22, Aux_1, n/2);
            strassen_mult(Aux_1, B_11, M_2, n/2);
        }
        #pragma omp section
        {
            //M3 = A11*(B12 - B22)
            mat_sub(B_12, B_22, Aux_1, n/2);
            strassen_mult(A_11, Aux_1, M_3, n/2);
        }
        #pragma omp section
        {
            //M4 = A22*(B21 - B11)
            mat_sub(B_21, B_11, Aux_1, n/2);
            strassen_mult(A_22, Aux_1, M_4, n/2);
        }
        #pragma omp section
        {
            //M5 = (A11 + A12)*B22
            mat_sum(A_11, A_12, Aux_1, n/2);
            strassen_mult(Aux_1, B_22, M_5, n/2);
        }
        #pragma omp section
        {
            //M6 = (A21 - A11)*(B11 + B12)
            mat_sub(A_21, A_11, Aux_1, n/2);
            mat_sum(B_11, B_12, Aux_2, n/2);
            strassen_mult(Aux_1, Aux_2, M_6, n/2);
        }
        #pragma omp section
        {
            //M7 = (A12 - A22)*(B21 + B22)
            mat_sub(A_12, A_22, Aux_1, n/2);
            mat_sum(B_21, B_22, Aux_2, n/2);
            strassen_mult(Aux_1, Aux_2, M_7, n/2);
        }
    }

    
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

// "Vectorizados"----------------------------------------------------------

void vect_traditional_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==4){
        mat_mul_4x4_vect(A, B, C);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **C_11 = new float*[n/2];
    float **C_12 = new float*[n/2];
    float **C_21 = new float*[n/2];
    float **C_22 = new float*[n/2];

    submat(C, C_11, n/2, 0, 0);
    submat(C, C_12, n/2, 0, n/2);
    submat(C, C_21, n/2, n/2, 0);
    submat(C, C_22, n/2, n/2, n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);


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

void vect_par_traditional_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==4){
        mat_mul_4x4_vect(A, B, C);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **C_11 = new float*[n/2];
    float **C_12 = new float*[n/2];
    float **C_21 = new float*[n/2];
    float **C_22 = new float*[n/2];

    submat(C, C_11, n/2, 0, 0);
    submat(C, C_12, n/2, 0, n/2);
    submat(C, C_21, n/2, n/2, 0);
    submat(C, C_22, n/2, n/2, n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);

    #pragma omp sections
    {
        #pragma omp section
        {
        traditional_mult(A_11, B_11, Aux_1, n/2);
        traditional_mult(A_12, B_21, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_11, n/2);
        }
        #pragma omp section
        {
        traditional_mult(A_11, B_12, Aux_1, n/2);
        traditional_mult(A_12, B_22, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_12, n/2);
        }
        #pragma omp section
        {
        traditional_mult(A_21, B_11, Aux_1, n/2);
        traditional_mult(A_22, B_21, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_21, n/2);
        }
        #pragma omp section
        {
        traditional_mult(A_21, B_12, Aux_1, n/2);
        traditional_mult(A_22, B_22, Aux_2, n/2);
        mat_sum(Aux_1, Aux_2, C_22, n/2);
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

    delete[] C_11;
    delete[] C_12;
    delete[] C_21;
    delete[] C_22;

    for (int i=0; i<n/2; i++){
        delete Aux_1[i];
        delete Aux_2[i];
    }
}

void vect_strassen_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==4){
        mat_mul_4x4_vect(A, B, C);
        return;
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **M_1 = empty_mat(n/2);
    float **M_2 = empty_mat(n/2);
    float **M_3 = empty_mat(n/2);
    float **M_4 = empty_mat(n/2);
    float **M_5 = empty_mat(n/2);
    float **M_6 = empty_mat(n/2);
    float **M_7 = empty_mat(n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);


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

void vect_par_strassen_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // con n potencia de 2.

    if (n==4){
        mat_mul_4x4_vect(A, B, C);
    }

    float **A_11 = new float*[n/2];
    float **A_12 = new float*[n/2];
    float **A_21 = new float*[n/2];
    float **A_22 = new float*[n/2];

    submat(A, A_11, n/2, 0, 0);
    submat(A, A_12, n/2, 0, n/2);
    submat(A, A_21, n/2, n/2, 0);
    submat(A, A_22, n/2, n/2, n/2);

    float **B_11 = new float*[n/2];
    float **B_12 = new float*[n/2];
    float **B_21 = new float*[n/2];
    float **B_22 = new float*[n/2];

    submat(B, B_11, n/2, 0, 0);
    submat(B, B_12, n/2, 0, n/2);
    submat(B, B_21, n/2, n/2, 0);
    submat(B, B_22, n/2, n/2, n/2);

    float **M_1 = empty_mat(n/2);
    float **M_2 = empty_mat(n/2);
    float **M_3 = empty_mat(n/2);
    float **M_4 = empty_mat(n/2);
    float **M_5 = empty_mat(n/2);
    float **M_6 = empty_mat(n/2);
    float **M_7 = empty_mat(n/2);

    float **Aux_1 = empty_mat(n/2);
    float **Aux_2 = empty_mat(n/2);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            // M1 = (A11 + A22)*(B11 + B22)
            mat_sum(A_11, A_22, Aux_1, n/2);
            mat_sum(B_11, B_22, Aux_2, n/2);
            strassen_mult(Aux_1, Aux_2, M_1, n/2);
        }
        #pragma omp section
        {
            //M2 = (A21 + A22)*B11
            mat_sum(A_21, A_22, Aux_1, n/2);
            strassen_mult(Aux_1, B_11, M_2, n/2);
        }
        #pragma omp section
        {
            //M3 = A11*(B12 - B22)
            mat_sub(B_12, B_22, Aux_1, n/2);
            strassen_mult(A_11, Aux_1, M_3, n/2);
        }
        #pragma omp section
        {
            //M4 = A22*(B21 - B11)
            mat_sub(B_21, B_11, Aux_1, n/2);
            strassen_mult(A_22, Aux_1, M_4, n/2);
        }
        #pragma omp section
        {
            //M5 = (A11 + A12)*B22
            mat_sum(A_11, A_12, Aux_1, n/2);
            strassen_mult(Aux_1, B_22, M_5, n/2);
        }
        #pragma omp section
        {
            //M6 = (A21 - A11)*(B11 + B12)
            mat_sub(A_21, A_11, Aux_1, n/2);
            mat_sum(B_11, B_12, Aux_2, n/2);
            strassen_mult(Aux_1, Aux_2, M_6, n/2);
        }
        #pragma omp section
        {
            //M7 = (A12 - A22)*(B21 + B22)
            mat_sub(A_12, A_22, Aux_1, n/2);
            mat_sum(B_21, B_22, Aux_2, n/2);
            strassen_mult(Aux_1, Aux_2, M_7, n/2);
        }
    }

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

#endif