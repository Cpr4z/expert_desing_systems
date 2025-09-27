#include "graph/breadth_first_search.hpp"

#include "breadth_search_params.hpp"
#include "graph.hpp"
#include "pattern_search_result.hpp"
#include "search_result.hpp"
#include "types/common.hpp"
#include "types/graph.hpp"
#include "utils/convert.hpp"

namespace {
PatternSearchResult sPatternSearch(BreadthSearchParams& p) {
    auto result = PatternSearchResult::kNotFound;

    // обходим все ребра графа, которые не являются посещенными
    for (size_t i = 0; i < p.m_edges.size(); ++i) {
        if (p.m_visited[i]) {
            continue;
        }

        // получаем вершину, которую мы не посетили и инцендентную данному ребру вешину
        const auto& [from, to] = p.m_edges[i];

        if (p.m_opened_vertices.front() == from) {
            p.m_opened_vertices.push(to);

            if (!p.m_back_vertex.contains(to)) {
                p.m_back_vertex[to] = from;
            }

            if (to == p.m_to) {
                return PatternSearchResult::kFoundLastEdge;
            }

            p.m_visited[i] = true;
            result = PatternSearchResult::kFoundNextEdge;
        }
    }

    return result;
}
}  // namespace

SearchResult breadthFirstSearch(const Graph& graph, Vertex from, Vertex to) {
    BreadthSearchParams p{graph, from, to};
    p.m_opened_vertices.push(from);

    // случай, если указаны невалидные начальные и конечные вершины
    if (!p.m_vertices.contains(from) || !p.m_vertices.contains(to)) {
        return {};
    }

    // случай если конечная вершина равна начальной
    if (from == to) {
        return {{from}, {}};
    }

    // пока список открытых вершин не пуст
    while (!p.m_opened_vertices.empty()) {
        const auto result = sPatternSearch(p);
        p.m_closed_vertices.push_front(p.m_opened_vertices.front());
        p.m_opened_vertices.pop();

        if (result == PatternSearchResult::kFoundLastEdge) {
            break;
        }
    }

    // случай, когда мы прошли весь граф но не нашли путь до целевой вершины
    auto it = p.m_back_vertex.find(to);
    if (it == p.m_back_vertex.end()) {
        return {{}, Utils::converted(p.m_closed_vertices)};
    }

    Vector<Vertex> path{to};
    do {
        path.push_back(it->second);
        it = p.m_back_vertex.find(it->second);
    } while (it != p.m_back_vertex.end() && it->first != from);

    std::reverse(path.begin(), path.end());

    return {path, Utils::converted(p.m_closed_vertices)};
}
