#include <Windows.h>
#include <iostream>
#include <filesystem>

// Namespace
using namespace std;
namespace fs = std::filesystem;


std::string GetCurrentPath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
}