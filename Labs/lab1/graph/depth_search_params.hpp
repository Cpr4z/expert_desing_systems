#pragma once

#include <types/common.hpp>

#include "search_params.hpp"

class DepthSearchParams : public SearchParams
{
public:
    DepthSearchParams(const Graph& graph,
                      const Vertex from,
                      const Vertex to) : SearchParams(graph, from, to) {}
public:
    Stack<Vertex> m_opened_vertices;
};
