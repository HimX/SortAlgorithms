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
}

void selectInputFile()
{
	string firstInput = "Entrada-800.txt",
		   secondInput = "Entrada-8000.txt",
		   thirdInput = "Entrada-80000.txt";
	int option;

	cout << "Seleccione el archivo de entrada:" << endl;
	cout << "- Para Entrada-800.txt presiona 1" << endl;
	cout << "- Para Entrada-8000.txt presiona 2" << endl;
	cout << "- Para Entrada-80000.txt presiona 3" << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		inputFilePath = firstInput;
		break;
	case 2:
		inputFilePath = secondInput;
		break;
	case 3:
		inputFilePath = thirdInput;
		break;
	default:
		cout << "La opci\242n no está disponible.";
		exit(EXIT_FAILURE);
		break;
	}
}

ifstream getFileReader()
{
	ifstream myReader(inputFilePath);
	return myReader;
}

void writeEndLine(string algorithmName, microseconds duration)
{
	cout << endl
		 << "Aqu\241 termina el algoritmo: " << algorithmName
		 << ". Duraci\242n en microsegundos: "
		 << duration.count()
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
	selectInputFile();
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
	int i, j;
	long temp;
	for (i = 0; i < tam; i++)
	{
		for (j = i + 1; j < tam; j++)
		{
			if (array[j] < array[i])
			{
				swap(&array[i], &array[j]);
			}
		}
	}

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
	int i, j, minUnsortedIndex;
	long temp;
	for (i = 0; i < tam - 1; i++)
	{
		minUnsortedIndex = i;
		for (j = i + 1; j < tam; j++)
		{
			if (array[j] < array[minUnsortedIndex])
				minUnsortedIndex = j;
		}
		swap(&array[i], &array[minUnsortedIndex]);
	}

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
	int i, j;
	long key;
	for (i = 1; i < tam; i++)
	{
		key = array[i];
		j = i - 1;

		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}

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
		return;
	}

	int mid = low + (high - low) / 2;
	mergeSort(array, low, mid);
	mergeSort(array, mid + 1, high);
	merge(array, low, high, mid);
}

void quickSort(long array[], long low, long high)
{
	if (low < high)
	{
		long pi = partition(array, low, high);

		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}

void merge(long array[], int low, int high, int mid)
{
	int leftLenght = mid - low + 1;
	int rightLenght = high - mid;
	// Arrays temporales
	long left[leftLenght], right[rightLenght];

	// Copiar información a los arrays temporales
	for (int i = 0; i < leftLenght; i++)
		left[i] = array[low + i];
	for (int j = 0; j < rightLenght; j++)
		right[j] = array[mid + 1 + j];

	int i = 0;
	int j = 0;
	int k = low;

	while (i < leftLenght && j < rightLenght)
	{
		if (left[i] <= right[j])
		{
			array[k] = left[i];
			i++;
		}
		else
		{
			array[k] = right[j];
			j++;
		}
		k++;
	}

	while (i < leftLenght)
	{
		array[k] = left[i];
		i++;
		k++;
	}

	while (j < rightLenght)
	{
		array[k] = right[j];
		j++;
		k++;
	}
}

long partition(long array[], long low, long high)
{
	long pivot = array[high];
	int i = (low - 1);

	for (int j = low; j < high; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}