/**
    Problem Statement:

    You are working on a network routing application. The network is represented as a directed graph where each node represents a router and each edge represents a direct connection between two routers. Each edge has a certain cost associated with it, representing the cost of sending a packet along that connection.

    You need to implement the following operations:

        AddRouter(router_id): Adds a new router to the network.

        AddConnection(router_id1, router_id2, cost): Adds a direct connection from router_id1 to router_id2 with the specified cost. If a connection already exists, update the cost.

        RemoveConnection(router_id1, router_id2): Removes the direct connection from router_id1 to router_id2.

        GetLeastCostPath(router_id1, router_id2): Returns the path (sequence of routers) with the least total cost from router_id1 to router_id2. If there are multiple paths with the same least cost, return any.

        GetLeastCost(router_id1, router_id2): Returns the least total cost from router_id1 to router_id2.

    You can assume that all router IDs are positive integers and all costs are positive integers.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

class Network {
private:
    // Adjacency list representation of the graph
    std::unordered_map<int, std::unordered_map<int, int>> adj_list;

public:
    void AddRouter(int router_id) {
        adj_list[router_id]; // Adds an empty map for the new router
    }

    void AddConnection(int router_id1, int router_id2, int cost) {
        adj_list[router_id1][router_id2] = cost; // Adds/updates the connection
    }

    void RemoveConnection(int router_id1, int router_id2) {
        adj_list[router_id1].erase(router_id2); // Removes the connection
    }

    std::vector<int> GetLeastCostPath(int router_id1, int router_id2) {
        // Dijkstra's algorithm
        std::unordered_map<int, int> dist;
        std::unordered_map<int, int> prev;
        using pii = std::pair<int, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<>> pq;

        for (const auto& [router_id, _] : adj_list) {
            dist[router_id] = std::numeric_limits<int>::max();
        }
        dist[router_id1] = 0;
        pq.push({0, router_id1});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& [v, cost] : adj_list[u]) {
                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Build the shortest path
        std::vector<int> path;
        for (int u = router_id2; u != router_id1; u = prev[u]) {
            path.push_back(u);
        }
        path.push_back(router_id1);
        std::reverse(path.begin(), path.end());
        return path;
    }

    int GetLeastCost(int router_id1, int router_id2) {
        auto path = GetLeastCostPath(router_id1, router_id2);
        int cost = 0;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            cost += adj_list[path[i]][path[i + 1]];
        }
        return cost;
    }
};