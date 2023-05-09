Para compilar se utilizó la siguiente linea:

```ruby
$g++ -o main -fopenmp main.cpp -O3
```

Luego, para correr main se ejecutó

```ruby
$./main
```

Y se almacenó el resultado en un archivo .txt para hacer los análisis experimentales. El programa ./main admite los siguientes flags:

```ruby
-m : Fija el tamaño mínimo de las matrices a analizar a 2^m. Por defecto es 6.
-n : Fija el tamaño máximo de las matrices a analizar a 2^n. Por defecto es 13.
-t : Fija la cantidad de threads a t utilizando omp_set_num_threads(t). Por defecto es 8.
-p : Opción para imprimir las matrices resultantes en pantalla (sin medir tiempo). Por defecto está desactivada.
-r : Fija la cantidad de repeticiones a realizar a r. Por defecto es 10.
```