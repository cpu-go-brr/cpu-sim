#include "matheval.hpp"
#include <matheval.h>
#include <assert.h>
#include <iostream>

double MathExpression::eval(std::string formula, std::vector<std::pair<std::string, double>> vals)
{
    //Initialize two vectors
    std::vector<char *> cstrings{};
    std::vector<double> nums{};

    for (const auto& [name, val] : vals)
    {
        cstrings.push_back((char*)name.c_str());
        nums.push_back(val);
    }

    //create evaluator
    auto f = evaluator_create((char *)formula.c_str());
    //check that formular was correct
    assert(f);

    //obtain res
    auto res = evaluator_evaluate(f, vals.size(), cstrings.data(), nums.data());

    //clear up evaluator
    evaluator_destroy (f);
    return res;
}