#include <iostream>
#include <fstream>
#include "include/json.hpp"
#include "./include/FUZZ.hpp"

using json = nlohmann::json;

int main() {
    std::ifstream file(".rq.json");
    if (!file) {
        std::cerr << "Failed to open JSON file\n";
        return 1;
    }

    json args;
    file >> args;

    std::cout << args.dump(4) << std::endl;

    std::cout << "option: " << args["option"] << std::endl;
    std::cout << "user: " << args["user"] << std::endl;
    FUZZ *fuzz = new FUZZ(args["file"], args["ip"], args["user"]);
    fuzz->creatThread();
    delete fuzz;

    return 0;
}
