#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{

}

void print_path(const vector<int>& v, int total)
{
    for (int i : v)
    {
        cout << i << endl;
        cout << "Total cost is " << total;
    }
}