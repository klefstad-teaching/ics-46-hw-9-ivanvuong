#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.size();
    std::vector<int> distances;
    std::vector<bool> visited; 

    distances.assign(n, INF);
    previous.resize(n, -1);
    visited.resize(n, false);

    priority_queue<Edge> pq;
    pq.push(Edge(source,0));
    distances[source] = 0;

    while (!pq.empty())
    {
        Edge e = pq.top();
        pq.pop();

        int u = e.src;

        if (visited[u])
            continue;

        visited[u] = true;

        for (auto neighbor : G[u])
        {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Edge(v,distances[v]));
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