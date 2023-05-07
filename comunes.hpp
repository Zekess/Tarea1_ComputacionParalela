#ifndef COMUNES
#define COMUNES

//#include <thread>
#include <iostream>
#include <vector>
#include <omp.h>

// ------------------------------------------
// Basic Functions:
// ------------------------------------------

int **filled_mat(int n){
    int **A = new int*[n];
    for (uint64_t i = 0; i < n; i++){
        A[i] = new int[n];
        for (uint64_t j = 0; j < n; j++) {
            A[i][j] = rand()%10;
        }
    }
    return A;
}

int **empty_mat(int n){
    int **A = new int*[n];
    for (uint64_t i = 0; i < n; i++){
        A[i] = new int[n];
    }
    return A;
}

void print_mat(int** A, int n){
    for (uint64_t i = 0; i < n; i++){
        for (uint64_t j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_vec(std::vector<int> A, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            std::cout << A[n*i+j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void base_mult(int** A, int** B, int** C, int n){
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


#endif