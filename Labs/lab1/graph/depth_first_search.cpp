#include "graph/depth_first_search.hpp"

// std
#include <iterator>

#include "graph.hpp"
#include "pattern_search_result.hpp"
#include "depth_search_params.hpp"
#include "search_result.hpp"
#include "types/graph.hpp"
#include "utils/convert.hpp"

namespace {
PatternSearchResult sPatternSearch(DepthSearchParams& p) {
    for (size_t i = 0; i < p.m_edges.size(); ++i) {
        if (p.m_visited[i]) {
            continue;
        }

        const auto& [from, to] = p.m_edges[i];

        if (p.m_opened_vertices.top() == from) {
            p.m_opened_vertices.push(to);

            if (to == p.m_to) {
                return PatternSearchResult::kFoundLastEdge;
            }

            p.m_visited[i] = true;
            return PatternSearchResult::kFoundNextEdge;
        }
    }

    return PatternSearchResult::kNotFound;
}
}  // namespace

SearchResult depthFirstSearch(const Graph& graph, Vertex from, Vertex to) {
    DepthSearchParams p{graph, from, to};
    p.m_opened_vertices.push(from);

    if (!p.m_vertices.contains(from) || !p.m_vertices.contains(to)) {
        return {};
    }

    if (from == to) {
        return {{from}, {}};
    }

    while (!p.m_opened_vertices.empty()) {
        const auto result = sPatternSearch(p);
        if (result == PatternSearchResult::kFoundLastEdge) {
            return { Utils::openedConverted(p.m_opened_vertices),
                    Utils::converted(p.m_closed_vertices)};
        }
        if (result == PatternSearchResult::kNotFound) {
            if (p.m_opened_vertices.size() > 1) {
                p.m_closed_vertices.push_front(p.m_opened_vertices.top());
                p.m_opened_vertices.pop();
            } else if (p.m_opened_vertices.top() == p.m_from) {
                return {{}, Utils::converted(p.m_closed_vertices)};
            }
        }
    }
    return {};
}
