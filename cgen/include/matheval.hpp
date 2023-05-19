#pragma once

#include <string>
#include <vector>

namespace MathExpression
{
    //evaluate a string with gioven values
    double eval(std::string formula, std::vector<std::pair<std::string, double>> vals = {});
}
