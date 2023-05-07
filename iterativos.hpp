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

int **tr_mat(int **A, int n){
    int **A_t = empty_mat(n);
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


void seq_mult(int** A, int** B, int** C, int n){
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


void par_mult(int** A, int** B, int** C, int n){
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


void cache_mult(int** A, int** B, int** C, int n){
    // Matriz A, B y C de nxn
    // n es potencia de 2.

    // Transponemos B
    int **B_t = tr_mat(B, n);

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


void cache_par_mult(int** A, int** B, int** C, int n){
    // Matriz A, B y C de nxn
    // n es potencia de 2.

    // Transponemos B
    int **B_t = tr_mat(B, n);

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