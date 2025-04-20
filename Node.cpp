#include "Node.hpp"

Node::Node(int type_id, node_type type, std::string name) : type_id(type_id), type(type), name(name) {}

int Node::get_id() const {
    return type_id;
}

node_type Node::get_type() const {
    return type;
}

std::string Node::get_name() const {
    return name;
}

Path::Path(int type_id, std::string name, int start_location, int end_location, double length, int max_speed, int max_vehicles, Intersection* intersection)
    : Node(type_id, PATH, name), start_location(start_location), end_location(end_location), length(length), max_speed(max_speed), max_vehicles(max_vehicles), intersection(intersection) {}

int Path::get_start() const {
    return start_location;
}

int Path::get_end() const {
    return end_location;
}

double Path::get_length() const {
    return length;
}

int Path::get_max_speed() const {
    return max_speed;
}

int Path::get_max_vehicles() const {
    return max_vehicles;
}

void Path::set_intersection(Intersection* intersection) {
    this->intersection = intersection;
}

void Path::set_max_vehicles(int maxVehicles) {
    max_vehicles = maxVehicles;
}

Intersection::Intersection(int type_id, std::string name) : Node(type_id, INTERSECTION, name), max_vehicles(0) {}

int Intersection::get_max_vehicles() const {
    return max_vehicles;
}

void Intersection::Add(Path* path, bool is_entrance) {
    if (is_entrance) {
        entrance_paths.push_back(path);
    } else {
        exit_paths.push_back(path);
    }
    path->set_intersection(this);
    path->set_max_vehicles(max_vehicles);
}

bool Intersection::check(Path* entrance, Path* exit, double& length, double& avg_speed) {
    if (avg_speed > 100) {
        auto entrance_it = std::find(entrance_paths.begin(), entrance_paths.end(), entrance);
        auto exit_it = std::find(exit_paths.begin(), exit_paths.end(), exit);

        if (entrance_it != entrance_paths.end() && exit_it != exit_paths.end()) {
            length = (*entrance_it)->get_length();
            avg_speed = static_cast<double>((*entrance_it)->get_max_speed() + (*exit_it)->get_max_speed()) / 2;
            return true;
        }
    }
    return false;
}

const std::vector<Path*>& Intersection::getEntrancePaths() const {
    return entrance_paths;
}

const std::vector<Path*>& Intersection::getExitPaths() const {
    return exit_paths;
}

void Intersection::setEntrancePaths(const std::vector<Path*>& paths) {
    entrance_paths = paths;
}

void Intersection::setExitPaths(const std::vector<Path*>& paths) {
    exit_paths = paths;
}

void Intersection::setMaxVehicles(int maxVehicles) {
    max_vehicles = maxVehicles;
}


Location::Location(int type_id, std::string name) : Node(type_id, LOCATION, name) {}

int Location::getID() const {
    return get_id();
}
