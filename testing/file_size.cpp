#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>


using namespace std;

streamsize file_size(const string &file_name);

int main(int argc, char *argv[])
{
    std::filesystem::path filePath = "/home/quan246/projects/src/mock_prj/file_sample/file_example_MP3_700KB.mp3";
    const char *filePathStr = filePath.c_str();
    cout << file_size(filePathStr);

    return 0;
}

streamsize file_size(const string &file_name)
{

    streamsize _size = 0;
    fstream file(file_name.c_str(), ios_base::in | ios_base::binary);
    if (file.is_open())
    {
        file.seekg(0, ios_base::end);
        _size = file.tellg();
        file.close();
        return _size;
    }
    else
        return 0;
}
