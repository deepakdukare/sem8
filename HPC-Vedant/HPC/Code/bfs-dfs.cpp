#include <iostream>
#include <vector>
#include <queue>
#include <atomic>
#include <chrono>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

void DFS(int node, vector<bool>& visited, const vector<vector<int>>& graph) {
    visited[node] = true;
    for (int neighbor : graph[node])
        if (!visited[neighbor])
            DFS(neighbor, visited, graph);
}


void ParallelDFS(int node, vector<bool>& visited, const vector<vector<int>>& graph) {
    visited[node] = true;
    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++)
        if (!visited[graph[node][i]])
            ParallelDFS(graph[node][i], visited, graph);
}


void BFS(int start, const vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int neighbor : graph[node])
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
    }
}


void ParallelBFS(int start, const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<atomic<bool>> visited(n);
    for (auto& v : visited) v = false;
    visited[start] = true;
    vector<int> current_level = {start};
    while (!current_level.empty()) {
        vector<int> next_level;
        #pragma omp parallel
        {
            vector<int> local_next;
            #pragma omp for nowait schedule(dynamic)
            for (int i = 0; i < current_level.size(); ++i) {
                int node = current_level[i];
                for (int neighbor : graph[node])
                    if (!visited[neighbor].exchange(true))
                        local_next.push_back(neighbor);
            }
            #pragma omp critical
            next_level.insert(next_level.end(), local_next.begin(), local_next.end());
        }
        current_level = move(next_level);
    }
}


int main() {
    int V = 10000;
    vector<vector<int>> graph(V);
    srand(time(0));
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (rand() % 2 == 0) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    vector<bool> visited(V, false);
    auto t1 = high_resolution_clock::now();
    DFS(0, visited, graph);
    auto t2 = high_resolution_clock::now();
    cout << "\nSequential DFS time: "
         << duration<double, milli>(t2 - t1).count() << " ms\n";

    fill(visited.begin(), visited.end(), false);

    t1 = high_resolution_clock::now();
    omp_set_num_threads(4);
    ParallelDFS(0, visited, graph);
    t2 = high_resolution_clock::now();
    cout << "\nParallel DFS time: "
         << duration<double, milli>(t2 - t1).count() << " ms\n";

    t1 = high_resolution_clock::now();
    BFS(0, graph);
    t2 = high_resolution_clock::now();
    cout << "\nSequential BFS time: "
         << duration<double, milli>(t2 - t1).count() << " ms\n";

    t1 = high_resolution_clock::now();
    ParallelBFS(0, graph);
    t2 = high_resolution_clock::now();
    cout << "\nParallel BFS time: "
         << duration<double, milli>(t2 - t1).count() << " ms\n";

    return 0;
}
