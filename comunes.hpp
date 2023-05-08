#ifndef COMUNES
#define COMUNES

#include <iostream>
#include <omp.h>


float **filled_mat(int n){
    float **A = new float*[n];
    for (uint64_t i = 0; i < n; i++){
        A[i] = new float[n];
        for (uint64_t j = 0; j < n; j++) {
            A[i][j] = rand()%10;
        }
    }
    return A;
}

float **empty_mat(int n){
    float **A = new float*[n];
    for (uint64_t i = 0; i < n; i++){
        A[i] = new float[n];
    }
    return A;
}

float **tr_mat(float **A, int n){
    float **A_t = empty_mat(n);
    for (uint64_t i = 0; i < n; i++){
        for (uint64_t j = 0; j < n; j++) {
            A_t[i][j] = A[j][i];
        }
    }
    return A_t;
}

void base_mult(float** A, float** B, float** C, float n){
    // Matriz A, B y C de nxn
    // n es potencia de 2.

    //Se realiza la mutplicación
    for (uint64_t i = 0; i < n; i++){
        for (uint64_t j = 0; j < n; j++) {
            float accum = 0;
            for (uint64_t k = 0; k < n; k++){
                accum += A[i][k]*B[k][j];
            }
            C[i][j] = accum;
        }
    }
}

void submat(float** A, float** B, int n, int n_row, int n_col){
	for (int i = 0; i < n; i++) 
		B[i] = &A[n_row+i][n_col];
}

float **mat_sum(float** A, float** B, float** C, int n){
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}

float **mat_sub(float** A, float** B, float** C, int n){
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}

void print(float** A, int n) {
    for (uint64_t i = 0; i < n; i++){
        for (uint64_t j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif