Para compilar se utilizó la siguiente linea:

```ruby
$g++ -o main -fopenmp main.cpp -O3
```
El programa ./main admite los siguientes flags:

```
-m : Fija el tamaño mínimo de las matrices a analizar a 2^m. Por defecto es 6.
-n : Fija el tamaño máximo de las matrices a analizar a 2^n. Por defecto es 13.
-t : Fija la cantidad de threads a t utilizando omp_set_num_threads(t). Por defecto es 8.
-p : Opción para imprimir las matrices resultantes en pantalla (sin medir tiempo). Por defecto está desactivada.
-r : Fija la cantidad de repeticiones a realizar a r. Por defecto es 10.
```
Así, para correr main se ejecutó utilizando los valores por defecto:

```ruby
$./main
```

Y se almacenó el resultado en un archivo .txt para hacer los análisis experimentales.


El archivo vectorized.cpp tiene el código con el que intentamos implementar vectorización a la multiplicación de matrices. Sin embargo sólo se logró multiplicar matrices de 4x4, lo cual no logró mostrar un impacto en los tiempos de ejecución de los algoritmos recursivos. Para compilarlo y ejecutarlo utilizamos lo siguiente

```ruby
$g++ -o vectorized -march=native vectorized.cpp -O3
```