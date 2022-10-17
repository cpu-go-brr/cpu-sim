#include <string>
#include <vector>

namespace Description
{
    class Instruction
    {
        std::string name = "", description = "", code = "", instruction = "";
    };

    class Memory
    {
    public:
        Memory(std::string key, YAML::Node config, std::vector<int> dimension = std::vector<int>());
        std::string name = "";
        int size = 0;
        std::vector<Memory> submemory;
    };

    class CPU
    {
    public:
        CPU(std::string path);
        std::string name, description;
        std::vector<Memory> memory;
    };

}