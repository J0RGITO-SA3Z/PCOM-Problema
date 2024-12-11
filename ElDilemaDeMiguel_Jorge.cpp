// Nombre del alumno Jorge Sáez Salto y Miguel Xuclá Herrero
// Usuario del Juez PC01
// El dilema de Miguel

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>


const int INF = 1e9;

int V;

using vi = std::vector<int>;
using vvi = std::vector<vi>;
vvi adj;

std::vector<int> parent;
std::vector<std::vector<int>> cap;
std::vector<bool> visited;

struct tArista {

    int capacidad;
    int id;
    int u;
    int v; 

    bool operator<(const tArista& other)const { 
        if (capacidad == other.capacidad) {
            return id > other.id; 
        }
        return  capacidad < other.capacidad;
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
    int N ,M, Z, K;  
    std::cin >> N >> M >> Z;
    if (!std::cin)
        return false;

    V = N;
    cap = std::vector<std::vector<int>>(V, std::vector<int>(V));
    parent = std::vector<int>(V);
    adj = std::vector<std::vector<int>>(V);
    std::priority_queue<tArista> pq; 

    tArista aux; 
    for (int i = 0; i < M; i++) {
        std::cin >> aux.u >> aux.v >> aux.capacidad;
        aux.u--; aux.v--;
        aux.id = i;
        adj[aux.u].push_back(aux.v);
        adj[aux.v].push_back(aux.u);
        cap[aux.u][aux.v] = aux.capacidad; 
        pq.push(aux);
    }

    std::cin >> K;

    while (K > 0) {  
        aux = pq.top();
        cap[aux.u][aux.v] = 0; 
        pq.pop();
        K--;
    }

    int sol = edmondsKarp(0, N - 1); 

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
    std::ifstream in("caso_prueba.txt");
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