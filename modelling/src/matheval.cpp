#include "../include/matheval.hpp"
#include <matheval.h>
#include <assert.h>
#include <iostream>

double eval(std::string formula, std::vector<std::pair<std::string, double>> vals)
{

    std::vector<char *> cstrings{};
    std::vector<double> nums{};

    for (const auto& pair : vals)
    {
        cstrings.push_back((char*)pair.first.c_str());
        nums.push_back(pair.second);
    }

    auto f = evaluator_create((char *)formula.c_str());
    assert(f);

    auto res = evaluator_evaluate(f, vals.size(), cstrings.data(), nums.data());

    evaluator_destroy (f);
    return res;
}