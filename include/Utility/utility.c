//
// Created by bizzi on 14/03/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define MIN 10
#define MAX 30

/* generate a random floating point number from min to max */
double rand_from(double min, double max)
{
    srand(time(NULL));
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void fill_vector(double* vector, int n){
    if(vector==NULL)
        return;
    for (int i = 0; i < n; i++)
        vector[i]=rand_from(10,30);
}

//Passare null per fare il printf
void append_to_file (char* fileName, char* string){
    FILE* file;
    if (fileName!=NULL)
        file=fopen(fileName,"a");
    else
        file=stdout;
    char* newLine="\n";

    if (file==NULL)
        return;

    fseek(file,0,SEEK_END);

    if (ftell(file)!=0)
        fprintf(file,newLine);
    fputs(string,file);
    if (fileName!=NULL)
        fclose(file);
}

void clean_file(char* fileName){
    if (fileName==NULL)
        return;
    FILE* file=fopen(fileName,"w");
    fclose(file);
}

double get_cur_time() {
  struct timeval   tv;
  double cur_time;
  
  gettimeofday(&tv, NULL);
  cur_time = tv.tv_sec + tv.tv_usec / 1000000.0;
  
  return cur_time;
}

int* find_divisors(int n){
    int alloc=5, //grandezza iniziale array dei divisori
        busy=0; //#celle occupate. Nella prima ci metto quanto è grande l'array
    int *array=(int*)calloc(5, sizeof(int));

    for (int i=1; i<=sqrt(n); i++)
    {
        if (n%i == 0)
        {
            array[++busy]=i;

            if (alloc==busy || alloc==busy+1){ //ri-allocazione vettore
                alloc*=2;
                array=realloc(array,alloc* sizeof(int));
            }
            array[++busy] = n / i;
        }
    }

    array[0]=busy;
    return array;
}