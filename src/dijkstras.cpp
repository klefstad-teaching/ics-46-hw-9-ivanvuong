#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVertices = G.size();
    std::vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous[source] = -1;
    priority_queue<pair<int,int>> minHeap;
    minHeap.push({source, 0});
    while (!minHeap.empty())
    {
        int u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge : G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    std::vector<int> shortest_path;
    while (destination != -1)
    {
        shortest_path.insert(shortest_path.begin(), destination);
        destination = previous[destination];
    }
    return shortest_path;
}

void print_path(const vector<int>& path, int total_cost) {
    for (int i = 0; i < path.size(); i++) 
    {
        cout << path[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total_cost << endl;
}