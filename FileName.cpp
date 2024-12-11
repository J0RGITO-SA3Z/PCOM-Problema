// Nombre del alumno Jorge Sáez Salto y Miguel Xuclá Herrero
// Usuario del Juez PC01
// El dilema de Miguel | Comprobador de limites en la entrada de datos |

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <cstdlib> // Para usar exit()

/* PROBLEMA: EL DILEMA DE MIGUEL -> Solución Comprobador de limites en la entrada de datos

    Resolución del problema utilizando Cola de prioridad para colocar las aristas
    en orden de capacidad y de entrada. Para el cálculo se utiliza el algortimo de
    Edmons Karp (Max-Flow o Flujo Máximo)

    Coste de insercción de n elementos en la cola de prioridad -> O(nlog(n))

    Coste del algortimo edmons Karp para grafos de V vértices y E aristas-> O(V*E^2)

*/

const int INF = 1e9;

int V;

using vi = std::vector<int>;    // Alias para simplificar la escritura de un vector de enteros.
using vvi = std::vector<vi>;    // Alias para simplificar la escritura de un vector de vectores de enteros.

vvi adj;                  // Lista de adyacencia para representar el grafo.
vi parent;                // Vector para almacenar los padres en un recorrido (para BFS).
vvi cap;                  // Matriz de capacidades de las aristas.
std::vector<bool> visited; // Vector de visitados para algoritmos como BFS/DFS.


struct tArista {
    int capacidad;   // Capacidad de la arista.
    int id;          // Identificador único de la arista (orden de entrada).
    int u;           // Nodo origen de la arista.
    int v;           // Nodo destino de la arista.

    // Sobrecarga del operador '<' para comparación en una cola de prioridad.
    bool operator<(const tArista& other)const {
        if (capacidad == other.capacidad) {
            return id > other.id;  // Desempate por orden de entrada (id).
        }
        return capacidad < other.capacidad; // Orden por capacidad (mayores tienen prioridad).
    }
};


void bfs(int s, int t) {
    std::queue<int> q;
    visited = std::vector<bool>(2 * V + 2, false);
    q.push(s);
    parent[s] = -1; visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!visited[v] && (cap[u][v] > 0)) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}


int sendFlow(int s, int t) {
    // Intentamos llegar de s a t
    bfs(s, t);
    if (!visited[t])
        return 0; // No pudimos
    // Buscamos capacidad m´as peque˜na en el camino
    int flow = INF, v = t;
    while (v != s) {
        flow = std::min(cap[parent[v]][v], flow);
        v = parent[v];
    }
    // Mandamos flujo
    v = t;
    while (v != s) {
        cap[parent[v]][v] -= flow;
        cap[v][parent[v]] += flow; // INVERSA
        v = parent[v];
    }
    return flow;
}

int edmondsKarp(int s, int t) {
    int ret = 0;
    int flow = 0;
    do {
        flow = sendFlow(s, t);
        ret += flow;
    } while (flow > 0);
    return ret;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M, Z, K;
    std::cin >> N >> M >> Z;
    if (!std::cin)
        return false;

    // Asserts -> Comprobantes de limite en la entrada de datos /------------------------------
    if (N < 2 || N > 100) {
        std::cerr << "Error: N debe estar entre 2 y 100." <<" N: "<< N <<'\n';
        exit(1); // Termina el programa con un código de error
    }
    if (M < N || M > 10000) {
        std::cerr << "Error: M debe estar entre N y 10000." << " M: " << N << '\n';
        exit(1);
    }
    if (Z < 1 || Z > 1e6) {
        std::cerr << "Error: Z debe estar entre 1 y 1e6." << " Z: " << Z << '\n';
        exit(1);
    }


    V = N;
    cap = std::vector<std::vector<int>>(V, std::vector<int>(V)); //Inicializamos los atributos globales
    parent = std::vector<int>(V);
    adj = std::vector<std::vector<int>>(V);
    std::priority_queue<tArista> pq;

    tArista aux;
    for (int i = 0; i < M; i++) {
        std::cin >> aux.u >> aux.v >> aux.capacidad;
        if (aux.u < 1 || aux.u > N || aux.v < 1 || aux.v > N) { 
            std::cerr << "Error: 'u' y 'v' deben estar entre 1 y N."<<" u: "<<aux.u<<" v: "<< aux.v << '\n';
            exit(1); 
        }
        aux.u--; aux.v--; 
        aux.id = i;
        adj[aux.u].push_back(aux.v);
        adj[aux.v].push_back(aux.u);
        cap[aux.u][aux.v] = aux.capacidad;
        pq.push(aux);
    }

    std::cin >> K;

    if (K < 0 || K > M) { 
        std::cerr << "Error: K debe estar entre 0 y M." << " K: " << K << '\n'; 
        exit(1); 
    }

    while (K > 0) {  // Ponemos capacidad 0 a las primeras de la lista de prioridad
        aux = pq.top();
        cap[aux.u][aux.v] = 0;
        pq.pop();
        K--;
    }

    int sol = edmondsKarp(0, N - 1);
    // Escribimos la salida correspondiente
    if (sol >= Z) {
        std::cout << "Ya lo habia pensado" << '\n';
    }
    else {
        std::cout << "Es cierto, no se me habia ocurrido" << '\n';
    }

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}