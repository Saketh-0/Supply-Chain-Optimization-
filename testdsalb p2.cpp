#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>

using namespace std;

// Edge structure (directed edge)
struct Edge {
    int to, capacity, cost, flow, rev;
};

class Graph {
public:
    int numNodes;
    vector<vector<Edge>> adj;
    vector<int> potential; // Potentials for reduced costs

    Graph(int nodes) : numNodes(nodes), adj(nodes), potential(nodes, 0) {}

    void addEdge(int from, int to, int capacity, int cost) {
        Edge forward = {to, capacity, cost, 0, (int)adj[to].size()};
        Edge backward = {from, 0, -cost, 0, (int)adj[from].size()};
        adj[from].push_back(forward);
        adj[to].push_back(backward);
    }
};

// Dijkstra's algorithm for finding shortest path with reduced costs
bool dijkstra(Graph &graph, int src, int sink, vector<int> &parent, vector<int> &edgeIndex) {
    vector<int> dist(graph.numNodes, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Min-heap 
    pq.push({0, src});
    
    // Main loop 
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > dist[currentNode]) continue;

        for (int i = 0; i < graph.adj[currentNode].size(); ++i) {
            const Edge &edge = graph.adj[currentNode][i];
            int reducedCost = edge.cost + graph.potential[currentNode] - graph.potential[edge.to];
            if (edge.flow < edge.capacity && dist[edge.to] > dist[currentNode] + reducedCost) {
                dist[edge.to] = dist[currentNode] + reducedCost;
                parent[edge.to] = currentNode;
                edgeIndex[edge.to] = i;
                pq.push({dist[edge.to], edge.to});
            }
        }
    }
    // update potetials
    for (int i = 0; i < graph.numNodes; ++i) {
        if (dist[i] < INT_MAX) {
            graph.potential[i] += dist[i];
        }
    }

    return dist[sink] < INT_MAX;
}

// Successive Shortest Path algorithm for Minimum Cost Maximum Flow
pair<int, int> minCostMaxFlow(Graph &graph, int src, int sink) {
    int totalFlow = 0, totalCost = 0;
    vector<int> parent(graph.numNodes);
    vector<int> edgeIndex(graph.numNodes);

    //finding paths from source to sink until no more augmenting paths are found
    while (dijkstra(graph, src, sink, parent, edgeIndex)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            int idx = edgeIndex[v];
            pathFlow = min(pathFlow, graph.adj[u][idx].capacity - graph.adj[u][idx].flow); //vottleneck flow checker
        }

        for (int v = sink; v != src; v = parent[v]) {
            int u = parent[v];
            int idx = edgeIndex[v];
            graph.adj[u][idx].flow += pathFlow;
            graph.adj[v][graph.adj[u][idx].rev].flow -= pathFlow;
            totalCost += pathFlow * graph.adj[u][idx].cost;
        }

        totalFlow += pathFlow;
    }

    return {totalFlow, totalCost};
}

int main() {

    string from, to;
    int capacity, cost;
    vector<tuple<string, string, int, int>> ed;
    unordered_map<string, int> nodeMap;
    set<string> uniqueNodes;   
    //input
    cout << "Enter the routes in the format (from, to, capacity, cost): enter stop to stop\n";
    while (true) {
        cin >> from;
        if (from == "stop") {
            break;
        }
        cin >> to >> capacity >> cost;

        if (capacity <= 0 || cost < 0) {
            cout << "Invalid route input. Capacity must be greater than 0 and cost must be non-negative.\n";
            continue;
        }
        ed.push_back({from, to, capacity, cost});
        uniqueNodes.insert(from);
        uniqueNodes.insert(to);
    }

    if (ed.empty()) {
    cout << "No valid routes were entered. Exiting...\n";
    return 0;
    }



    int id = 0;
    for (const string& node : uniqueNodes) {
        nodeMap[node] = id++;
    }

    int numNodes = uniqueNodes.size();

    Graph supplyChain(numNodes);
    for (const auto &[from, to, capacity, cost] : ed) {
        supplyChain.addEdge(nodeMap[from], nodeMap[to], capacity, cost);
    }
    char ch;
    while(true){
    string win, cinn;
    cout << "Enter the source warehouse's name: ";
    cin >> win;

    cout << "Enter the consumer's name: ";
    cin >> cinn;

    if(nodeMap.find(win) == nodeMap.end() || nodeMap.find(cinn) == nodeMap.end()) {
            cout << "Invalid source or consumer. Please try again." << endl;
            continue;
        }

    auto [maxFlow, minCost] = minCostMaxFlow(supplyChain, nodeMap[win], nodeMap[cinn]);

    //output
    if (maxFlow == 0) {
        cout << "No valid path found from " << win << " to " << cinn << ". No flow is possible.\n";
    }else{
    cout << "The maximum flow that can be sent from the source warehouse to the consumer is: " << maxFlow << endl;
    cout << "The minimum cost to achieve this flow is: " << minCost << endl;
    }
    cout<<endl;
    cout<<"do you wish to calculate for a different route.(Y/N)"<<endl;
    cin>>ch;

    if(ch=='n' || ch=='N') break;
    }

    return 0;
}
