#ifndef COMUNES
#define COMUNES

//#include <thread>
#include <iostream>
#include <vector>
#include <omp.h>
#include <immintrin.h>

// ------------------------------------------
// Basic Functions:
// ------------------------------------------

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

void mat_mul_4x4_vect(float** A, float** B, float** C){
    __m128 B_col_0 = _mm_load_ps(B[0]);
    __m128 B_col_1 = _mm_load_ps(B[1]);
    __m128 B_col_2 = _mm_load_ps(B[2]);
    __m128 B_col_3 = _mm_load_ps(B[3]);

    _MM_TRANSPOSE4_PS(B_col_0, B_col_1, B_col_2, B_col_3);

    for(int i=0; i<4; i++){
        __m128 A_row_i = _mm_load_ps(A[i]);

        __m128 r8 = _mm_mul_ps(A_row_i, B_col_0);
        __m128 r9 = _mm_mul_ps(A_row_i, B_col_1);
        __m128 r10 = _mm_mul_ps(A_row_i, B_col_2);
        __m128 r11 = _mm_mul_ps(A_row_i, B_col_3);

        r8 = _mm_hadd_ps(r8, r9);
        r9 = _mm_hadd_ps(r10, r11);

        __m128 r12 = _mm_hadd_ps(r8, r9);
        _mm_store_ps(C[i], r12);
    }
}

void print(const __m128 v) {
    float *a = (float *) &v;
    for (int i = 0; i < 4; ++i) std::cout<<a[i]<< " ";
    std::cout << std::endl;
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