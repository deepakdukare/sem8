#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int n;

// Parallel BFS
void parallelBFS(int start) {
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Parallel BFS Traversal: ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            if (graph[node][i]) {
                #pragma omp critical
                {
                    if (!visited[i]) {
                        visited[i] = true;
                        q.push(i);
                    }
                }
            }
        }
    }
    cout << endl;
}

// Parallel DFS
void parallelDFS(int start) {
    vector<bool> visited(n, false);
    stack<int> s;

    s.push(start);
    visited[start] = true;

    cout << "Parallel DFS Traversal: ";

    while (!s.empty()) {
        int node;

        #pragma omp critical
        {
            node = s.top();
            s.pop();
        }

        cout << node << " ";

        #pragma omp parallel for
        for (int i = n - 1; i >= 0; i--) {
            if (graph[node][i]) {
                #pragma omp critical
                {
                    if (!visited[i]) {
                        visited[i] = true;
                        s.push(i);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter adjacency matrix (0/1):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    parallelBFS(0);
    parallelDFS(0);

    return 0;
}

