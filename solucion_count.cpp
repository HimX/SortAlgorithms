#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include "solucion.h"

using namespace std;
using namespace std::chrono;

/*
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}
*/

long long operationsCount = 0;
string inputFilePath;

void merge(long array[], int, int, int);
void mergeSort(long array[], int, int);
void quickSort(long array[], long, long);
long partition(long array[], long, long);

void printArray(long array[], int size)
{
    cout << endl;
    int i;
    for (i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
    operationsCount += 3;
}

ifstream getFileReader()
{
    ifstream myReader("Entrada-80000.txt");
    return myReader;
}

void writeEndLine(string algorithmName, microseconds duration)
{
    cout << endl
         << "Aqu\241 termina el algoritmo: " << algorithmName
         << ". Cantidad de operaciones: "
         << operationsCount
         << endl;
}

long getArraySize()
{
    ifstream myReader = getFileReader();
    string myText;
    long arraySize = 0;

    while (getline(myReader, myText))
    {
        arraySize++;
    }

    myReader.close();
    return arraySize;
}

void setArrayElements(long array[])
{
    ifstream myReader = getFileReader();
    string myText;
    long i = 0;

    std::string::size_type sz;
    while (getline(myReader, myText))
    {
        array[i] = std::stol(myText, &sz);
        i++;
    }

    myReader.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

    long num;
    long *arreglo, *arregloBur, *arregloSele, *arregloInser, *arregloMergesort, *arregloQuicksort;
    system("CLS");
    //cout << "Cu\240l es el tama\244o de la muestra: ";
    //cin >> num;
    num = getArraySize();
    arreglo = new long[num];
    arregloBur = new long[num];
    arregloSele = new long[num];
    arregloInser = new long[num];
    arregloMergesort = new long[num];
    arregloQuicksort = new long[num];

    //generarMuestra(arreglo, num);
    setArrayElements(arreglo);
    printArray(arreglo, num);

    for (int i = 0; i < num; i++)
    {
        arregloBur[i] = arreglo[i];
        arregloSele[i] = arreglo[i];
        arregloInser[i] = arreglo[i];
        arregloMergesort[i] = arreglo[i];
        arregloQuicksort[i] = arreglo[i];
    }

    algoBurbuja(arregloBur, num);

    algoSeleccion(arregloSele, num);

    algoInsercion(arregloInser, num);

    algoMergeSort(arregloMergesort, num);

    algoQuickSort(arregloQuicksort, num);

    return EXIT_SUCCESS;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//genera un vector con una muestra aleatoria de tamaño tam
void generarMuestra(long arreglo[], long tam)
{
    srand(time(NULL));

    for (long i = 0; i <= tam; i++)
    {
        arreglo[i] = rand();
        cout << arreglo[i] << endl;
    }
}

//Ordena el vector utilizando el algoritmo de la burbuja
// y muestra por pantalla el tiempo de ejecución
void algoBurbuja(long array[], long tam)
{
    cout << endl
         << "Aqu\241 inicia el algoritmo de la burbuja" << endl;

    auto start = high_resolution_clock::now();
    operationsCount = 0;
    int i, j;
    long temp;
    operationsCount = operationsCount + 3;
    for (i = 0; i < tam; i++)
    {
        operationsCount += 4;
        for (j = i + 1; j < tam; j++)
        {
            operationsCount += 2;
            if (array[j] < array[i])
            {
                swap(&array[i], &array[j]);
                operationsCount += 3;
            }
            operationsCount += 3;
        }
        operationsCount += 2;
    }
    operationsCount += 3;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printArray(array, tam);
    writeEndLine("burbuja", duration);
}

//Ordena el vector utilizando el algoritmo de selección
// y muestra por pantalla el tiempo de ejecución
void algoSeleccion(long array[], long tam)
{
    cout << endl
         << "Aqu\241 inicia el algoritmo de selecci\242n" << endl;

    auto start = high_resolution_clock::now();
    operationsCount = 0;
    int i, j, minUnsortedIndex;
    long temp;
    operationsCount += 5;
    for (i = 0; i < tam - 1; i++)
    {
        minUnsortedIndex = i;
        operationsCount += 6;
        for (j = i + 1; j < tam; j++)
        {
            operationsCount += 2;
            if (array[j] < array[minUnsortedIndex])
            {
                minUnsortedIndex = j;
                operationsCount++;
            }
            operationsCount += 3;
        }
        swap(&array[i], &array[minUnsortedIndex]);
        operationsCount += 5;
    }
    operationsCount += 2;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printArray(array, tam);
    writeEndLine("seleci\242n", duration);
}

//Ordena el vector utilizando el algoritmo de inserción
// y muestra por pantalla el tiempo de ejecución
void algoInsercion(long array[], long tam)
{
    cout << endl
         << "Aqu\241 inicia el algoritmo de inserci\242n" << endl;

    auto start = high_resolution_clock::now();
    operationsCount = 0;
    int i, j;
    long key;
    operationsCount += 4;
    for (i = 1; i < tam; i++)
    {
        key = array[i];
        j = i - 1;
        operationsCount += 6;

        while (j >= 0 && array[j] > key)
        {
            operationsCount += 4;
            array[j + 1] = array[j];
            j = j - 1;
            operationsCount += 5;
        }
        array[j + 1] = key;
        operationsCount += 4;
    }
    operationsCount += 2;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printArray(array, tam);
    writeEndLine("inserci\242n", duration);
}

//Ordena el vector utilizando el algoritmo mergesort
// y muestra por pantalla el tiempo de ejecución
void algoMergeSort(long array[], long tam)
{
    cout << endl
         << "Aqu\241 inicia el algoritmo mergesort" << endl;

    auto start = high_resolution_clock::now();

    operationsCount = 2;
    mergeSort(array, 0, tam - 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printArray(array, tam);
    writeEndLine("mergesort", duration);
}

//Ordena el vector utilizando el algoritmo quicksort
// y muestra por pantalla el tiempo de ejecución
void algoQuickSort(long array[], long tam)
{
    cout << endl
         << "Aqu\241 inicia el algoritmo quicksort" << endl;

    auto start = high_resolution_clock::now();

    operationsCount = 2;
    quickSort(array, 0, tam - 1);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printArray(array, tam);
    writeEndLine("quicksort", duration);
}

void mergeSort(long array[], int low, int high)
{
    if (low >= high)
    {
        operationsCount++;
        return;
    }

    int mid = low + (high - low) / 2;
    mergeSort(array, low, mid);
    mergeSort(array, mid + 1, high);
    merge(array, low, high, mid);
    operationsCount += 8;
}

void quickSort(long array[], long low, long high)
{
    operationsCount++;
    if (low < high)
    {
        long pi = partition(array, low, high);

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
        operationsCount += 6;
    }
}

void merge(long array[], int low, int high, int mid)
{
    int leftLenght = mid - low + 1;
    int rightLenght = high - mid;
    // Arrays temporales
    long left[leftLenght], right[rightLenght];
    operationsCount += 9;

    // Copiar información a los arrays temporales
    for (int i = 0; i < leftLenght; i++)
    {
        left[i] = array[low + i];
        operationsCount += 6;
    }
    operationsCount += 2;
    for (int j = 0; j < rightLenght; j++)
    {
        right[j] = array[mid + 1 + j];
        operationsCount += 7;
    }
    operationsCount += 2;

    int i = 0;
    int j = 0;
    int k = low;
    operationsCount += 3;

    while (i < leftLenght && j < rightLenght)
    {
        operationsCount += 7;
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            i++;
            operationsCount += 4;
        }
        else
        {
            array[k] = right[j];
            j++;
            operationsCount += 4;
        }
        k++;
    }
    operationsCount += 3;

    while (i < leftLenght)
    {
        array[k] = left[i];
        i++;
        k++;
        operationsCount += 6;
    }
    operationsCount++;

    while (j < rightLenght)
    {
        array[k] = right[j];
        j++;
        k++;
        operationsCount += 6;
    }
    operationsCount++;
}

long partition(long array[], long low, long high)
{
    long pivot = array[high];
    int i = (low - 1);
    operationsCount += 5;

    for (int j = low; j < high; j++)
    {
        operationsCount += 2;
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
            operationsCount += 4;
        }
        operationsCount += 2;
    }
    operationsCount += 2;
    swap(&array[i + 1], &array[high]);
    operationsCount += 4;
    return (i + 1);
}