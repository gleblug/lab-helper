#include "Utils.hpp"

#include <iostream>

std::vector<std::string> files_path(std::string const &path)
{
    size_t file_ind = path.find_last_of('/') + 1;
    std::string directory = path;
    directory.erase(file_ind);

    auto directory_iterator = fs::directory_iterator(directory);
    std::vector<std::string> files_path;

    for (const auto &directory_entry : directory_iterator)
    {
        auto filename = std::string(directory_entry.path());
        if (!filename.find(path))
            files_path.push_back(filename);
    }

    return files_path;
}

double strtod(std::string const &value)
{
    double number;
    std::istringstream iss(value);
    iss >> number;
    return number;
}
