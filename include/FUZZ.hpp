

#ifndef FUZZ_HPP
#define FUZZ_HPP

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <fstream>
#include <vector>
#include <curl/curl.h>
#include <exception>

class FUZZ {
    private:
        std::string nameFile;
        std::ifstream file;
        std::mutex lock_file;
        std::mutex lock_print;
        std::string IP;
        std::string user;
    public :
        FUZZ(std::string name, std::string IP, std::string user);
        void    creatThread();
        void    Broot();
        int     cheack(std::string pass);
};


#endif

