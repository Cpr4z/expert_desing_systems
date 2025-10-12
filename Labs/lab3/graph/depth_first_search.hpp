#pragma once

#include "types/graph.hpp"
#include "utils/my_stack.hpp"

class HyperGraph;
class Trace;

struct SearchResult {
    Vector<Vertex> closed_vertices;
    Vector<Rule> closed_rules;
    bool found = false;
};

class DepthFirstSearch final
{
public:
    // Метод обратного поиска в глубину
    DepthFirstSearch(const HyperGraph& graph, Vertex goal_node, const Vertices& in_node_arr);
    SearchResult search() noexcept;

private:
    void init(const HyperGraph& graph, Vertex goal_node, const Vertices& in_node_arr);

    int childSearch() noexcept;
    void backtrack() noexcept;
    void label() noexcept;
    bool add_new_goal(const Vertices& vertices) noexcept;
    bool is_forbidden_node_exists(const Vertices& vertices) noexcept;

    Rule getBackOpenedRule() noexcept;
    void popBackOpenedRule() noexcept;

    void logTrace(std::string_view custom_message) noexcept;

private:
    Rules m_rules;

    const Vertex m_target_vertex;

    // Список открытых вершин/правил
    Stack<Vertex> m_opened_vertices;
    Rules m_opened_rules;

    // Список закрытых вершин/правил
    Set<Vertex> m_closed_vertices;
    Set<Rule> m_closed_rules;

    // Список запрещенных вершин/правил
    Set<Vertex> m_forbidden_vertices;
    Set<Rule> m_forbidden_rules;

    bool m_solution_flag = false;
    bool m_no_solution_flag = false;
};