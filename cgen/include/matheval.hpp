#pragma once

#include <string>
#include <vector>

namespace MathExpression
{
    double eval(std::string formula, std::vector<std::pair<std::string, double>> vals = {});
}
