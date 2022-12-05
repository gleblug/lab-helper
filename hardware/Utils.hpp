#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

using port_t = std::size_t;
using ind_t = std::size_t;

enum class channels
{
    C1 = 1,
    C2 = 2
};

std::vector<std::string> files_path(std::string const &path);

double strtod(std::string const &number);
