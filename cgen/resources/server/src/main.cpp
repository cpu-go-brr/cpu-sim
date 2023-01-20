#include "httplib.hpp"
#include "gasm.hpp"
#include "${CPU_NAME}.hpp"

void addCORS(const httplib::Request &req, httplib::Response &res)
{
    res.set_header("Access-Control-Allow-Origin", req.get_header_value("Origin").c_str());
    res.set_header("Allow", "GET, POST, HEAD, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept, Origin, Authorization");
    res.set_header("Access-Control-Allow-Methods", "OPTIONS, GET, POST, HEAD");
}

int main(int argc, char **argv)
{
    ${CPU_NAME} cpu;
    GenericAssembler ga;
    httplib::Server svr;
    
    svr.Get("/simulate", [&](const httplib::Request &req, httplib::Response &res)
            {
                cpu.simulate();
                addCORS(req,res);
                res.set_content("", ""); 
            });

    svr.Get("/get", [&](const httplib::Request &req, httplib::Response &res)
            {
                addCORS(req,res);
                res.set_content(cpu.json(), "application/json"); 
            });


    svr.Post("/flash", [&](const httplib::Request &req, httplib::Response &res)
    {
        std::cout << req.body << "\n";
        auto ints = ga.assemble_string(req.body);
        std::vector<bitset> bitsets;
        for(auto i : ints)
            bitsets.push_back(i);
        cpu.flash_rom(bitsets);


        addCORS(req,res);
        res.set_content("", "");
    });
    
    svr.listen("0.0.0.0", 8080);
    
    return 0;
}
