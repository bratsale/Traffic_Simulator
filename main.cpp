#include <iostream>
#include "Node.cpp"
#include "Pointed_Graph.cpp"
#include "Vehicle.cpp"

int main() {
    Pointed_Graph graph;

    Location* lokacija1 = new Location(0, "Lokacija 1");
    Location* lokacija2 = new Location(1, "Lokacija 2");
    Location* lokacija3 = new Location(2, "Lokacija 3");
    Location* lokacija4 = new Location(3, "Lokacija 4");

    graph.addNode(lokacija1);
    graph.addNode(lokacija2);
    graph.addNode(lokacija3);
    graph.addNode(lokacija4);

    Path* put1 = new Path(4, "Put 1", 0, 1, 100, 50, 10, nullptr);
    Path* put2 = new Path(5, "Put 2", 0, 2, 200, 30, 10, nullptr);
    Path* put3 = new Path(6, "Put 3", 1, 2, 50, 60, 10, nullptr);
    Path* put4 = new Path(7, "Put 4", 1, 3, 150, 40, 10, nullptr);
    Path* put5 = new Path(8, "Put 5", 2, 3, 100, 70, 10, nullptr);

    graph.addPath(put1);
    graph.addPath(put2);
    graph.addPath(put3);
    graph.addPath(put4);
    graph.addPath(put5);

    Intersection* intersection1 = new Intersection(9, "Raskrsnica 1");
    Intersection* intersection2 = new Intersection(10, "Raskrsnica 2");

   
    intersection1->Add(put1, true); 
    intersection1->Add(put2, true); 
    intersection1->Add(put3, false); 

    intersection2->Add(put4, true); 
    intersection2->Add(put5, true);

    graph.addNode(intersection1);
    graph.addNode(intersection2);

    Location start_location = *lokacija1; 
    Location end_location = *lokacija4; 
    int avg_speed = 60; 
    Vehicle vozilo(start_location, end_location, avg_speed);

    std::vector<int> putanja1 = vozilo.FindShortestPath(graph, true);
    std::cout << "Najbolja putanja sa minimalnom distancom: ";
    for (int cvor : putanja1) {
        std::cout << cvor << " ";
    }
    std::cout << std::endl;

    std::vector<int> putanja2 = vozilo.FindShortestPath(graph, false);
    std::cout << "Najbolja putanja sa minimalnim vremenom: ";
    for (int cvor : putanja2) {
        std::cout << cvor << " ";
    }
    std::cout << std::endl;

    graph.save("graph.dat");
    std::cout << "Graf je serijalizovan u 'graph.dat'" << std::endl;

    Pointed_Graph loaded_graph;
    loaded_graph.load("graph.dat");
    std::cout << "Graf je deserializovan iz 'graph.dat'" << std::endl;

    std::vector<int> putanja1_loaded = vozilo.FindShortestPath(loaded_graph, true);
    std::cout << "Najbolja putanja sa minimalnom distancom (iz učitanog grafa): ";
    for (int cvor : putanja1_loaded) {
        std::cout << cvor << " ";
    }
    std::cout << std::endl;

    std::vector<int> putanja2_loaded = vozilo.FindShortestPath(loaded_graph, false);
    std::cout << "Najbolja putanja sa minimalnim vremenom (iz učitanog grafa): ";
    for (int cvor : putanja2_loaded) {
        std::cout << cvor << " ";
    }
    std::cout << std::endl;

    delete lokacija1;
    delete lokacija2;
    delete lokacija3;
    delete lokacija4;
    delete put1;
    delete put2;
    delete put3;
    delete put4;
    delete put5;
    delete intersection1;
    delete intersection2;

    return 0;
}
