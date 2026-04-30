#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<string> countryNames;

    Graph(vector<Edge> const &edges, vector<string> const &names) {
        adjList.resize(SIZE);
        countryNames = names;


        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }
 
    void printTradeNetwork() {
        cout << "Global Trade Network:" << endl;
        cout << "=====================" << endl;

        for (int i = 0; i < adjList.size(); i++) {
            cout << countryNames[i] << " connects to:" << endl;

            for (Pair v : adjList[i]) {
                cout << "  -> " << countryNames[v.first]
                     << " (Trade Cost: " << v.second << ")" << endl;
            }

            cout << endl;
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);

        cout << "DFS starting from vertex " << start << ":" << endl;
        DFSHelper(start, visited);
        cout << endl ;
    }
    void DFSHelper(int vertex, vector<bool> &visited) {
       visited[vertex] = true;

        cout << "Visiting " << countryNames[vertex] << endl;

        for (Pair neighbor : adjList[vertex]) {
            int nextVertex = neighbor.first;
            int tradeCost = neighbor.second;

            if (!visited[nextVertex]) {
                cout << "  -> Trade can expand to " << countryNames[nextVertex]
                     << " (Trade Cost: " << tradeCost << ")" << endl;

                DFSHelper(nextVertex, visited);
            }
        } 
    }

void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();

            cout << vertex << " ";

            for (Pair neighbor : adjList[vertex]) {
                int nextVertex = neighbor.first;

                if (!visited[nextVertex]) {
                    visited[nextVertex] = true;
                    q.push(nextVertex);
                }
            }
        }

        cout << endl;
    }
    int minDistance(vector<int> &dist, vector<bool> &visited) {
    int min = 999999;
    int minIndex = -1;

    for (int i = 0; i < SIZE; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void shortestPath(int start) {
    vector<int> dist(SIZE, 999999);
    vector<bool> visited(SIZE, false);

    dist[start] = 0;

    for (int count = 0; count < SIZE - 1; count++) {
        int u = minDistance(dist, visited);

        if (u == -1) {
            break;
        }

        visited[u] = true;

        for (Pair neighbor : adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && dist[u] != 999999 &&
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    cout << "Lowest Trade Cost Paths from " << countryNames[start] << ":" << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << countryNames[start] << " -> " << countryNames[i]
             << " : " << dist[i] << endl;
    }

    cout << endl;
}
};



int main() {
    vector<string> countries = {
        "United States",
        "China",
        "South Korea",
        "Japan",
        "Germany",
        "Vietnam",
        "India",
        "Brazil",
        "Canada"
    };

    vector<Edge> edges = {
        {0, 1, 8},
        {0, 2, 21},
        {1, 2, 6},
        {1, 3, 5},
        {1, 4, 4},
        {2, 7, 11},
        {2, 8, 8},
        {3, 4, 9},
        {5, 6, 10},
        {5, 7, 15},
        {5, 8, 5},
        {6, 7, 3},
        {6, 8, 7}
    };


    Graph graph(edges, countries);

    graph.printTradeNetwork();
    graph.DFS(0);
    graph.BFS(0);
    graph.shortestPath(0);
    return 0;
}