#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

vector<int> bfs(const vector<vector<int>>& graph, int start, vector<int>& dist, vector<int>& parent) {
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
                parent[v] = u;
                q.push(v);
                
            }
        }
    }

    return order;
}

string nodeColor(int dist) {
    if (dist == 0) return "gold";
    if (dist == -1) return "lightgray";
    if (dist == 1) return "lightblue";
    if (dist == 2) return "lightgreen";
    if (dist == 3) return "lightpink";
    return "white";
}

void outputDot(
    const vector<pair<int, int>>& edges,
    const vector<int>& dist,
    const vector<int>& parent,
    const string& filename
) {
    ofstream fout(filename);
    int n = static_cast<int>(dist.size()) - 1;
    set<pair<int, int>> treeEdges;

    for (int v = 1; v <= n; ++v) {
        if (parent[v] != -1) {
            int a = min(parent[v], v);
            int b = max(parent[v], v);
            treeEdges.insert({a, b});
        }
    }

    fout << "graph G {\n";
    fout << "    layout=neato;\n";
    fout << "    overlap=false;\n";
    fout << "    splines=true;\n";
    fout << "    node [shape=circle, style=filled, fontname=\"Consolas\"];\n";
    fout << "    edge [fontname=\"Consolas\"];\n\n";

    for (int i = 1; i <= n; ++i) {
        fout << "    " << i
             << " [label=\"" << i << "\\nd=" << dist[i]
             << "\", fillcolor=\"" << nodeColor(dist[i]) << "\"];\n";
    }

    fout << '\n';

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        int a = min(u, v);
        int b = max(u, v);

        fout << "    " << u << " -- " << v;
        if (treeEdges.count({a, b})) {
            fout << " [color=red, penwidth=3]";
        }
        fout << ";\n";
    }

    fout << "}\n";
}




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, start;
    cin >> n >> m >> start;

    vector<vector<int>> graph(n + 1);
    vector<pair<int, int>> edges;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back({u, v});
    }

    for (int i = 1; i <= n; ++i) {
        sort(graph[i].begin(), graph[i].end());
    }

    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, -1);
    vector<int> order = bfs(graph, start, dist, parent);

    cout << "BFS order:";
    for (int x : order) {
        cout << ' ' << x;
    }
    cout << '\n';

    cout << "Distance from " << start << ":\n";
    for (int i = 1; i <= n; ++i) {
        cout << i << ": " << dist[i] << '\n';
    }

    outputDot(edges, dist, parent, "graph.dot");
    cout << "Visualization DOT file written to graph.dot\n";

    return 0;
}
