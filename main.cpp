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
    int reps = 1;

	while ((c = getopt(argc, argv, "n:t:r:p")) != -1)
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
			case 'r':
				reps = std::stoi (optarg);
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

    if (print_results){
        TIMERSTART(Secuencial)
        seq_mult(A, B, C, n);
        print_mat(C, n);
        TIMERSTOP(Secuencial)

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
        
        for(int i=0;i<reps;i++){
            TIMERSTART(Secuencial)
            seq_mult(A, B, C, n);
            TIMERSTOP(Secuencial)
        }

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