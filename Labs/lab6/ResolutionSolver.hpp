#pragma once
#include <cstdint>
#include <unordered_set>

#include <iostream>

#include <types/atom.hpp>
#include <types/clause.hpp>
#include <types/formula.hpp>

class ResolutionSolver {
public:
    ResolutionSolver(const std::vector<Formula>& formulas,
                     const Formula& neg_target);
    void Solve();

private:
    bool IsSeen(size_t x, size_t i, size_t y, size_t j);
    void SubstituteTerminals(const std::string& old_name,
                             const std::string& new_name,
                             bool do_make_const);
    static Clause GetNewClause(const std::vector<Atom>& a1,
                               size_t i,
                               const std::vector<Atom>& a2,
                               size_t j);
    bool AddNewClause(Clause new_clause, bool& is_final_result);
    bool UnifyAtoms(const Atom& a1, const Atom& a2);
    bool CheckClauses(size_t x, size_t y, bool& is_final_result);
    void PrintClauses() const;

private:
    std::vector<Clause> clauses_;
    std::unordered_set<size_t> seen_;
};
