#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <set>
#include <map>
#include <string>
#include <assert.h>

/*** Overload of the to_string function to work with std::string ***/
std::string to_string(const std::string& value) {
    return value;
}
template <typename T>
std::string value(T u) {
    using namespace std;
    return to_string(u);
}
/****************************************************************************/

template <class T>
class Digraph {
    /*** Public Interface ***/
public:
    Digraph();
    ~Digraph();

    /*** Modifiers ***/
    /*
     * Allows to insert a new vertex with an empty list of successor vertices.
     * If the vertex is already in the graph, this function does nothing (it does not overwrite the value associated with the key).
     */
    void insert_vertex(T u);
    void insert_edge(T u, T v);
    /*
     * Deletes a vertex and all the adjacent edges to this vertex.
     */
    void remove_vertex(T u);
    void remove_edge(T u, T v);

    /*** Functions for graph characteristics ***/
    /*
     * The following two functions respectively return
     * the number of vertices and the number of edges in the graph.
     */
    int num_vertices() const;
    int num_edges() const;
    /*
     * Returns a set with all the vertices p, such that there
     * exists an edge (p,u).
     */
    const std::set<T> predecessors(T u) const;
    /*
     * Returns a set with all the vertices s, such that there
     * exists an edge (u,s) (set of the successors of u).
     */
    const std::set<T> successors(T u) const;
    int in_degree(T u) const;
    int out_degree(T u) const;
    /*
     * Returns "true" if (u,v) is an edge of the graph, "false" if not.
     */
    bool edge(T u, T v) const;

    /*** Predicates ***/
    /*
     * Returns "true" if the edge (u,u) exists in the graph, "false"
     * if not.
     */
    bool loop(T u) const;
    /*
     * Returns "true" if the out-degree of u is 0, "false" if not.
     */
    bool sink(T u) const;
    /*
     * Returns "true" if,
     *  - the out-degree of u is 1 and the in-degree of u > 0
     * or
     *  - the in-degree of u is 1 and the out-degree of u > 0
     * "false" if not.
     */
    bool bypass(T u) const;
    /*
     * Returns "true" if no cycle goes through the edge (u,v),
     * "false" if not.
     */
    bool acyclic(T u, T v) const;

    /*** Graph reductions ***/
    /*
     * Applies as many times as possible the base reductions
     * (see statement and the functions loop(T u) and sink(T u)).
     * It returns "true" if at least one base reduction has been
     * applied, "false" if not.
     */
    bool basic_reduction();
    /*
     * Applies as many times as possible the intermediate reduction
     * (see statement and the function bypass(T u)). It returns
     * "true" if at least one intermediate reduction has been
     * applied, otherwise "false".
     */
    bool intermediate_reduction();
    /*
     * Applies the advanced reduction (see the statement and the acyclic(T u, T v) function)
     * as many times as possible. It returns "true" if at least one advanced reduction has
     * been applied, and "false" otherwise.
     */
    bool advanced_reduction();

    /*** To draw a graph with the dot command ***/
    std::string graphviz() const;

    /*** Representation ***/
    /**** You are not allowed to modify this representation ******/
    /**** So you cannot add new attribute/variable ***/
private:
    /*
     * We represent a graph with an adjacency list.
     * Each vertex u is associated with a set of vertices s such that
     * the edge (u, s) exists (all successors of u). See the statement
     * for examples.
     */
    std::map<T, std::set<T>> graph;

    /*
     * Returns "true" if the graph contains the vertex with the given parameters
     * and "false" otherwise.
     */
    bool contains_vertex(T);

    /*
     * Helper function for the acyclic(T, T) function. Applies the depth-first seedgeh and
     * returns "true" if the edge (formed by the two vertices passed as parameters) is acyclic
     * and "false" otherwise.
     */
    bool apply_cyclic(const T&, const T&, std::map<T, bool>) const;

    /*
     * Helper function for the acyclic(T, T) function. Initializes the value (visited) to false for
     * all vertices in the graph and calls the apply_cyclic function passing it the visited container
     * and the two vertices forming the edge to check. It returns the boolean value returned by
     * apply_cyclic.
     */
    bool cyclic(const T&, const T&) const;


    /*
     * Helper function for the basic_reduction function. Checks if the vertex passed as parameters
     * forms a loop or a sink. If so, it removes the vertex. It returns "true" if a modification is
     * applied and "false" otherwise.
     */
    bool basic_reduction_apply2(const T&);

    /*
     * Helper function for the basic_reduction function. Calls the basic_reduction_apply2 function
     * as long as a loop or a sink edge still exists in the graph, passing it the first one found.
     * It returns "true" if at least one basic reduction is applied and "false" otherwise.
     */
    bool basic_reduction_apply(const T&);

    /*
     * Helper function for the intermediate_reduction function. Checks if the vertex passed as parameters
     * forms an edge without a loop and to be bypassed. If so, it makes the necessary modifications of
     * the intermediate reduction and removes the vertex. It returns "true" if a modification is
     * applied and "false" otherwise.
     */
    bool apply_intermediate_reduction2(const T&);

    /*
     * Helper function for the intermediate_reduction function. Calls the intermediate_reduction_apply2
     * function as long as a bypass edge still exists in the graph, passing it the first one found.
     * It returns "true" if at least one intermediate reduction is applied and "false" otherwise.
     */
    bool apply_intermediate_reduction(const T&);

    /*
     * Helper function for the advanced_reduction function. Checks if the vertex passed as parameters
     * forms an acyclic edge with one of its adjacent vertices. If so, it removes the edge. It returns "true"
     * if a modification is applied and "false" otherwise.
     */
    bool apply_advanced_reduction2(const T&);

    /*
     * Helper function for apply_advanced_reduction.
     * Calls apply_advanced_reduction2 as long as there exists
     * a directed acyclic graph in the graph, passing the first one found
     * as a parameter.
     * Returns "true" if at least one advanced reduction is applied
     * "false" otherwise.
     */
    bool apply_advanced_reduction(const T&);

    /*
     * Returns "true" if the graph contains a directed acyclic graph
     * "false" otherwise.
     */
    bool acyclic_exists();

    /*
     * Returns "true" if the graph contains a loop or a sink edge
     * "false" otherwise.
     */
    bool loop_sink_exists();

    /*
     * Returns "true" if the graph contains a bypass edge
     * "false" otherwise.
     */
    bool bypass_exists();

    /*
     * Returns "true" if the vertex passed as a parameter forms
     * a directed acyclic graph with one of its adjacent vertices
     * "false" otherwise.
     */
    bool acyclic_vertex(const T&);
};
/******* Implementation *******/

template <class T>
Digraph<T>::Digraph() : graph() {
}

template <class T>
Digraph<T>::~Digraph() {
}

/*** Modifiers ***/

template <class T>
void Digraph<T>::insert_vertex(T u) {
    if (!contains_vertex(u)) {
        std::set<T> adj_set;
        graph.insert({ u, adj_set });
    }
}
template <class T>
void Digraph<T>::insert_edge(T u, T v) {
    if (!edge(u, v) || !edge(v, u)) {
        if (!contains_vertex(u))
            insert_vertex(u);
        if (!contains_vertex(v))
            insert_vertex(v);
        graph.at(u).insert(v);
    }
}

template <class T>
void Digraph<T>::remove_vertex(T u) {
    std::set<T> predecessors;
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        if (iter->second.find(u) != iter->second.end())
            predecessors.insert(iter->first);
    }
    std::set<T> successors;
    if (graph.find(u) != graph.end())
        successors = graph.at(u);
    for (auto it = successors.begin(); it != successors.end(); ++it) {
        remove_edge(u, *it);
    }
    for (auto it = predecessors.begin(); it != predecessors.end(); ++it) {
        remove_edge(*it, u);
    }

    graph.erase(u);
}

template <class T>
void Digraph<T>::remove_edge(T u, T v) {
    if (edge(u, v) || edge(v, u)) {
        std::set<T> u_set = graph.at(u);
        for (auto it = u_set.begin(); it != u_set.end(); ) {
            if (*it == v) {
                it = u_set.erase(it);
                graph.at(u) = u_set;
            }
            else {
                ++it;
            }
        }
        std::set<T> v_set = graph.at(v);
        for (auto it = v_set.begin(); it != v_set.end(); ) {
            if (*it == u) {
                it = v_set.erase(it);
                graph.at(v) = v_set;
            }
            else {
                ++it;
            }
        }
    }
}

/*** Graph Characteristics Functions ***/
template <class T>
int Digraph<T>::num_vertices() const {
    return graph.size();
}

template <class T>
int Digraph<T>::num_edges() const {
    int edges = 0;
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        for (auto reti = iter->second.begin(); reti != iter->second.end(); ++reti)
            edges++;
    }
    return edges;
}

template <class T>
const std::set<T> Digraph<T>::predecessors(T u) const {
    std::set<T> p;
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        if (iter->second.find(u) != iter->second.end())
            p.insert(iter->first);
    }
    return p;
}

template <class T>
const std::set<T> Digraph<T>::successors(T u) const {
    std::set<T> s;
    if (graph.find(u) != graph.end())
        s = graph.at(u);
    return s;
}

template <class T>
int Digraph<T>::in_degree(T u) const {
    std::set<T> p = predecessors(u);
    return p.size();
}

template <class T>
int Digraph<T>::out_degree(T u) const {
    std::set<T> s = successors(u);
    return s.size();
}

template <class T>
bool Digraph<T>::edge(T u, T v) const {
    if (graph.count(u) == 0)
        return false;
    std::set<T> adj_set = graph.at(u);
    return adj_set.find(v) != adj_set.end();
}


/*** Predicates ***/
template <class T>
bool Digraph<T>::loop(T u) const {
    if (graph.count(u) == 0)
        return false;
    std::set<T> adj_set = graph.at(u);
    return adj_set.find(u) != adj_set.end();
}

template <class T>
bool Digraph<T>::sink(T u) const {
    if (out_degree(u) == 0)
        return true;
    else
        return false;
}

template <class T>
bool Digraph<T>::bypass(T u) const {
    if ((out_degree(u) == 1 && in_degree(u) > 0) ||
        (in_degree(u) == 1 && out_degree(u) > 0))
        return true;
    return false;
}

template <class T>
bool Digraph<T>::acyclic(T u, T v) const {
    if (cyclic(u, v))
        return false;
    else
        return true;
}

/*** Graph reductions ***/
template <class T>
bool Digraph<T>::basic_reduction() {
    return basic_reduction_apply(graph.begin()->first);
}

template <class T>
bool Digraph<T>::intermediate_reduction() {
    return apply_intermediate_reduction(graph.begin()->first);
}

template <class T>
bool Digraph<T>::advanced_reduction() {
    return apply_advanced_reduction(graph.begin()->first);
}

/*** Private functions ***/
template <class T>
bool Digraph<T>::contains_vertex(T u) {
    if (graph.find(u) == graph.end())
        return false;
    else
        return true;
}
template <class T>
bool Digraph<T>::cyclic(const T& u, const T& v) const {

    std::map<T, bool> visited;

    for (auto iter = graph.begin(); iter != graph.end(); ++iter)
    {
        visited.insert({ iter->first, false });
    }

    return apply_cyclic(u, v, visited);
}

template <class T>
bool Digraph<T>::apply_cyclic(const T& u, const T& v, std::map<T, bool> visited) const
{
    if (visited.at(u))
        return true;

    if (!visited.at(v)) {

        visited.at(v) = true;
        std::set<T> s = successors(v);
        auto i = s.begin();
        while (i != s.end()) {
            if (apply_cyclic(u, *i, visited))
                return true;
            i++;
        }
    }

    return false;
}

template <class T>
bool Digraph<T>::apply_intermediate_reduction2(const T& u) {

    std::set<T> s = successors(u);
    std::set<T> p = predecessors(u);

    if (bypass(u) && !loop(u)) {
        if (s.size() == 1 && p.size() > 0) {
            auto replace = s.begin();
            for (auto k = p.begin(); k != p.end(); ++k) {
                insert_edge(*k, *replace);
            }
        }
        else if (p.size() == 1 && s.size() > 0) {
            auto replace = p.begin();
            for (auto k = s.begin(); k != s.end(); ++k) {
                insert_edge(*replace, *k);
            }
        }
        remove_vertex(u);
        return true;
    }

    return false;
}

template <class T>
bool Digraph<T>::basic_reduction_apply2(const T& u) {
    if (loop(u) || sink(u)) {
        remove_vertex(u);
        return true;
    }
    return false;
}

template <class T>
bool Digraph<T>::apply_advanced_reduction2(const T& u) {
    std::set<T> s = successors(u);
    for (auto k = s.begin(); k != s.end(); ++k) {
        if (acyclic(u, *k)) {
            remove_edge(u, *k);
            return true;
        }
    }
    return false;
}

template <class T>
bool Digraph<T>::basic_reduction_apply(const T& u) {
    bool applied = basic_reduction_apply2(u);
    while (loop_sink_exists()) {
        for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
            if (loop(iter->first) || sink(iter->first)) {
                return basic_reduction_apply(iter->first);
            }
        }
    }
    return applied;
}

template <class T>
bool Digraph<T>::apply_intermediate_reduction(const T& u) {
    bool applied = apply_intermediate_reduction2(u);
    while (bypass_exists()) {
        for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
            if (bypass(iter->first) && !loop(iter->first)) {
                return apply_intermediate_reduction(iter->first);
            }
        }
    }
    return applied;
}

template <class T>
bool Digraph<T>::apply_advanced_reduction(const T& u) {
    bool applied = apply_advanced_reduction2(u);
    while (acyclic_exists()) {
        for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
            if (acyclic_vertex(iter->first)) {
                return apply_advanced_reduction(iter->first);
            }
        }
    }
    return applied;
}

template <class T>
bool Digraph<T>::acyclic_exists() {
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        for (auto k = graph.at(iter->first).begin(); k != graph.at(iter->first).end(); ++k) {
            if (acyclic(iter->first, *k)) {
                return true;
            }
        }
    }
    return false;
}

template <class T>
bool Digraph<T>::loop_sink_exists() {
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        if (loop(iter->first) || sink(iter->first)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool Digraph<T>::bypass_exists() {
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        if (bypass(iter->first) && !loop(iter->first)) {
            return true;
        }
    }
    return false;
}

template <class T>
bool Digraph<T>::acyclic_vertex(const T& u) {
    if (out_degree(u) != 0) {
        for (auto k = graph.at(u).begin(); k != graph.at(u).end(); ++k) {
            if (acyclic(u, *k)) {
                return true;
            }
        }
    }
    return false;
}

/*** To draw a graph with the dot command ***/
#include <iostream>

template <class T>
std::string Digraph<T>::graphviz() const {
    std::string header = "digraph {\n";
    std::string body_v = "";
    std::string body_a = "";
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        body_v += " " + value(iter->first) + ";\n";
        for (auto reti = iter->second.begin(); reti != iter->second.end(); ++reti)
            body_a += " " + value(iter->first) + " -> " + value(*reti) + ";\n";
    }
    std::string footer = "}\n";
    return header + body_v + body_a + footer;
}


#endif