#include <iostream>
#include <fstream>
#include <set>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

const int numCasos = 500;

int main() {
    std::srand(std::time(0));
    int maxVertices = 100, maxAristas = 1000, maxCap = 1000000;
    //Abrimos el archivo
    std::ofstream outfile("caso_prueba.txt");
    int N, maxAristasAhora, M, Z, u, v, cap, K;
    std::set<std::pair<int, int>> aristas;

    //Vamos a ir fijando parámetros y generamos 10 casos permiutando aleatoriamente el resto de valores
    //Generamos la primera tanda de casos exhaustivos, fijando K=0
    for(int j = 0; j < 10; ++j){
        //Generamos N, M y Z aleatorios
        N = 2 + std::rand() % (maxVertices - 2 + 1); //(max - min + 1)
        maxAristasAhora = std::min(maxAristas, N * (N - 1) / 2);
        if(maxAristasAhora <= N) M = N;
        else M = N + std::rand() % (maxAristasAhora - N + 2);
        Z = 1 + std::rand() % 1000000;

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

    //Generamos la segunda tanda de casos exhaustivos, fijando K = M
    for(int j = 0; j < 10; ++j){
        //Generamos N, M y Z aleatorios
        N = 2 + std::rand() % (maxVertices - 2 + 1); //(max - min + 1)
        maxAristasAhora = std::min(maxAristas, N * (N - 1) / 2);
        if(maxAristasAhora <= N) M = N;
        else M = N + std::rand() % (maxAristasAhora - N + 2);
        Z = 1 + std::rand() % 1000000;

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

    //Generamos la tercera tanda de casos exhaustivos, fijando Z = 1
    for(int j = 0; j < 10; ++j){
        //Generamos N, M y Z aleatorios
        N = 2 + std::rand() % (maxVertices - 2 + 1); //(max - min + 1)
        maxAristasAhora = std::min(maxAristas, N * (N - 1) / 2);
        if(maxAristasAhora <= N) M = N;
        else M = N + std::rand() % (maxAristasAhora - N + 2);
        Z = 1;

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
        K = 0 + std::rand() % (M + 1);

        //Escribimos K
        outfile << K << '\n';
    }

    //Generamos la cuarta tanda de casos exhaustivos, fijando Z = 1e6
    for(int j = 0; j < 10; ++j){
        //Generamos N, M y Z aleatorios
        N = 2 + std::rand() % (maxVertices - 2 + 1); //(max - min + 1)
        maxAristasAhora = std::min(maxAristas, N * (N - 1) / 2);
        if(maxAristasAhora <= N) M = N;
        else M = N + std::rand() % (maxAristasAhora - N + 2);
        Z = 1000000;

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
        K = 0 + std::rand() % (M + 1);

        //Escribimos K
        outfile << K << '\n';
    }

    //Generamos la cuarta tanda de casos exhaustivos, fijando cap = 1
    for(int j = 0; j < 10; ++j){
        //Generamos N, M y Z aleatorios
        N = 2 + std::rand() % ((maxVertices/2) - 2 + 1); //(max - min + 1)
        maxAristasAhora = std::min(maxAristas/2, N * (N - 1) / 2);
        if(maxAristasAhora <= N) M = N;
        else M = N + std::rand() % (maxAristasAhora - N + 2);
        Z = 1 + std::rand() % 1000000;

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
            cap = 1;

            aristas.insert({ u, v });

            // Escribir la arista
            outfile << u << " " << v << " " << cap << '\n';
        }

        //Generamos K, en la primera mitad de los casos va a ser mayor y en la segunda menor
        //así nos aseguramos de que haya variedad de soluciones
        K = 0 + std::rand() % (M + 1);

        //Escribimos K
        outfile << K << '\n';
    }

    //Generamos la quinta tanda de casos exhaustivos, fijando cap = maxCap
    for(int j = 0; j < 10; ++j){
        //Generamos N, M y Z aleatorios
        N = 2 + std::rand() % ((maxVertices/2) - 2 + 1); //(max - min + 1)
        maxAristasAhora = std::min(maxAristas/2, N * (N - 1) / 2);
        if(maxAristasAhora <= N) M = N;
        else M = N + std::rand() % (maxAristasAhora - N + 2);
        Z = 1 + std::rand() % 1000000;

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
            cap = maxCap;

            aristas.insert({ u, v });

            // Escribir la arista
            outfile << u << " " << v << " " << cap << '\n';
        }

        //Generamos K, en la primera mitad de los casos va a ser mayor y en la segunda menor
        //así nos aseguramos de que haya variedad de soluciones
        K = 0 + std::rand() % (M + 1);

        //Escribimos K
        outfile << K << '\n';
    }

    // Cerrar el archivo
    outfile.close();

    return 0;
}
