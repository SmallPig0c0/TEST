#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> bfs(const vector<vector<int>>& graph, int start, vector<int>& dist) {
    int n = static_cast<int>(graph.size()) - 1;
    vector<int> order;
    vector<bool> visited(n + 1, false);
    queue<int> q;

    visited[start] = true;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, start;
    cin >> n >> m >> start;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        sort(graph[i].begin(), graph[i].end());
    }

    vector<int> dist(n + 1, -1);
    vector<int> order = bfs(graph, start, dist);

    cout << "BFS order:";
    for (int x : order) {
        cout << ' ' << x;
    }
    cout << '\n';

    cout << "Distance from " << start << ":\n";
    for (int i = 1; i <= n; ++i) {
        cout << i << ": " << dist[i] << '\n';
    }

    return 0;
}
