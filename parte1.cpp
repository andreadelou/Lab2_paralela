#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>

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
    int N; // Número de elementos a generar
    cout << "Ingrese la cantidad de números aleatorios: ";
    cin >> N;

    // Generar N números aleatorios
    srand(time(0)); // Semilla para generar números aleatorios
    int *numbers = new int[N]; // Crear un arreglo en memoria dinámica
    for (int i = 0; i < N; i++) {
        numbers[i] = rand() % 100; // Generar números aleatorios entre 0 y 99
    }

    // Escribir los números en un archivo
    ofstream outFile("numeros.txt");
    for (int i = 0; i < N; i++) {
        outFile << numbers[i];
        if (i < N - 1) {
            outFile << ",";
        }
    }
    outFile.close();

    // Liberar la memoria
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

    // Ordenar los números
    sort(numbersVector.begin(), numbersVector.end());

    // Escribir los números ordenados en un segundo archivo
    ofstream outFileSorted("numeros_ordenados.txt");
    for (size_t i = 0; i < numbersVector.size(); i++) {
        outFileSorted << numbersVector[i];
        if (i < numbersVector.size() - 1) {
            outFileSorted << ",";
        }
    }
    outFileSorted.close();

    return 0;
}
