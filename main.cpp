#include <iostream>
#include <cstdint>
#include "metrictime.hpp"
//#include "comunes.hpp"
#include "iterativos.hpp"
#include "recursivos.hpp"
#include <getopt.h>

//using namespace std;



int main(int argc, char *argv[]){
    int n;
    char c;
    bool print_results = false;
    uint threads = 8;

	while ((c = getopt(argc, argv, "n:t:p")) != -1)
	{
		switch (c) {
			case 'n':
				n = (1 << std::stoi (optarg));
			break;
			case 't':
				threads = std::stoi (optarg);
			break;
			case 'p':
				print_results = true;
			break;
			default:
			break;
		}
	}

    omp_set_num_threads (threads);
    std::cout << "n = " << n << "\n";
    
    int** A = filled_mat(n);
    int** B = filled_mat(n);
    int** C = empty_mat(n);

    std::vector<int> vec_1 (n*n, 3);
    std::vector<int> vec_2 (n*n, 2);
    std::vector<int> vec_3 (n*n, 0);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            vec_1[n*i+j] = A[i][j];
            vec_2[n*i+j] = B[i][j];
        }
    }
    //int** C_cache = empty_mat(n);
    //int** C_cache_par = empty_mat(n);

    //print_mat(A, n);
    //print_mat(B, n);

    if (print_results){
        TIMERSTART(Secuencial)
        seq_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Secuencial)

        // TIMERSTART(Vector)
        // vec_mult(vec_1, vec_2, vec_3, n);
        // print_vec(vec_3, n);
        // TIMERSTOP(Vector)

        TIMERSTART(Paralelo)
        par_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Paralelo)

        TIMERSTART(Cache)
        cache_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Cache)

        TIMERSTART(Cache_Paralelo)
        cache_par_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Cache_Paralelo)

        TIMERSTART(Tradicional_Recursivo)
        traditional_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Tradicional_Recursivo)

        TIMERSTART(Strassen_Recursivo)
        strassen_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Strassen_Recursivo)

        // TIMERSTART(Strassen_Paralelo_Recursivo)
        // strassen_par_mult(A, B, C, n);
        // print_mat(C, n);
        // TIMERSTOP(Strassen_Paralelo_Recursivo)
    }else{
        TIMERSTART(Secuencial)
        seq_mult(A, B, C, n);
        TIMERSTOP(Secuencial)

        // TIMERSTART(Vector)
        // vec_mult(vec_1, vec_2, vec_3, n);
        // TIMERSTOP(Vector)

        TIMERSTART(Paralelo)
        par_mult(A, B, C, n);
        TIMERSTOP(Paralelo)

        TIMERSTART(Cache)
        cache_mult(A, B, C, n);
        TIMERSTOP(Cache)

        TIMERSTART(Cache_Paralelo)
        cache_par_mult(A, B, C, n);
        TIMERSTOP(Cache_Paralelo)

        TIMERSTART(Tradicional_Recursivo)
        traditional_mult(A, B, C, n);
        TIMERSTOP(Tradicional_Recursivo)

        TIMERSTART(Strassen_Recursivo)
        strassen_mult(A, B, C, n);
        TIMERSTOP(Strassen_Recursivo)

        // TIMERSTART(Strassen_Paralelo_Recursivo)
        // strassen_par_mult(A, B, C, n);
        // TIMERSTOP(Strassen_Paralelo_Recursivo)
    }

    
    return 0;
}