#ifndef ITERATIVOS
#define ITERATIVOS

#include "comunes.hpp"


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
//     // Para vectorizar la multiplicación usarémos la función 
//     // mat_mul_4x4_vect sobre bloques de 4x4 secuenciales
//     for (uint64_t i = 0; i < n; i+=4){
//         for (uint64_t j = 0; j < n; j+=4) {
//             // Se extraen los bloques de 4x4
//             float** A_block_ij = new float*[4];
//             float** B_block_ij = new float*[4];
//             float** C_block_ij = new float*[4];
//             submat(A, A_block_ij, 4, i, j);
//             submat(B, B_block_ij, 4, i, j);
//             submat(C, C_block_ij, 4, i, j);
//             print(A_block_ij, 4);
//             print(B_block_ij, 4);
//             print(C_block_ij, 4);
//             // Realizamos la multiplicación:
//             mat_mul_4x4_vect(A_block_ij, B_block_ij, C_block_ij);
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