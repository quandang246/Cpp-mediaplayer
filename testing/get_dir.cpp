#include <string>
#include <iostream>
#include <limits.h>
#include <unistd.h>
#include <cstring> // Include for strrchr
#include <filesystem> // Include for std::filesystem::path

std::filesystem::path getexepath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        result[count] = '\0'; // Null-terminate the string
        // Find the last occurrence of '/' in the path
        char *lastSlash = strrchr(result, '/');
        if (lastSlash != nullptr) {
            *(lastSlash + 1) = '\0'; // Null-terminate at the position of the last '/'
            return std::filesystem::path(result);
        }
    }
    return ""; // Return an empty path if there's an error or no '/'
}

int main () 
{
    std::cout << "Dir: " << getexepath() << std::endl;
    return 0;
}
