// graph.h (Declaration of Class Graph)
#ifndef GRAPH_H
#define GRAPH_H

#define and &&
#define or ||
#define not !

#include <iostream>
#include <vector>

class Graph {
public:
  using NodeId = int;  // vertices are numbered 0,...,num_nodes()-1

  class Neighbor {
  public:
    Neighbor(Graph::NodeId n, double w);
    double edge_weight();
    Graph::NodeId id();
  private:
    Graph::NodeId _id;
    double _edge_weight;
  };

  class Node {
  public:
    void add_neighbor(Graph::NodeId nodeid, double weight);
    std::vector<Neighbor>& adjacent_nodes();
  private:
    std::vector<Neighbor> _neighbors;
  };

  enum DirType { directed, undirected };  // enum defines a type with possible values
  Graph(NodeId num_nodes, DirType dirtype);
  Graph(char* filename, DirType dirtype);

  void add_nodes(NodeId num_new_nodes);
  void add_edge(NodeId tail, NodeId head, double weight = 1.0);

  NodeId num_nodes();
  Node& get_node(NodeId);
  void print();

  DirType dirtype;
  static  NodeId invalid_node;
  static  double infinite_weight;

private:
  std::vector<Node> _nodes;
};

#endif // GRAPH_H
