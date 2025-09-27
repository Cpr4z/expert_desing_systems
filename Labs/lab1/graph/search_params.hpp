#pragma once

#include "types/graph.hpp"

class Graph;

struct SearchParams {
    SearchParams(const Graph& graph, Vertex from, Vertex to);

    // База знаний
    const Vertices& m_vertices; // список вершин графа
    const Edges& m_edges; // список ребер графа

    Vertex m_from; // начальная вершина
    Vertex m_to; // целевая вершина

    // список закрытых вершин
    List<Vertex> m_closed_vertices;

    // список посещенных ребер
    Vector<bool> m_visited;
};
