#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <string>
#include <algorithm>

enum node_type {
    LOCATION,
    PATH,
    INTERSECTION
};

class Node {
public:
    Node(int type_id, node_type type, std::string name);
    virtual ~Node() = default;

    virtual int get_id() const; 
    virtual node_type get_type() const;
    virtual std::string get_name() const;

protected:
    int type_id;
    node_type type;
    std::string name;
};

class Path;

class Intersection : public Node {
public:
    Intersection(int type_id, std::string name);

    int get_max_vehicles() const;
    void Add(Path* path, bool is_entrance);
    bool check(Path* entrance, Path* exit, double& length, double& avg_speed);
    const std::vector<Path*>& getEntrancePaths() const;
    const std::vector<Path*>& getExitPaths() const;
    void setEntrancePaths(const std::vector<Path*>& paths);
    void setExitPaths(const std::vector<Path*>& paths);
    void setMaxVehicles(int maxVehicles);

private:
    std::vector<Path*> entrance_paths;
    std::vector<Path*> exit_paths;
    int max_vehicles;
};

class Path : public Node {
public:
    Path(int type_id, std::string name, int start_location, int end_location, double length, int max_speed, int max_vehicles, Intersection* intersection);

    int get_start() const;
    int get_end() const;
    double get_length() const;
    int get_max_speed() const;
    int get_max_vehicles() const;

    void set_intersection(Intersection* intersection);
    void set_max_vehicles(int maxVehicles);

private:
    int start_location;
    int end_location;
    double length;
    int max_speed;
    int max_vehicles;
    Intersection* intersection;
};

class Location : public Node {
public:
    Location(int type_id, std::string name);
    int getID() const;
};

#endif
