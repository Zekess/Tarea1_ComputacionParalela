#ifndef ITERATIVOS
#define ITERATIVOS

//#include <thread>
#include <iostream>
#include "comunes.hpp"
#include <vector>
#include <omp.h>
#include <immintrin.h>

// ------------------------------------------
// Basic Functions:
// ------------------------------------------

// void swap(float *a, float *b){
//     float *aux;
//     a 
// }

float **tr_mat(float **A, int n){
    float **A_t = empty_mat(n);
    for (uint64_t i = 0; i < n; i++){
        for (uint64_t j = 0; j < n; j++) {
            A_t[i][j] = A[j][i];
        }
    }
    return A_t;
}


// ------------------------------------------
// Traditional Multiplication Functions:
// ------------------------------------------


void seq_mult(float** A, float** B, float** C, float n){
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


// void seq_mult_vect(float** A, float** B, float** C, int n){
//     // Matriz A, B y C de nxn
//     // n es potencia de 2.

//     //Se realiza la mutplicación
//     for (uint64_t i = 0; i < n; i++){
//         for (uint64_t j = 0; j < n; j++) {
//             float accum = 0;
//             for (uint64_t k = 0; k < n; k++){
//                 __m256 A_row_i = _mm256_loadu_ps(&A[i][j+8*k]);
//                 __m256 B_col_j = _mm256_loadu_ps(&B[i+8*k][j]);
//                 accum += _mm256_dp_ps(A_row_i, B_col_j, 0);
//             }
//             C[i][j] = accum;
//         }
//     }
// }


void par_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // n es potencia de 2.

    //Se realiza la mutplicación
    #pragma omp parallel for
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


void cache_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // n es potencia de 2.

    // Transponemos B
    float **B_t = tr_mat(B, n);

    // Multiplicamos
    for (uint64_t i = 0; i < n; i++){
        for (uint64_t j = 0; j < n; j++) {
            float accum = 0;
            for (uint64_t k = 0; k < n; k++){
                accum += A[i][k]*B_t[j][k];
            }
            C[i][j] = accum;
        }
    }
}


void cache_par_mult(float** A, float** B, float** C, int n){
    // Matriz A, B y C de nxn
    // n es potencia de 2.

    // Transponemos B
    float **B_t = tr_mat(B, n);

    // Multiplicamos
    #pragma omp parallel for
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


#endif