#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream inFile("numeros.txt");
    vector<int> numbers;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line, ',')) {
            int number;
            stringstream(line) >> number;
            numbers.push_back(number);
        }
        inFile.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    // Ordenar los números
    sort(numbers.begin(), numbers.end());

    // Escribir los números ordenados en un segundo archivo
    ofstream outFile("numeros_ordenados.txt");
    for (size_t i = 0; i < numbers.size(); i++) {
        outFile << numbers[i];
        if (i < numbers.size() - 1) {
            outFile << ",";
        }
    }
    outFile.close();

    return 0;
}
