/*
 * Test for the Digraph class.
 *
 */

#include "digraph.h"
#include <iostream>

int main() {
    Digraph<int> graph;
    int error = 0;
    for (int i = 0; i < 14; i++)
        graph.insert_vertex(i);
    graph.insert_edge(0, 5);
    std::set<int> s1({ 0, 2, 6, 7 });
    for (auto const& i : s1)
        graph.insert_edge(1, i);
    std::set<int> s3({ 2, 4, 8, 9 });
    for (auto const& i : s3)
        graph.insert_edge(3, i);
    graph.insert_edge(4, 10);
    graph.insert_edge(4, 13);
    graph.insert_edge(5, 1);
    graph.insert_edge(6, 11);
    graph.insert_edge(7, 3);
    graph.insert_edge(8, 13);
    graph.insert_edge(9, 13);
    graph.insert_edge(10, 4);
    std::set<int> s11({ 5, 7, 11, 12 });
    for (auto const& i : s11)
        graph.insert_edge(11, i);
    graph.insert_edge(12, 7);
    graph.insert_edge(12, 13);
    graph.basic_reduction();
    if (graph.num_vertices() != 8) {
        std::cerr << "FAILURE - I" << std::endl;
        error++;
    }
    if (graph.num_edges() != 9) {
        std::cerr << "FAILURE - II" << std::endl;
        error++;
    }
    if (!graph.edge(0, 5) ||
        !graph.edge(1, 0) ||
        !graph.edge(1, 7) ||
        !graph.edge(3, 4) ||
        !graph.edge(4, 10) ||
        !graph.edge(5, 1) ||
        !graph.edge(7, 3) ||
        !graph.edge(10, 4) ||
        !graph.edge(12, 7)) {
        std::cerr << "FAILURE - III" << std::endl;
        error++;
    }
    graph.remove_edge(4, 10);
    graph.basic_reduction();
    if (graph.num_vertices() != 3) {
        std::cerr << "FAILURE - IV" << std::endl;
        error++;
    }

    if (graph.num_edges() != 3) {
        std::cerr << "FAILURE - V" << std::endl;
        error++;
    }
    if (!graph.edge(0, 5) || !graph.edge(1, 0) || !graph.edge(5, 1)) {
        std::cerr << "FAILURE - VI" << std::endl;
        error++;
    }
    if (error == 0)
        std::cout << "\t==> OK" << std::endl;
    return error;
}
