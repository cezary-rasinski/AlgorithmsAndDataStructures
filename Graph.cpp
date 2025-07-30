/*
Wejście:
Na wejściu program otrzymuje liczbę naturalną t – liczbę testów.  
Każdy test składa się z:
- trzech liczb naturalnych n, m, s  
  • n – liczba wierzchołków (numerowanych od 0 do n−1),  
  • m – liczba skierowanych krawędzi,  
  • s – numer wierzchołka startowego,  
- oraz m kolejnych linii, z każdą parą x y opisującą skierowaną krawędź z x do y.

Opis zadania:
Dany jest skierowana graf G, o n-wierzchołkach i m-krawędziach. Janusz zaczyna w wierzchołku s, którego status początkowo jest „stabilny”.  
Przy każdym przejściu po krawędzi (u → v) status wierzchołka v zmienia się na przeciwny do statusu u („stabilny” ↔ „niestabilny”).  
Celem jest dotarcie do wierzchołka docelowego – takiego, który nie ma wychodzących krawędzi – z końcowym statusem „stabilnym”.

- Jeśli istnieje ścieżka od s do pewnego wierzchołka docelowego, przy której docelowy wierzchołek kończy jako „stabilny”,  
  wypisz „TAK” i w kolejnej linii wypisz numery wierzchołków tej ścieżki (od s do docelowego).  
  Wypisz najkrótszą możliwą ścieżkę; w razie remisu weź tę, która jest najmniejsza leksykograficznie.

- Jeśli stabilizacja nie jest możliwa, ale istnieje ścieżka od s prowadząca do dowolnego cyklu w G (pętli czasowej),  
  wypisz „PETLA”.

- Jeśli ani stabilizacja, ani dojście do cyklu nie są osiągalne, wypisz „NIE”.

Wyjście:
Dla każdego z t testów najpierw jedna linia ze słowem „TAK”, „PETLA” lub „NIE”.  
W przypadku „TAK” w drugiej linii – opisana wyżej ścieżka.

Przykład:
Wejście:
3
6 7 3
0 1
1 5
2 0
2 1
3 2
3 4
4 0
4 3 0
0 1
1 2
2 3
2 2 0
0 1
1 0

Wyjście:
TAK
3 2 0 1 5
NIE
PETLA
*/


#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

void dfs(int state, const vector<vector<int>> &graph, const vector<bool> &visited, vector<int> &color, bool &cycle_found) {
    color[state] = 1; 
    
    
    int u = state / 2;  
    int p = state % 2; 
    
    for (int v : graph[u]) {
        int nxt = v * 2 + (1 - p);  
        if (!visited[nxt])
            continue; 
        
        if (color[nxt] == 1) {
            cycle_found = true;
            return;
        }
        
        if (color[nxt] == 0) {
            dfs(nxt, graph, visited, color, cycle_found);
            if (cycle_found)
                return; 
        }
    }
    
    color[state] = 2;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    
    int tests;  
    cin >> tests;
    

    
    for (int i = 0; i < tests; i++) {

        int n, m, s;
        cin >> n >> m >> s;
        
        vector<vector<int>> graph(n);
        vector<int> num_of_edges(n, 0);
        
        for (int j = 0; j < m; j++){
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
            num_of_edges[x]++;
        }
        
        for (int k = 0; k < n; k++){
            sort(graph[k].begin(), graph[k].end());
        }
        
        int total_states = n * 2;
        vector<bool> visited(total_states, false);
        vector<int> parent(total_states, -1);
 
        int startState = s*2 + 0;
        visited[startState] = true;
        parent[startState] = -1; 
        deque<int> dq;  
        dq.push_back(startState);
 
       
        int final_node_state = -1;
        
        while(!dq.empty()){
            int cur = dq.front();
            dq.pop_front();
            int curr_node = cur / 2; 
            int curr_stability  = cur % 2;    
            
            if (num_of_edges[curr_node] == 0 && curr_stability == 0) {
                final_node_state = cur;
                break; 
            }
            
            for (int v : graph[curr_node]){
                int nextState = v * 2 + (1 - curr_stability);
                if (!visited[nextState]){
                    visited[nextState] = true;
                    parent[nextState] = cur;
                    dq.push_back(nextState);
                }
            }
        }
 
        if (final_node_state != -1){
            vector<int> path;
            int cur = final_node_state;
            while(cur != -1){
                int node = cur / 2;
                path.push_back(node);
                cur = parent[cur];
            }
            reverse(path.begin(), path.end());
 
            cout << "TAK\n";
            for (size_t i = 0; i < path.size(); i++){
                cout << path[i] << (i + 1 < path.size() ? " " : "\n");
            }
            continue;
        }
        vector<int> reachable;
        for (int state = 0; state < total_states; state++){
            if(visited[state])
                reachable.push_back(state);
        }
        vector<int> indeg(total_states, 0);
        for (int st : reachable) {
            int u = st / 2; 
            int p = st % 2; 
            for (int v : graph[u]){
                int nxt = v * 2 + (1 - p);
                if(visited[nxt])
                    indeg[nxt]++;
            }
        }
    vector<int> color(total_states, 0);
    bool cycle_found = false;
    
    for (int state = 0; state < total_states; state++){
        if (visited[state] && color[state] == 0) {
            dfs(state, graph, visited, color, cycle_found);
        }
        if (cycle_found)
            break;
    }

    if (cycle_found)
        cout << "PETLA\n";
    else
        cout << "NIE\n";
 }
}
