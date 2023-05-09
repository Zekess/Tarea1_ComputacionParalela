#include "metrictime.hpp"
#include "comunes.hpp"
#include "iterativos.hpp"
#include "recursivos.hpp"
#include <getopt.h>


int main(int argc, char *argv[]){
    int n_min = 6;
    int n_max = 13;
    bool print_results = false;
    uint threads = 8;
    int reps = 10;

    char c;

	while ((c = getopt(argc, argv, "m:n:t:r:p")) != -1)
	{
		switch (c) {
			case 'm':
                n_min = std::stoi (optarg);
			break;
			case 'n':
                n_max = std::stoi (optarg);
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

    
    std::cout << "n_min = " << n_min << "\n";
    std::cout << "n_max = " << n_max << "\n";
    std::cout << "threads = " << threads << "\n";
    std::cout << "reps = " << reps << "\n";
    std::cout << "\n";

    if (print_results){
        for(int n = n_min; n<n_max+1; n++){
            int n_p = (1 << n);
            float** A = filled_mat(n_p);
            float** B = filled_mat(n_p);
            float** C = empty_mat(n_p);

            std::cout << "Matriz A:" << "\n";
            print(A, n_p);
            std::cout << "\n";

            std::cout << "Matriz B:" << "\n";
            print(B, n_p);
            std::cout << "\n";

            // Iterativos -------------------------------

            TIMERSTART(Secuencial)
            seq_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Secuencial)

            TIMERSTART(Paralelo)
            par_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Paralelo)

            TIMERSTART(Cache)
            cache_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Cache)

            TIMERSTART(Cache_Paralelo)
            cache_par_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Cache_Paralelo)

            // Recursivos -------------------------------

            TIMERSTART(Tradicional_Recursivo)
            traditional_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Tradicional_Recursivo)

            TIMERSTART(Tradicional_Recursivo_Paralelo)
            par_traditional_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Tradicional_Recursivo_Paralelo)

            TIMERSTART(Strassen_Recursivo)
            strassen_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Strassen_Recursivo)

            TIMERSTART(Strassen_Recursivo_Paralelo)
            par_strassen_mult(A, B, C, n_p);
            print(C, n_p);
            TIMERSTOP(Strassen_Recursivo_Paralelo)
        }
    }else{
        for(int n=n_min; n<n_max+1; n++){
            std::cout << "dim = 2^" << n << "\n";
            int n_p = (1 << n);
            float** A = filled_mat(n_p);
            float** B = filled_mat(n_p);
            float** C = empty_mat(n_p);

            // Iterativos ----------------------------

            for(int i=0;i<reps;i++){
                TIMERSTART(Secuencial)
                seq_mult(A, B, C, n_p);
                TIMERSTOP(Secuencial)
            }

            for(int i=0;i<reps;i++){
                TIMERSTART(Paralelo)
                par_mult(A, B, C, n_p);
                TIMERSTOP(Paralelo)
            }

            for(int i=0;i<reps;i++){
                TIMERSTART(Cache)
                cache_mult(A, B, C, n_p);
                TIMERSTOP(Cache)
            }

            for(int i=0;i<reps;i++){
                TIMERSTART(Cache_Paralelo)
                cache_par_mult(A, B, C, n_p);
                TIMERSTOP(Cache_Paralelo)
            }

            // Recursivos -------------------------------------

            for(int i=0;i<reps;i++){
                TIMERSTART(Tradicional_Recursivo)
                traditional_mult(A, B, C, n_p);
                TIMERSTOP(Tradicional_Recursivo)
            }

            for(int i=0;i<reps;i++){
                TIMERSTART(Tradicional_Recursivo_Paralelo)
                par_traditional_mult(A, B, C, n_p);
                TIMERSTOP(Tradicional_Recursivo_Paralelo)
            }

            for(int i=0;i<reps;i++){
                TIMERSTART(Strassen_Recursivo)
                strassen_mult(A, B, C, n_p);
                TIMERSTOP(Strassen_Recursivo)
            }

            for(int i=0;i<reps;i++){
                TIMERSTART(Strassen_Recursivo_Paralelo)
                par_strassen_mult(A, B, C, n_p);
                TIMERSTOP(Strassen_Recursivo_Paralelo)
            }
        }
    }

    
    return 0;
}