// LABORATORIO 2 PARTE 2

// Nombre:
// Andrea De Lourdes Lam Pelaez
// Carné:
// 20102


// Nombre:
// Gabriel Alejandro Vicente Lorenzo
// Carné:
// 20498




#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;

bool isPrime(int number) {
    if (number == 0 || number == 1) {
        return false;
    }
    int divisor;
    for (divisor = number / 2; number % divisor != 0; --divisor) {
        ;
    }
    if (divisor != 1) {
        return false;
    } else {
        return true;
    }
}

int main() {
    int N;
    cout << "Ingrese la cantidad de números aleatorios: ";
    cin >> N;

    srand(time(0));
    int *numbers = new int[N];

    auto start_generation = chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 100;
    }

    auto end_generation = chrono::high_resolution_clock::now();

    ofstream outFile("numeros.txt");
    for (int i = 0; i < N; i++) {
        outFile << numbers[i];
        if (i < N - 1) {
            outFile << ",";
        }
    }
    outFile.close();

    delete[] numbers;

    ifstream inFile("numeros.txt");
    vector<int> numbersVector;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line, ',')) {
            int number;
            stringstream(line) >> number;
            numbersVector.push_back(number);
        }
        inFile.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    auto start_sorting = chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            sort(numbersVector.begin(), numbersVector.end());
        }
    }

    auto end_sorting = chrono::high_resolution_clock::now();

    ofstream outFileSorted("numeros_ordenados.txt");
    for (size_t i = 0; i < numbersVector.size(); i++) {
        outFileSorted << numbersVector[i];
        if (i < numbersVector.size() - 1) {
            outFileSorted << ",";
        }
    }
    outFileSorted.close();

    auto duration_generation = chrono::duration_cast<chrono::milliseconds>(end_generation - start_generation);
    auto duration_sorting = chrono::duration_cast<chrono::milliseconds>(end_sorting - start_sorting);

    cout << "Tiempo de generación: " << duration_generation.count() << " ms" << endl;
    cout << "Tiempo de ordenamiento: " << duration_sorting.count() << " ms" << endl;

    return 0;
}
