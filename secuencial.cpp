
#include <fstream>     
#include <stdlib.h>
#include <iostream>
#include <string>
#include <omp.h>

using namespace std;
#define FILENAME "numbers.csv"
#define FILENAME_ORDERED "ordered.csv"


void quick_sort(int*, int, int);

int main(int argc, char* argv[])
{
    int N = 1000;
    double start_t, end_t;

    if (argc>1)
        N = strtol(argv[1], 0, 10);

    ofstream dumpStream(FILENAME,ios::out);
    if( dumpStream.bad() ) 
    {
        cerr<<"Falló la creación del archivo "<<FILENAME<<endl;
        return -1;
    }

    start_t = omp_get_wtime();  
    for (int i = 0; i < N; i++)
        dumpStream << (rand() % 10000) << ",";
    dumpStream.close();
    end_t = omp_get_wtime();    

    cout << "Tiempo de escritura a "
        <<FILENAME<<": " << end_t-start_t << endl;

    int* buffer = new int[N];
    int index = 0;
    ifstream readStream(FILENAME);
    string extracted_number;

    start_t = omp_get_wtime();  
    while(getline(readStream, extracted_number, ','))
        buffer[index++] = stoi(extracted_number);
    end_t = omp_get_wtime();    

    cout << "Tiempo de lectura de datos: " << end_t-start_t << endl;

    readStream.close();
    start_t = omp_get_wtime();
    quick_sort(buffer, 0, N);
    end_t = omp_get_wtime();
    cout << "Tiempo del quicksort: " << end_t-start_t << endl;

    dumpStream = ofstream(FILENAME_ORDERED,ios::out);
    if( dumpStream.bad() ) 
    {
        cerr<<"Falló la creación del archivo "<<FILENAME_ORDERED<<endl;
        return -1;
    }

    start_t = omp_get_wtime();  
    for (int i = 0; i < N; i++)
        dumpStream << buffer[i] << ",";
    dumpStream.close();
    end_t = omp_get_wtime();    
    
    cout << "Tiempo de escritura a "
        << FILENAME_ORDERED <<": " << end_t-start_t << endl;
    
    return 0;
}


void quick_sort(int *data, int lo, int hi) //}, int (*compare)(const int *, const int*))
{
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo)/2];

  while(l <= h){
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l<=h){
      //swap
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  //recursive call
  quick_sort(data, lo, h);
  quick_sort(data, l, hi);
}