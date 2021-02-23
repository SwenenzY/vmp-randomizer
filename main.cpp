#include "stdafx.h"

int main(int argc, char* argv[])
{
    SetConsoleTitleA("VMP-Randomizer by SwenenzY :)");
    std::cout << "[+] Initializing..." << std::endl;

    if (argv[1]) {
        if (std::filesystem::exists(argv[1])) {

        }
        else {
            std::cout << "where is the vmp amk cocu.";
        }
    }
    else {
        for (const auto& entry : fs::directory_iterator(std::filesystem::current_path()))
        {
            std::cout << entry.path().string() << std::endl;
        }
        std::cout << "where is the vmp amk cocu.";
    }
}
