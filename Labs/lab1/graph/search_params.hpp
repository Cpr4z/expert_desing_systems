#pragma once

#include "types/graph.hpp"

class Graph;

struct SearchParams {
    SearchParams(const Graph& graph, Vertex from, Vertex to);

    const Vertices& m_vertices;
    const Edges& m_edges;

    Vertex m_from;
    Vertex m_to;

    List<Vertex> m_closed_vertices;

    Vector<bool> m_visited;
};
