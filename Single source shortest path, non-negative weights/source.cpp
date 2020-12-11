#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

#define umap unordered_map
#define debug(x) cout<<#x<<" -> "<<x<<'\n'

void fast() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

umap<int, umap<int, int>> build_graph(int num_nodes, int num_sides) {
    umap<int, umap<int, int>> graph;
    for (int i = 0; i < num_sides; i++) {
        int nodeIn, nodeOut, weight;
        string s;
        getline(cin, s);
        sscanf(s.c_str(), "%d %d %d", &nodeIn, &nodeOut, &weight);

        // if hashmap empty initialize it
        // if (graph.find(nodeIn) == graph.end()) {
        //     umap<int, int> auxMap;
        //     graph[nodeIn] = auxMap;
        // }
        // umap<int, int> tempMap = graph[nodeIn];
        // tempMap[nodeOut] = weight;
        graph[nodeIn][nodeOut] = weight;
    }
    return graph;
}

int minDistance(vector<int> dist, vector<bool> visited, int num_nodes) {
    int min = INT32_MAX, min_index;

    for (int neighbour = 0; neighbour < num_nodes; neighbour++)
        if (visited[neighbour] == false && dist[neighbour] <= min) {
            min = dist[neighbour];
            min_index = neighbour;
        }
    return min_index;
}

vector<int> dijkstra (umap<int, umap<int, int>> graph, int source, int num_nodes) {
    vector<int> dist(num_nodes, INT32_MAX);
    vector<bool> visited (num_nodes, false);
    dist[source] = 0;

    for (int count = 0; count < num_nodes - 1; count++) {
        int min_node = minDistance(dist, visited, num_nodes);

        visited[min_node] = true;

        for (int neighbour = 0; neighbour < num_nodes; neighbour++)
            if (!visited[neighbour] && graph[min_node][neighbour] &&
                dist[min_node] != INT32_MAX &&
                dist[min_node] + graph[min_node][neighbour] < dist[neighbour])

                dist[neighbour] = dist[min_node] + graph[min_node][neighbour];
    }

    return dist;
}

int main() {
    fast();
    
    string s;
    int num_nodes, num_sides, num_query, start_node;
    while (getline(cin, s)) {
        sscanf(s.c_str(), "%d %d %d %d", &num_nodes, &num_sides, &num_query, &start_node);
        if (!num_nodes || !num_sides)
            continue;
        // declare graph
            umap<int, umap<int, int>> graph = build_graph(num_nodes, num_sides);
        // now we should call dijkstra
        vector<int> dijkstra_results = dijkstra(graph, start_node, num_nodes);
        if (!num_query)
            continue;
        for (int j = 0; j < num_query; j++) {
            int node_to_query;
            getline(cin, s);
            sscanf(s.c_str(), "%d", &node_to_query);
            if (dijkstra_results[node_to_query] == INT32_MAX)
                cout << "Impossible" << endl;
            else 
                cout << dijkstra_results[node_to_query] << endl;
        }
        cout << endl;
    }

    return 0;
}