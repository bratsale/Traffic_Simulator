#include "Vehicle.hpp"
#include <limits>
#include <algorithm>

Vehicle::Vehicle(Location start, Location end, int avg_speed)
    : start_location(start), end_location(end), average_speed(avg_speed) {
    current_speed = 0.0f; 
}

void Vehicle::setStartLocation(Location start) {
    start_location = start;
}

Location Vehicle::getStartLocation() const {
    return start_location;
}

void Vehicle::setEndLocation(Location end) {
    end_location = end;
}

Location Vehicle::getEndLocation() const {
    return end_location;
}

void Vehicle::setAverageSpeed(int avg_speed) {
    average_speed = avg_speed;
}

int Vehicle::getAverageSpeed() const {
    return average_speed;
}

#include <algorithm> 
#include <iostream>  

std::vector<int> Vehicle::FindShortestPath(Pointed_Graph& mreza, bool minimizirajDistancu) {
    auto adjList = mreza.getAdjList();
    int V = mreza.getNodes().size();
    std::vector<double> dist(V, std::numeric_limits<double>::infinity());
    std::vector<int> prethodnik(V, -1);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    int startIdx = -1;
    int endIdx = -1;
    auto nodes = mreza.getNodes();
    for (size_t i = 0; i < nodes.size(); ++i) {
        Location* locNode = dynamic_cast<Location*>(nodes[i]);
        if (locNode) {
            std::cout << "Node ID: " << locNode->getID() << ", Index: " << i << std::endl;
            if (locNode->getID() == start_location.getID()) startIdx = i;
            if (locNode->getID() == end_location.getID()) endIdx = i;
        }
    }

    if (startIdx == -1 || endIdx == -1) {
        std::cout << "Greška: Početna ili krajnja tačka nije pronađena u saobraćajnoj mreži" << std::endl;
        return {};
    }

    std::cout << "Startni indeks: " << startIdx << ", Krajnji indeks: " << endIdx << std::endl;

    dist[startIdx] = 0;
    pq.push(std::make_pair(0, startIdx));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == endIdx) break; 

        for (auto& put : adjList.at(u)) {
            int v = put->get_end();
            double dodatnaVrijednost;
            if (minimizirajDistancu) {
                dodatnaVrijednost = put->get_length();
            } else {
                int maxSpeed = std::min(put->get_max_speed(), average_speed);
                dodatnaVrijednost = (put->get_length() * 60) / static_cast<double>(maxSpeed);
            }

            if (dist[v] > dist[u] + dodatnaVrijednost) {
                dist[v] = dist[u] + dodatnaVrijednost;
                prethodnik[v] = u;
                pq.push(std::make_pair(dist[v], v));
                std::cout << "Ažuriram putanju: " << v << " sa distancom: " << dist[v] << std::endl;
            }
        }
    }

    std::vector<int> putanja;
    for (int at = endIdx; at != -1; at = prethodnik[at])
        putanja.push_back(at);
    std::reverse(putanja.begin(), putanja.end());

    if (putanja.size() == 1 && putanja[0] == endIdx) {
        std::cout << "Pronađena putanja sadrži samo krajnji čvor." << std::endl;
    }

    return putanja;
}
