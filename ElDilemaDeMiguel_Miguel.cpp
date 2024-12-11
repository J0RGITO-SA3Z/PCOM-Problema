// Nombre del alumno: Miguel Xuclá y Jorge Sáez
// Usuario del Juez: PC01


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

const int INF = 1e9; // o cualquier valor grande suficiente

std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> cap;
std::vector<int> parent;
std::vector<bool> visited;
//Cola para guardar las aristas ordenadas en función de su capacidad y en igualdad de condiciones, por orden de entrada
std::priority_queue<std::pair<std::pair<int, int>, std::pair<int, int>>> aristasOrdenadas; // <<capacidad, horaLLegada>, <u, v>>


void bfs(int s, int t) {
    std::queue<int> q;
    visited.assign(visited.size(), false);
    q.push(s);
    parent[s] = -1;
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
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
    if (!visited[t]) return 0; // No pudimos
    // Buscamos capacidad más pequeña en el camino
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

void addArista(std::pair<std::pair<int, int>, std::pair<int, int>> arista){
    adj[arista.second.first].push_back(arista.second.second);
    cap[arista.second.first][arista.second.second] = arista.first.first;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M, Z, K;
    std::cin >> N >> M >> Z;
    if (!std::cin)
        return false;

    adj.assign(N + 1, std::vector<int>());
    cap.assign(N + 1, std::vector<int>(N + 1, 0));
    parent.assign(N + 1, -1);
    visited.assign(N + 1, false);
    aristasOrdenadas = std::priority_queue<std::pair<std::pair<int, int>, std::pair<int, int>>>();

    int u, v, c;
    for (int i = 0; i < M; ++i) {
        std::cin >> u >> v >> c;
        aristasOrdenadas.push({{c, i},{u, v}});
    }

    std::cin >> K;
    for(int i = 0; i < K; ++i){
        aristasOrdenadas.pop();
    }

    while(!aristasOrdenadas.empty()){
        addArista(aristasOrdenadas.top());
        aristasOrdenadas.pop();
    }

    if(edmondsKarp(1, N) >= Z) std::cout << "Ya lo habia pensado\n";
    else std::cout << "Es cierto, no se me habia ocurrido\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("caso_prueba.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}