#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

int main() {
    std::srand(std::time(0));
    int maxVertices = 100, maxAristas = 1000, maxCap = 1000000;
    //Abrimos el archivo
    std::ofstream outfile("caso_prueba.txt");
    int N, maxAristasAhora, M, Z, u, v, cap, K;
    std::set<std::pair<int, int>> aristas;

    //Generamos los casos grandes (2)
    //Primer caso grande: maximo de vertices y aristas, con K = 0
    for(int j = 0; j < 1; ++j){
        //Definimos N, M y Z
        N = maxVertices;
        M = maxAristas;
        Z = 1 + std::rand() % 100;

        //Escribimos N, M y Z
        outfile << N << " " << M << " " << Z << '\n';

        //Set que lleva la cuenta de las aristas ya existentes para no repetir
        aristas.clear();


        //Generamos las M - 2 aristas
        for (int i = 0; i < M; ++i) {
            //Generamos dos vértices
            do {
                u = 1 + std::rand() % N;
                v = 1 + std::rand() % N;
            } while (u == v || aristas.count({ u, v }) > 0); //Comprobamos q no sea una autoarista y q no exista ya

            //Generamos una capacidad aleatoria entre 1 y 10^6
            cap = 1 + std::rand() % maxCap;

            aristas.insert({ u, v });

            // Escribir la arista
            outfile << u << " " << v << " " << cap << '\n';
        }

        //Generamos K, en la primera mitad de los casos va a ser mayor y en la segunda menor
        //así nos aseguramos de que haya variedad de soluciones
        K = 0;

        //Escribimos K
        outfile << K << '\n';
    }

    //Segundo caso grande: maximo de vertices y aristas, con K maxima tambien
    for(int j = 0; j < 1; ++j){
        //Definimos N, M y Z
        N = maxVertices;
        M = maxAristas;
        Z = 1 + std::rand() % 100;

        //Escribimos N, M y Z
        outfile << N << " " << M << " " << Z << '\n';

        //Set que lleva la cuenta de las aristas ya existentes para no repetir
        aristas.clear();


        //Generamos las M - 2 aristas
        for (int i = 0; i < M; ++i) {
            //Generamos dos vértices
            do {
                u = 1 + std::rand() % N;
                v = 1 + std::rand() % N;
            } while (u == v || aristas.count({ u, v }) > 0); //Comprobamos q no sea una autoarista y q no exista ya

            //Generamos una capacidad aleatoria entre 1 y 10^6
            cap = 1 + std::rand() % maxCap;

            aristas.insert({ u, v });

            // Escribir la arista
            outfile << u << " " << v << " " << cap << '\n';
        }

        //Generamos K, en la primera mitad de los casos va a ser mayor y en la segunda menor
        //así nos aseguramos de que haya variedad de soluciones
        K = M;

        //Escribimos K
        outfile << K << '\n';
    }

    // Cerrar el archivo
    outfile.close();

    return 0;
}
