#include "graph/search_params.hpp"

#include "graph/graph.hpp"
#include "types/graph.hpp"

SearchParams::SearchParams(const Graph& graph, const Vertex from, const Vertex to)
        : m_vertices{graph.vertices()},
          m_edges{graph.edges()},
          m_from{from},
          m_to{to},
          m_visited(m_edges.size()) {}
