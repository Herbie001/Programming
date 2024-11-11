#include "Graph.h"
#include "iostream"
#include <fstream>
#include <istream>
#include <unordered_set>
#include <fstream>
#include <sstream> 
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <queue>

Graph::Graph(const char* const & edgelist_csv_fn) {
    ifstream file(edgelist_csv_fn);
    string line;
    while(getline(file, line)) {  // read one line from the file
        istringstream ss(line);      // create istringstream of current line
        string first, second, third; 
        // insert node
        getline(ss, first, ',');    
        // insert adjacent node
        getline(ss, second, ',');    
        // weight of edge {first,second}
        getline(ss, third, '\n');    
        // cout << "First: " << first << ", Second: " << second << ", Third: " << third << endl;
        // insert first as string, second and third in nested unordered_map<second, third>
        double weight = stod(third);
        insertNodesToVector(first, second, nodesVector);
        insertToAdjList(first, second, weight, adj);
        // Called twice swapping order of node1&node2 which gives us exactly what we want.
        insertToAdjList(second,first,weight,adj);
        // adj[first][second] = weight;
    }
}

/**
 * Checking existence of node in vector.
 */
bool Graph::nodeIsInVector(string & node, vector<string> & nodesVector) {
    vector<string>::iterator itr = nodesVector.begin();
    vector<string>::iterator end = nodesVector.end();
    while(itr != end) {
        if((*itr) == node) {
            return false;
        }
        ++itr;
    }
    return true;
}

/**
 * Can create a vector<vector<int>> where indicies will correlate to degree of node, 
 * and nested vector is the set of nodes correlated to that degree.
 */
void Graph::createDegreeVector(unordered_map<string, unordered_map<string, double>>& adj, vector<vector<string>>& degreeVec) {
    for (const auto& pair1 : adj) {
        const string& node1 = pair1.first;
        const size_t degree = pair1.second.size(); // Degree of the node is the size of its adjacency list
        degreeVec[degree].push_back(node1);
    }
}

/**
 * Insert nodes into the node vector while also checking existence before.
 */
void Graph::insertNodesToVector(string node1, string node2, vector<string> & nodesVector) {
    if(nodesVector.size() == 0){
        if(node1 != node2) {
            nodesVector.push_back(node1);
            nodesVector.push_back(node2);
        } else {
            nodesVector.push_back(node1);
        }
    }
    if(nodeIsInVector(node1, nodesVector) == true) {
        nodesVector.push_back(node1);
    }
    if(nodeIsInVector(node2, nodesVector) == true) {
        nodesVector.push_back(node2);
    }
}

/**
 * Insertion function for adj. list.
 */
void Graph::insertToAdjList(string node1, string node2, double edgeWeight, unordered_map<string, unordered_map<string, double>>& adj) {
    if (adj.empty()) {
        adj[node1][node2] = edgeWeight;
    } else {
        bool found = false;
        for (auto& pair : adj) {
            const string& node_u = pair.first;
            if (node_u == node1) {
                found = true;
                pair.second[node2] = edgeWeight;
                break;
            }
        }
        if (!found) {
            adj[node1][node2] = edgeWeight;
        }
    }
}

unsigned int Graph::num_nodes() {
    // Return nodes.size()
    return nodesVector.size();
}

vector<string> Graph::nodes() {
    // Return the nodes vector.
    return nodesVector;
}

unsigned int Graph::num_edges() {
    unsigned int totalEdges = 0;
    for (const auto& node : nodesVector) {
        totalEdges += num_neighbors(node);
    }
    // Since each edge is counted twice (once for each node), divide by 2
    return totalEdges / 2;
}

unsigned int Graph::num_neighbors(string const & node_label) {
    // Can get this by checking size of first.second of adj.
    unsigned int numOfNeighbors = 0;
    if(adj.find(node_label) != adj.end()) {
        numOfNeighbors = adj[node_label].size();
        return numOfNeighbors;
    }
    return numOfNeighbors;
}

double Graph::edge_weight(string const & u_label, string const & v_label) {
    // Can get this from using adj. Just checking existence before returning "double weight = adj[u_label, v_label]"
    double edgeWeight = -1;
    auto u_iter = adj.find(u_label); // Find the node u_label in the outer map
    if (u_iter != adj.end()) {
        auto v_iter = u_iter->second.find(v_label); // Find the node v_label in the inner map of u_label
        if (v_iter != u_iter->second.end()) {
            edgeWeight = v_iter->second; // Assign the edge weight
        }
    }
    return edgeWeight;
}

vector<string> Graph::neighbors(string const & node_label) {
    // Can use adj. for this too.
    vector<string> theNeighbors; 
    if(adj.find(node_label) != adj.end()) {
        for(const auto& neighbor : adj[node_label]) {
            theNeighbors.push_back(neighbor.first);
        }
    }
    return theNeighbors;
}

vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    vector<string> path;
    unordered_set<string> visited;
    unordered_map<string, string> parent;
    queue<string> q;
    q.push(start_label);
    visited.insert(start_label);
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        if (curr == end_label) {
            // Reconstruct path 
            while (curr != start_label) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(start_label);
            reverse(path.begin(), path.end());
            return path;
        }
        for (const auto& neighbor : adj[curr]) {
            if (visited.find(neighbor.first) == visited.end()) {
                q.push(neighbor.first);
                visited.insert(neighbor.first);
                parent[neighbor.first] = curr;
            }
        }
    }
    // If end_label is unreachable
    return {};
}

vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    vector<tuple<string,string,double>> path;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    unordered_map<string, double> distanceMap;
    unordered_map<string, string> parent;

    for(const auto& node : adj) {
        distanceMap[node.first] = numeric_limits<double>::max();
    }
    distanceMap[start_label] = 0;
    pq.push({0.0, start_label});
    while(!pq.empty()) {
        string current = pq.top().second;
        pq.pop();
        if(current == end_label) {
            // Reconstruct the path
            string currentNode = current;
            while(currentNode != start_label) {
                string previousNode = parent[currentNode];
                double weight = adj[previousNode][currentNode];
                tuple<string,string,double> tupleToAdd = make_tuple(previousNode, currentNode, weight);
                path.push_back(tupleToAdd);
                currentNode = previousNode;
            }
            // Add self-loop if start_label is equal to end_label
            // If you don't want to include the trivial path, remove conditional below.
            if (start_label == end_label) {
                path.push_back(make_tuple(start_label, start_label, -1));
            }
            // Reverse the path
            reverse(path.begin(), path.end());
            break;
        }
        // Comparing distances and updating if necessary and pushing onto pq.
        for(const auto& neighbor : adj[current]) {
            double weight = neighbor.second;
            if(distanceMap[current] + weight < distanceMap[neighbor.first]) {
                distanceMap[neighbor.first] = distanceMap[current] + weight;
                parent[neighbor.first] = current;
                pq.push({distanceMap[neighbor.first], neighbor.first});
            }
        }
    }
    return path;
}

void Graph::dfs(const string& node, double threshold, unordered_map<string, bool>& visited, vector<string>& component) {
    visited[node] = true;
    component.push_back(node);

    // Visit all neighbors of the current node
    for (const auto& neighbor : adj[node]) {
        if (!visited[neighbor.first] && neighbor.second <= threshold) {
            dfs(neighbor.first, threshold, visited, component);
        }
    }
}

vector<vector<string>> Graph::connected_components(double const & threshold) {
    vector<vector<string>> connectedComps;
    unordered_map<string, bool> visited;

    // Mark all nodes as not visited initially
    for (const string& node : nodesVector) {
        visited[node] = false;
    }

    // Perform DFS to find connected components
    for (const string& node : nodesVector) {
        if (!visited[node]) {
            vector<string> component;
            dfs(node, threshold, visited, component);
            connectedComps.push_back(component);
        }
    }

    return connectedComps;
}

double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
    if (start_label == end_label) {
        return 0;
    }

    unordered_map<string, double> max_edge_weights;
    unordered_map<string, double> distances = dijkstra(start_label, max_edge_weights);

    if (distances[end_label] == numeric_limits<double>::max()) {
        return -1;  // No path exists
    }

    return max_edge_weights[end_label];
}

unordered_map<string, double> Graph::dijkstra(string const & start_label, unordered_map<string, double> & max_edge_weights) {
    // Priority queue for Dijkstra's algorithm
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
    unordered_map<string, double> distances;
    unordered_map<string, bool> visited;

    for (const auto& node : adj) {
        distances[node.first] = numeric_limits<double>::max();
        max_edge_weights[node.first] = 0.0;
    }
    distances[start_label] = 0;
    pq.push({0.0, start_label});

    while (!pq.empty()) {
        string current = pq.top().second;
        double current_distance = pq.top().first;
        pq.pop();

        if (visited[current]) {
            continue;
        }
        visited[current] = true;

        for (const auto& neighbor : adj[current]) {
            string next_node = neighbor.first;
            double edge_weight = neighbor.second;
            double new_distance = current_distance + edge_weight;

            if (new_distance < distances[next_node]) {
                distances[next_node] = new_distance;
                max_edge_weights[next_node] = max(max_edge_weights[current], edge_weight);
                pq.push({new_distance, next_node});
            }
        }
    }

    return distances;
}