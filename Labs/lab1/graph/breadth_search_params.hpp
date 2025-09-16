#pragma once

#include <types/common.hpp>

#include "search_params.hpp"

class BreadthSearchParams : public SearchParams {
public:
    BreadthSearchParams(const Graph& graph,
                        const Vertex from,
                        const Vertex to) : SearchParams(graph, from, to) {}

public:
    Queue<Vertex> m_opened_vertices;
    UMap<Vertex, Vertex> m_back_vertex;
};
