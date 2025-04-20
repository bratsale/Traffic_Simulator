#include "Pointed_Graph.hpp"

Pointed_Graph::Pointed_Graph(const std::vector<Node*>& initial_nodes) : nodes(initial_nodes) {
    for (const auto& node : initial_nodes) {
        if (node->get_type() == PATH) {
            int start = dynamic_cast<Path*>(node)->get_start();
            adjList[start].push_back(dynamic_cast<Path*>(node));

            int end = dynamic_cast<Path*>(node)->get_end();
            adjList[end].push_back(dynamic_cast<Path*>(node));
        }
    }
}

void Pointed_Graph::addNode(Node* node) {
    nodes.push_back(node);
    if (node->get_type() == PATH) {
        int start = dynamic_cast<Path*>(node)->get_start();
        adjList[start].push_back(dynamic_cast<Path*>(node));

        int end = dynamic_cast<Path*>(node)->get_end();
        adjList[end].push_back(dynamic_cast<Path*>(node));
    }
}

void Pointed_Graph::addPath(Path* path) {
    nodes.push_back(path);

    int start = path->get_start();
    adjList[start].push_back(path);

    int end = path->get_end();
    adjList[end].push_back(path);
}

const std::vector<Node*>& Pointed_Graph::getNodes() const {
    return nodes;
}

const std::unordered_map<int, std::vector<Path*>>& Pointed_Graph::getAdjList() const {
    return adjList;
}

void Pointed_Graph::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Ne moze se otvoriti " + filename);
    }

    out << nodes.size() << "\n";

    for (const auto& node : nodes) {
        out << static_cast<int>(node->get_type()) << " "
            << node->get_id() << " "
            << node->get_name().length() << " "
            << node->get_name() << "\n";

        if (node->get_type() == PATH) {
            auto* path = dynamic_cast<Path*>(node);
            out << path->get_start() << " "
                << path->get_end() << " "
                << path->get_length() << " "
                << path->get_max_speed() << " "
                << path->get_max_vehicles() << "\n";
        } else if (node->get_type() == INTERSECTION) {
            auto* intersection = dynamic_cast<Intersection*>(node);
            out << intersection->get_max_vehicles() << " "
                << intersection->getEntrancePaths().size() << "\n";

            for (const auto& path : intersection->getEntrancePaths()) {
                out << path->get_id() << " ";
            }
            out << "\n" << intersection->getExitPaths().size() << "\n";

            for (const auto& path : intersection->getExitPaths()) {
                out << path->get_id() << " ";
            }
            out << "\n";
        }
    }

    out << adjList.size() << "\n";
    for (const auto& pair : adjList) {
        out << pair.first << " " << pair.second.size() << "\n";
        for (const auto& path : pair.second) {
            out << path->get_id() << " ";
        }
        out << "\n";
    }

    out.close();
}

void Pointed_Graph::load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Ne moze se otvoriti " + filename);
    }

    size_t node_count;
    in >> node_count;

    std::unordered_map<int, Node*> id_to_node;
    nodes.clear();

    for (size_t i = 0; i < node_count; ++i) {
        int type_int, type_id;
        size_t name_length;
        std::string name;

        in >> type_int >> type_id >> name_length;
        name.resize(name_length);
        in.ignore();
        in.read(&name[0], name_length);

        Node* node = nullptr;
        if (static_cast<node_type>(type_int) == PATH) {
            int start_location, end_location, max_speed, max_vehicles;
            double length;

            in >> start_location >> end_location >> length >> max_speed >> max_vehicles;
            node = new Path(type_id, name, start_location, end_location, length, max_speed, max_vehicles, nullptr);
        } else if (static_cast<node_type>(type_int) == INTERSECTION) {
            int max_vehicles;
            size_t entrance_count, exit_count;

            in >> max_vehicles >> entrance_count;

            std::vector<Path*> entrance_paths(entrance_count);
            for (size_t j = 0; j < entrance_count; ++j) {
                int path_id;
                in >> path_id;
                entrance_paths[j] = reinterpret_cast<Path*>(path_id);
            }

            in >> exit_count;
            std::vector<Path*> exit_paths(exit_count);
            for (size_t j = 0; j < exit_count; ++j) {
                int path_id;
                in >> path_id;
                exit_paths[j] = reinterpret_cast<Path*>(path_id);
            }

            auto* intersection = new Intersection(type_id, name);
            intersection->setEntrancePaths(entrance_paths);
            intersection->setExitPaths(exit_paths);
            intersection->setMaxVehicles(max_vehicles);

            node = intersection;
        } else if (static_cast<node_type>(type_int) == LOCATION) {
            node = new Location(type_id, name);
        }

        nodes.push_back(node);
        id_to_node[type_id] = node;
    }

    size_t adjList_size;
    in >> adjList_size;
    adjList.clear();

    for (size_t i = 0; i < adjList_size; ++i) {
        int key;
        size_t path_count;
        in >> key >> path_count;

        std::vector<Path*> paths(path_count);
        for (size_t j = 0; j < path_count; ++j) {
            int path_id;
            in >> path_id;
            paths[j] = dynamic_cast<Path*>(id_to_node[path_id]);
        }

        adjList[key] = std::move(paths);
    }

    in.close();
}
