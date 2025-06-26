// knoten.cpp
#include "graph.h"
#include <iostream>
#include <vector>

// Funktion, die einen Graphen und eine Knoten-ID nimmt und die Anzahl der angrenzenden Kanten des Knotens zurückgibt
int num_edges_adjacent(const Graph& g, Graph::NodeId nodeid)
{
    int num_edges = 0;
    for (auto neighbor : g.get_node(nodeid).adjacent_nodes()) {
        ++num_edges;
    }
    return num_edges;
}

// Funktion, die von einem Graphen die Gesamtanzahl der Kanten berechnet
int calc_total_num_edges(const Graph& g)
{
    int num_edges = 0;
    for (Graph::NodeId nodeid = 0; nodeid < g.num_nodes(); ++nodeid) {
        num_edges += num_edges_adjacent(g, nodeid);
    }
    return num_edges / 2;
}

// Funktion, die einen Graphen, den Vektor der Anzahl der angrenzenden Kanten jedes Knotens und eine Knoten-ID nimmt und die Summe der Anzahl der angrenzenden Kanten aller Nachbarn des Knotens zurückgibt
int sum_adjacent_edges_neighbors(const Graph& g, std::vector<int>& vec_num_edges, Graph::NodeId nodeid)
{
    int num_sum_adjacent = 0;
    for (auto neighbor : g.get_node(nodeid).adjacent_nodes()) {
        num_sum_adjacent += vec_num_edges[neighbor.id()];
    }
    return num_sum_adjacent;
}

// Funktion die einen Graphen, den Vektor der Anzahl der angrenzenden Kanten jedes Knotens und
// die important_number annimmt und für jeden Knoten die num_sum_adjacent_edges_neighbors ausrechtnet
// und ausgibt ob die, geteilt durch die anzahl adjazenter Kanten >= important_number ist
int is_it_larger(const Graph& g, std::vector<int>& vec_num_edges, double important_number)
{
    double sum_divided;

    for (Graph::NodeId nodeid = 0; nodeid < g.num_nodes(); ++nodeid) {

        if (vec_num_edges[nodeid] != 0) {

            double num_sum_adjacent_edges_neighbors = sum_adjacent_edges_neighbors(g, vec_num_edges, nodeid);
            sum_divided = num_sum_adjacent_edges_neighbors / vec_num_edges[nodeid];

            if (sum_divided >= important_number) {
                std::cout << "Knoten " << nodeid << " erfuellt die Ungleichung !!!.\n";
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        Graph g(argv[1], Graph::undirected);  //Graph sollte undirected sein.

        const double total_num_edges = calc_total_num_edges(g);
        const double total_num_nodes = g.num_nodes();
        const double important_number = (2 * total_num_edges) / total_num_nodes;

        std::vector<int> vec_num_edges;
        // Erstellt den Vector vec_num_edges, der die Anzahl der angrenzenden Kanten jedes Knotens enthaelt (ja, der for loop koennte auch in der Funktion sein)
        for (Graph::NodeId nodeid = 0; nodeid < g.num_nodes(); ++nodeid) {
            vec_num_edges.push_back(num_edges_adjacent(g, nodeid));
        }

        is_it_larger(g, vec_num_edges, important_number);
    }
    return 0;
}
