#include "formula.hpp"

#include <initializer_list>
#include <vector>

//#include "clause.hpp"

Formula::Formula(const std::initializer_list<Clause> clauses)
        : clauses_{clauses} {}

const std::vector<Clause>& Formula::clauses() const {
    return clauses_;
}

std::vector<Clause>& Formula::clauses() {
    return clauses_;
}
