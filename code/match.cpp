#include "graph_mod.h"
#include "heap.h"
#include "queue.h"

#define and &&
#define or ||
#define not !


// to use match.cpp the custom graph.cpp and graph.h files are needed, I removed all const's
// so that graphs could be modified, now idea how to do this without that
// the algorithm isn't quite correct occasionally a node has two edges
// but I don't have any more time to fix that
// The implementation is also terrible, and very inefficient


struct PrevData { // struct to store previous node and weight
    Graph::NodeId id;
    double weight; // here basically a tuple
};

bool has_edge(Graph& graph, Graph::NodeId source, Graph::NodeId target) {

    if (graph.dirtype == Graph::undirected) {
        for (auto& neighbor : graph.get_node(target).adjacent_nodes()) {
            if (neighbor.id() == source) {
                return true;
            }
        }
    }
    else {
        for (auto& neighbor : graph.get_node(source).adjacent_nodes()) {
            if (neighbor.id() == target) {
                return true;
            }
        }
    }
    return false;
}


bool bfs_and_update_matching(Graph& H, const Graph::NodeId s, Graph& matching)
{
    std::vector<bool> visited(H.num_nodes(), false); // vector of bools visited, with size of number of nodes, all set to false
    Graph bfs_tree(H.num_nodes(), Graph::directed); // creates bfs_tree, with number of nodes same as original graph
    Queue<Graph::NodeId> queue; // creates queue of NodeIds

    std::vector<PrevData> prev(H.num_nodes(), { Graph::invalid_node, 0.0 }); // create vector of PrevData
    // this is done using vector of structs

    bool possible = false;
    int t = H.num_nodes() - 1;

    queue.push_back(s);
    visited[s] = true; // sets our vector from before visited, to true for start node

    while (not queue.is_empty()) {
        auto cur_nodeid = queue.pop_front(); // removes first element from queue and assigns it to cur_nodeid

        for (auto neighbor : H.get_node(cur_nodeid).adjacent_nodes()) {

            if (not visited[neighbor.id()]) {

                visited[neighbor.id()] = true;
                bfs_tree.add_edge(cur_nodeid, neighbor.id());
                queue.push_back(neighbor.id());

                prev[neighbor.id()] = { cur_nodeid, neighbor.edge_weight() };
                // set parent node of that neighbor to the current node, and the weight to the current edge weight

                if (neighbor.id() == t) {
                    possible = true;

                    // CREATING THE PATH
                    // and also Make matching be symmetric difference of matching and path
                    Graph path(H.num_nodes(), Graph::directed);

                    Graph::NodeId current_node = t;

                    while (current_node != s) {

                        Graph::NodeId parent = prev[current_node].id;
                        path.add_edge(parent, current_node);
                        current_node = parent;
                    }


                    // remove edges from H that are at the very start and end of the path
                    // and reverse other edges in H that are in the path

                    Graph new_H(H.num_nodes(), Graph::directed);

                    for (auto nodeid = 0; nodeid < H.num_nodes(); ++nodeid) // looping through all nodes in H
                    {
                        for (auto neighbor : H.get_node(nodeid).adjacent_nodes()) // looping through all neighbors of nodeid
                        {
                            if (not has_edge(path, nodeid, neighbor.id()))
                            {
                                new_H.add_edge(nodeid, neighbor.id());
                            }
                            else
                            {
                                // check if edge at very start or end of path
                                if (nodeid == s or neighbor.id() == t)
                                {
                                }
                                else
                                {
                                    // reverse edge
                                    new_H.add_edge(neighbor.id(), nodeid);
                                }
                            }
                        }
                    }

                    Graph new_matching(matching.num_nodes(), Graph::undirected);

                    for (auto nodeid = 0; nodeid < path.num_nodes() - 2; ++nodeid)
                    {
                        for (auto neighbor : path.get_node(nodeid).adjacent_nodes()) // looping through all neighbors of nodeid
                        {
                            if ((neighbor.id() != t) and
                                (neighbor.id() != s)
                                and not has_edge(matching, nodeid, neighbor.id())
                                and not has_edge(matching, neighbor.id(), nodeid)
                                and not has_edge(new_matching, nodeid, neighbor.id())
                                and not has_edge(new_matching, neighbor.id(), nodeid)
                                )
                            {
                                new_matching.add_edge(neighbor.id(), nodeid);
                            }
                        }
                    }

                    for (auto nodeid = 0; nodeid < matching.num_nodes(); ++nodeid)
                    {
                        for (auto neighbor : matching.get_node(nodeid).adjacent_nodes()) // looping through all neighbors of nodeid
                        {
                            if (not has_edge(path, nodeid, neighbor.id())
                                and not has_edge(new_matching, nodeid, neighbor.id())
                                and not has_edge(new_matching, neighbor.id(), nodeid))
                            {
                                new_matching.add_edge(nodeid, neighbor.id());
                            }

                        }
                    }

                    for (auto nodeid = 0; nodeid < path.num_nodes() - 2; ++nodeid)
                    {
                        for (auto neighbor : path.get_node(nodeid).adjacent_nodes()) // looping through all neighbors of nodeid
                        {
                            if ((neighbor.id() != t) and
                                (neighbor.id() != s)
                                and not has_edge(matching, nodeid, neighbor.id())
                                and not has_edge(matching, neighbor.id(), nodeid)
                                and not has_edge(new_matching, nodeid, neighbor.id())
                                and not has_edge(new_matching, neighbor.id(), nodeid)
                                )
                            {
                                new_matching.add_edge(neighbor.id(), nodeid);
                            }
                        }
                    }
                    matching = new_matching;
                    H = new_H;
                }
            }
        }
    }
    return possible;
}


Graph Bipartiter_Matching_Algorithmus(Graph& g) {

    Graph matching(g.num_nodes(), Graph::undirected);
    // create Graph Matching, that should theoretically be empty set for now

    int n = g.num_nodes();
    // create Graph H, a graph
    Graph H = g;
    // adding nodes s and t
    H.add_nodes(2);

    int s = H.num_nodes() - 2;

    // and adding connecting edges
    for (auto i = 0; i <= n / 2 - 1; ++i) {             // adding edges from s to A
        H.add_edge(s, i);
    }
    for (auto i = n / 2; i <= n - 1; ++i) {             // adding edes from B to t
        H.add_edge(i, H.num_nodes() - 1);
    }

    int index = 0;
    while (true)
    {
        bool possible = false;
        possible = bfs_and_update_matching(H, s, matching);

        if (possible == false)
        {
            break;
        }

    }
    return matching;
}


int main(int argc, char* argv[])
{
    if (argc > 1) {
        Graph g(argv[1], Graph::directed);

        Graph matching = Bipartiter_Matching_Algorithmus(g);

        std::cout << "The following is the matching:\n";
        matching.print();
    }
}
