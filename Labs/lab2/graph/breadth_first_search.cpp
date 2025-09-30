#include "breadth_first_search.hpp"

#include <algorithm>
#include <iostream>

#include "graph/graph.hpp"
#include "types/common.hpp"
#include "types/graph.hpp"
#include "utils/io_utils.hpp"

namespace {
class Tracing {
public:
    explicit Tracing(size_t& indent) : indent_{indent} { ++indent; }

    Tracing(const Tracing&) = delete;
    Tracing(Tracing&&) = delete;
    Tracing& operator=(const Tracing&) = delete;
    Tracing& operator=(Tracing&&) = delete;

    ~Tracing() noexcept { --indent_; }

    template <typename T>
    std::ostream& operator<<(const T& value) {
        return std::cout << std::string(indent_, '\t') << value;
    }

private:
    size_t& indent_;
};
}  // namespace

SearchResult breadthFirstSearch(const HyperGraph& graph,
                                const Vertices& from,
                                Vertex to) {
    const auto& vertices = graph.vertices();
    const auto& edges = graph.edges();

    SearchResult r;
    size_t indent = 0;

    Tracing{indent} << "Запуск поиска в ширину от множества вершин к цели " << to << "\n";

    if (!vertices.contains(to)) {
        Tracing{indent} << "Цель " << to << " не является вершиной графа\n";
        return r;
    }

    r.closed_vertices = Vector<Vertex>(from.begin(), from.end());
    USet<Vertex> closed_vertices_fast_lookup(from.begin(), from.end());

    Tracing{indent} << "Начальные закрытые вершины: ";
    join(from, std::cout, ", ");
    std::cout << "\n";

    if (from.contains(to)) {
        Tracing{indent} << "Цель уже содержится среди начальных вершин\n";
        r.found = true;
        return r;
    }

    USet<size_t> closed_rules_fast_lookup;

    const auto all_closed = [&closed_vertices_fast_lookup](const Vertices& vs) {
        return std::all_of(vs.begin(), vs.end(),
                           [&closed_vertices_fast_lookup](Vertex v) {
                               return closed_vertices_fast_lookup.contains(v);
                           });
    };

    bool rule_was_added = true;
    while (!r.found && rule_was_added) {
        rule_was_added = false;

        for (auto&& [from_, tos_, id] : edges) {
            if (closed_rules_fast_lookup.contains(id)) {
                continue;
            }

            Tracing{indent} << "Проверяем правило " << id << "\n";

            if (all_closed(tos_)) {
                Tracing{indent} << "Все вершины правила " << id << " доказаны\n";
                r.closed_vertices.push_back(from_);
                closed_vertices_fast_lookup.insert(from_);

                r.closed_rules.push_back(id);
                closed_rules_fast_lookup.insert(id);

                Tracing{indent} << "Добавляем вершину " << from_
                                << " и правило " << id << " в закрытые\n";

                rule_was_added = true;

                if (from_ == to) {
                    Tracing{indent} << "Цель " << to << " достигнута!\n";
                    r.found = true;
                    break;
                }
            } else {
                Tracing{indent} << "Не все вершины правила " << id << " доказаны\n";
            }
        }
    }

    return r;
}
