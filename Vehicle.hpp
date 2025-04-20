#pragma once
#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Node.hpp"
#include "Pointed_Graph.hpp"

class Vehicle {
private:
    Location start_location;
    Location end_location;
    int average_speed;
    int current_speed;

public:
    Vehicle(Location start, Location end, int avg_speed);


    void setStartLocation(Location start);
    Location getStartLocation() const;

    void setEndLocation(Location end);
    Location getEndLocation() const;

    void setAverageSpeed(int avg_speed);
    int getAverageSpeed() const;

    std::vector<int> FindShortestPath(Pointed_Graph& graph, bool minimize_distance);

};

#endif 
