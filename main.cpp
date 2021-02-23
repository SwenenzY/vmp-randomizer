#include "stdafx.h"

std::filesystem::directory_entry vmpPath;

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
        std::cout << "[-] Vmp not specified. Trying to find automatically" << std::endl;

        string dir = std::filesystem::current_path().string() + "\\";
        std::cout << "[!] Working directory : " << dir << std::endl;

        bool Status = false;
        for (const auto& entry : fs::directory_iterator(std::filesystem::current_path()))
        {
            string ext = fs::path(entry.path()).extension().string();
            std::cout << ext << std::endl;
            if (ext == ".vmp") { 
                Status = true;
                vmpPath = entry;
            }
        }
        if (Status) {
            if (std::filesystem::exists(vmpPath.path().string())) {
                std::cout << "[+]" << std::endl;
            }
            else {
                std::cout << "[-] Failed to get vmp path." << std::endl;
            }
        }
        else {
            std::cout << "[-] System failed or folder does not contain vmp." << std::endl;
        }
    }

    system("pause");
    return 0;
}
