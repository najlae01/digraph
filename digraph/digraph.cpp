// digraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/**
 * Main program to use the Digraph class.
 */
#include "digraph.h"
#include <iostream>

 /**
  *
  * Usage:
  *	g++ digraph.cpp -o digraph
  * 	./digraph < dico
  * Expected output:
  *	Original dictionary: 6036 words and 28623 links.
  *	Number of essential words: 78
  * Execution time: less than 40 seconds.
  */

int main() {
	Digraph<std::string> graph;
	while (std::cin) {
		std::string src, dest;
		std::cin >> src >> dest;
		if (!src.empty() && !dest.empty()) {
			graph.insert_vertex(src);
			graph.insert_vertex(dest);
			graph.insert_edge(src, dest);
		}
	}
	int words = graph.num_vertices(), edges = graph.num_edges();
	while (graph.basic_reduction()) {
	}
	std::cout << "Original dictionary: " << words << " words and " << edges << " links." << std::endl;
	std::cout << "Number of essential words: " << graph.num_vertices() << std::endl;
	// To display the essential dictionary
	//std::cout << graph.graphviz() << std::endl;
	return 0;
}
