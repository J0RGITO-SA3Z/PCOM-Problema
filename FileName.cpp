#include <iostream>
#include <fstream>
#include <random>
#include <set>

using namespace std;

int main() {
    // Crear un generador de números aleatorios
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist_2_100(2, 100);  // Para número de vértices
    uniform_int_distribution<int> dist_1_1000(1, 1000);  // Para número de aristas
    uniform_int_distribution<int> dist_1_10e6(1, 1000000);  // Para capacidades de aristas
    uniform_int_distribution<int> dist_1_N(1, 100);  // Para el umbral Z

    // Número de vértices (aleatorio entre 2 y 100)
    int N = dist_2_100(gen);

    // Número de aristas (aleatorio entre 1 y 1000)
    int M = dist_1_1000(gen);

    // Abrir el archivo para escribir el caso de prueba
    ofstream outfile("caso_prueba.txt");

    // Umbral Z (aleatorio entre 1 y N)
    int Z = dist_1_N(gen);

    // Escribir N, M y Z en el archivo
    outfile << N << " " << M << " " << Z << "\n";

    // Conjunto para verificar las aristas existentes (u, v) no se repitan
    set<pair<int, int>> aristas;

    // Generar las M aristas
    for (int i = 0; i < M; ++i) {
        int u, v;

        // Generar dos vértices distintos
        do {
            u = dist_2_100(gen);
            v = dist_2_100(gen);
        } while (u == v || aristas.count({ u, v }) > 0); // Asegurarse de que u != v y no haya arista repetida

        // Generar una capacidad aleatoria entre 1 y 10^6
        int capacidad = dist_1_10e6(gen);

        // Añadir la arista al conjunto para evitar duplicados
        aristas.insert({ u, v });

        // Escribir la arista en el archivo
        outfile << u << " " << v << " " << capacidad << "\n";
    }

    // Cerrar el archivo
    outfile.close();

    return 0;
}
