#include <exception>
#include <iostream>

#include <ResolutionSolver.hpp>

#include "types/atom.hpp"
#include "types/clause.hpp"
#include "types/formula.hpp"
#include "types/terminal.hpp"

int main() {

    try {
        constexpr auto kNegative = true;

        // Определяем термины (константы и переменные)
        const Terminal v_Petya = Terminal::Variable("Петя");
        const Terminal v_Lena = Terminal::Variable("Лена");
        const Terminal v_Kolya = Terminal::Variable("Коля");
        const Terminal c_Dozhd = Terminal::Constant("Дождь");
        const Terminal c_Sneg = Terminal::Constant("Снег");

        // переменная для снега и дождя
        const Terminal v_X = Terminal::Variable("X");
        const Terminal v_Y = Terminal::Variable("Y");

        // S(A) | M(A)
        const Atom atom1 = {"S", {v_Petya}};
        const Atom atom2 = {"M", {v_Petya}};
        const Clause clause1 = {atom1, atom2};
        const Formula formula1 = {clause1};

        // S(B) | M(B)
        const Atom atom3 = {"S", {v_Lena}};
        const Atom atom4 = {"M", {v_Lena}};
        const Clause clause2 = {atom3, atom4};
        const Formula formula2 = {clause2};

        // S(C) | M(C)
        const Atom atom5 = {"S", {v_Kolya}};
        const Atom atom6 = {"M", {v_Kolya}};
        const Clause clause3 = {atom5, atom6};
        const Formula formula3 = {clause3};

        // ~M(x) | ~L(x, R)
        const Atom atom7 = {"M", {v_X}, true};
        const Atom atom8 = {"L", {v_X, c_Dozhd}, true};
        const Clause clause4 = {atom7, atom8};
        const Formula formula4 = {clause4};

        // ~S(x) | L(x, W)
        const Atom atom9 = {"S", {v_X}, true};
        const Atom atom10 = {"L", {v_X, c_Sneg}};
        const Clause clause5 = {atom9, atom10};
        const Formula formula5 = {clause5};

        // ~L(B, y) | ~L(A, y)
        const Atom atom11 = {"L", {v_Lena, v_Y}, true};
        const Atom atom12 = {"L", {v_Petya, v_Y}, true};
        const Clause clause6 = {atom11, atom12};
        const Formula formula6 = {clause6};

        // ~L(B, y) | ~L(A, y)
        const Atom atom13 = {"L", {v_Lena, v_Y}};
        const Atom atom14 = {"L", {v_Petya, v_Y}, true};
        const Clause clause7 = {atom13, atom14};
        const Formula formula7 {clause7};

        // L(A, R)
        const Atom atom15 = {"L", {v_Petya, c_Dozhd}};
        const Clause clause8 = {atom15};
        const Formula formula8 = {clause8};

        // L(A, W)
        const Atom atom16 = {"L", {v_Petya, c_Sneg}};
        const Clause clause9 = {atom16};
        const Formula formula9 = {clause9};

        // ~M(x) | S(x)
        const Atom atom17 = {"M", {v_X}, true};
        const Atom atom18 = {"S", {v_X}};
        const Clause clause10 = {atom17, atom18};
        const Formula neg_target = {clause10};

        ResolutionSolver({formula1, formula2,
                          formula3, formula4,
                          formula5, formula6,
                          formula7, formula8,
                          formula9}, neg_target).Solve();
        return 0;
    } catch (const std::exception& exception) {
        std::cout << "[exception] " << exception.what() << '\n';
        return 1;
    }
}
