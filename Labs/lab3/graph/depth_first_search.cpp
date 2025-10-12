#include "graph/depth_first_search.hpp"

#include <iostream>
#include <string>

#include "graph/graph.hpp"
#include "types/graph.hpp"
#include "utils/io_utils.hpp"

namespace {

using namespace std::string_view_literals;

size_t INDENT = 0;

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


DepthFirstSearch::DepthFirstSearch(const HyperGraph &graph,
                                   Vertex goal_node,
                                   const Vertices& in_node_arr) : m_target_vertex(goal_node) {
    init(graph, goal_node, in_node_arr);
}

void DepthFirstSearch::init(const HyperGraph& graph,
                            Vertex goal_node,
                            const Vertices& in_node_arr) {
    m_closed_vertices.clear();
    m_opened_rules.clear();
    m_closed_rules.clear();
    m_closed_vertices.clear();
    m_forbidden_vertices.clear();
    m_forbidden_rules.clear();
    m_rules.clear();

    auto rules = graph.rules();
    m_rules = rules;

    m_closed_vertices.insert(in_node_arr.begin(), in_node_arr.end());
    m_opened_vertices.push(goal_node);
}

SearchResult DepthFirstSearch::search() noexcept {
    SearchResult result;
    logTrace("Начало обратного поиска в глубину.\n"sv);
    while(!m_solution_flag && !m_no_solution_flag) {
        int rule_cnt = childSearch();
        if (m_solution_flag) {
            result.closed_rules = convertToVector(m_closed_rules.begin(), m_closed_rules.end());
            result.closed_vertices = convertToVector(m_closed_vertices.begin(), m_closed_vertices.end());
            result.found = m_solution_flag;
            return result;
        }

        if (!rule_cnt && m_opened_vertices.size() < 2) {
            m_no_solution_flag = true;
            return result;
        } else if (!rule_cnt) {
            backtrack();
        }
    }
    result.closed_rules = convertToVector(m_closed_rules.begin(), m_closed_rules.end());
    result.closed_vertices = convertToVector(m_closed_vertices.begin(), m_closed_vertices.end());
    return result;
}

Rule DepthFirstSearch::getBackOpenedRule() noexcept {
    return *m_opened_rules.rbegin();
}

void DepthFirstSearch::popBackOpenedRule() noexcept {
    if (!m_opened_rules.empty()) {
        auto it = std::prev(m_opened_rules.end());
        m_opened_rules.erase(it);
    }
}

bool DepthFirstSearch::add_new_goal(const Vertices &vertices) noexcept {
    bool new_goal_flag = false;
    for (auto it = vertices.rbegin(); it != vertices.rend(); ++it) {
        if (!m_closed_vertices.contains(*it)) {
            m_opened_vertices.push(*it);
            new_goal_flag = true;
        }
    }
    return new_goal_flag;
}

bool DepthFirstSearch::is_forbidden_node_exists(const Vertices& vertices) noexcept {
    return std::any_of(vertices.begin(), vertices.end(), [this](const auto& vertex){
        return m_forbidden_vertices.contains(vertex);
    });
}

int DepthFirstSearch::childSearch() noexcept {
    int cnt_rules = 0;
    for (const Rule& const_rule: m_rules) {
        std::cout << "Текущее правило: " << const_rule.id << std::endl;
        Vertex current_vertex = m_opened_vertices.top();
        std::cout << "Текущая вершина: " << current_vertex.id << std::endl;
        logTrace("Поиск потомков.\n"sv);
        Rule& rule = const_cast<Rule&>(const_rule);
        if (rule.label != Label::OPEN) {
            continue;
        }

        if (rule.from == current_vertex) {
            rule.label = Label::VIEWED;
            m_opened_rules.push_back(rule);
            bool is_new_goal_added = add_new_goal(rule.to);
            if (!is_new_goal_added) {
                label();
            }

            cnt_rules += 1;
            break;
        }

        if (is_forbidden_node_exists(rule.to)) {
            m_forbidden_rules.insert(rule);
            rule.label = Label::FORBIDDEN;
        }
    }
    return cnt_rules;
}

void DepthFirstSearch::backtrack() noexcept {
    logTrace("Запуск бэктрекинга.\n"sv);
    Vertex current_vertex = m_opened_vertices.top();
    m_opened_vertices.pop();

    Rule rule = getBackOpenedRule();
    popBackOpenedRule();

    current_vertex.label = Label::FORBIDDEN;
    m_forbidden_vertices.insert(current_vertex);

    rule.label = Label::FORBIDDEN;
    m_forbidden_rules.insert(rule);

    for (const auto& node : rule.to) {
        m_opened_vertices.remove_element(node);
    }
}

void DepthFirstSearch::label() noexcept {
    logTrace("Запуск метода label.\n"sv);
    while (true) {
        const Rule rule = getBackOpenedRule();
        popBackOpenedRule();
        m_closed_rules.insert(rule);

        const Vertex vertex = m_opened_vertices.top();
        m_opened_vertices.pop();
        m_closed_vertices.insert(vertex);

        if (vertex == m_target_vertex) {
            m_solution_flag = true;
            break;
        }

        const Vertex current_vertex = m_opened_vertices.top();
        const Rule current_rule = getBackOpenedRule();
        if (current_rule.from != current_vertex) {
            break;
        }
    }
}

void DepthFirstSearch::logTrace(std::string_view custom_message) noexcept {
    Tracing tracing(INDENT);
    tracing << custom_message;

    tracing << "Список открытых вершин: ";
    join(m_opened_vertices, std::cout, ", ");
    std::cout << std::endl;

    tracing << "Список открытых правил: ";
    join(m_opened_rules, std::cout, ", ");
    std::cout << std::endl;

    tracing << "Список закрытых вершин: ";
    join(m_closed_vertices, std::cout, ", ");
    std::cout << std::endl;

    tracing << "Список доказанных правил: ";
    join(m_closed_rules, std::cout, ", ");
    std::cout << std::endl;

    tracing << "Список запрещенных вершин: ";
    join(m_forbidden_vertices, std::cout, ", ");
    std::cout << std::endl;

    tracing << "Список запрещенных правил: ";
    join(m_forbidden_rules, std::cout, ", ");
    std::cout << std::endl;
    std::cout << "#################################\n";
}