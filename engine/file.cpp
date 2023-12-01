#include <dlfcn.h>
#include <sys/stat.h>
#include <string>
#include <algorithm>
#include <dirent.h>
#include <vector>
#include <err.h>
using namespace std;
bool isDirectory(const std::string& path) {
    struct stat statBuffer;
    if (stat(path.c_str(), &statBuffer) != 0)
        return false;
    return S_ISDIR(statBuffer.st_mode);
}//Returns file extension(e. g. .so, .txt)
string getFileExtension(const std::string& fileName) {
    size_t dotIndex = fileName.find_last_of(".");
    if (dotIndex != std::string::npos) 
        return fileName.substr(dotIndex + 1);
    return "";
}//ls command
vector<string> getFilesInDirectory(string path, string extension){
    vector<string> strs;
    DIR* directory = opendir(path.c_str());
    if (directory == nullptr)
        err(-1,"Failed to open directory.");
    dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        string fileName = entry->d_name;
        string extension1 = getFileExtension(fileName);
        if (fileName == "." || fileName == ".." || isDirectory(fileName) || extension1 != extension)
            continue;
        strs.push_back(path + fileName);
    }closedir(directory);
    return strs;
}
