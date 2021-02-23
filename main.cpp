#include "stdafx.h"

std::filesystem::directory_entry vmpPath;

int main(int argc, char* argv[])
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    bool isObfuscated = false;
    // main
    SetConsoleTitleA("VMP-Randomizer by SwenenzY :)");
    std::cout << "[+] Initializing..." << std::endl;

    // have args 
    if (argv[1]) { // vmp-randomizer.exe vmp-randomizer.exe.vmp
        if (std::filesystem::exists(argv[1])) { // is file exists ?
            std::cout << "[!] Working directory : " << argv[1] << std::endl; // print
            std::cout << "[+] Starting obfuscation." << std::endl; // print
            // obfuscate here
            isObfuscated = ObfuscateVMP(argv[1]);
            if(isObfuscated)  std::cout << "[+] Successfly obfuscated." << std::endl;
        }
        else { // file doesnt exists
            std::cout << "[-] The specified path does not contain vmp." << std::endl; // print
        }
    }
    else { // vmp not specified we need to found auto
        std::cout << "[-] Vmp not specified. Trying to find automatically" << std::endl; // print

        // current dir + "\\" "C:\Users\Administrator\source\repos\vmp-randomizer\x64\"
        string dir = std::filesystem::current_path().string() + "\\"; 
        std::cout << "[!] Working directory : " << dir << std::endl; // print

        bool Status = false; // for check
        for (const auto& entry : fs::directory_iterator(std::filesystem::current_path()))
        {
            // if file extension is vmp
            if (fs::path(entry.path()).extension().string() == ".vmp") {
                // save status true and entry
                Status = true;
                vmpPath = entry;
            }
        }
        // if vmp
        if (Status) {
            // first check file for bug check
            if (std::filesystem::exists(vmpPath.path().string())) {
                std::cout << "[+] Starting obfuscation." << std::endl; //print
                // obfuscate here
                isObfuscated = ObfuscateVMP(vmpPath.path().string());
                if (isObfuscated)  std::cout << "[+] Successfly obfuscated." << std::endl;
            }
            // error
            else {
                std::cout << "[-] Failed to get vmp path." << std::endl; //print
            }
        }
        // error
        else {
            std::cout << "[-] System failed or folder does not contain vmp." << std::endl; //print
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    if(isObfuscated) std::cout << "\n[-] Finished operation in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
    return 0;
}

bool ObfuscateVMP(string path) {
    bool Status = false;
    // first check why its 3.? I don't know too just beautiful: D
    if (std::filesystem::exists(path)) {
        // we need to found .custom
        // <Protection InputFileName="vmp-randomizer.exe" Options="857032" VMCodeSectionName=".Custom">
        // VMCodeSectionName=".Custom"

        std::ifstream file(path);
        std::string str;
        std::string tempfile;
        while (std::getline(file, str))
        {
            // if line have VMCodeSectionName 
            if (str.find("VMCodeSectionName") != std::string::npos) {
                // trim to VMCodeSectionName
                std::string SectionString = str.substr(str.find("VMCodeSectionName")); // VMCodeSectionName=".Custom">
                // trim VMCodeSectionName

                // i found bug
                // VMCodeSectionName=".test" OutputFileName="test.sys"> if have OutputFileName crashing

                replaceAll(SectionString,"VMCodeSectionName=",""); //".Custom">

                // if have OutputFileName
                if (SectionString.find("OutputFileName") != std::string::npos) {
                    // get last string OutputFileName="test.sys"> 
                    std::string JunkString = str.substr(str.find("OutputFileName"));
                    // remove from ".test" OutputFileName="test.sys">
                    replaceAll(SectionString, JunkString, ""); //".Custom">
                    // and = ".test"
                    // ez fix
                }
               
                // trim junk
                replaceAll(SectionString, "\"", ""); // .Custom>
                // trim junk
                replaceAll(SectionString, ">", ""); // .Custom

                // before check null
                if (SectionString.find(" ") != std::string::npos) {
                    replaceAll(SectionString, " ", "");
                }
                // print 
                std::cout << "[!] Old Section : " << SectionString << std::endl;

                //setup random
                srand((unsigned int)time(NULL));
                int RandomHash = rand() % 50;
                // if random number lower 4 rundem number 16
                if (RandomHash < 4) RandomHash = 16;
                // create string from random number
                string RandomSection = "." + random_string_only_char(RandomHash);
                // print
                std::cout << "[+] New Section : " << RandomSection << std::endl;
                // replace old section to new section
                replaceAll(str, SectionString, RandomSection);
                // save status
                Status = true;
            }
            // save temp file
            tempfile += str + "\n";
        }
        // only re write when found
        if (Status) {
            // create ofstream
            ofstream myfile;
            // open stream
            myfile.open(path);
            myfile << tempfile; // re output file
            // close stream
            myfile.close();
        }
    }
    return Status;
}