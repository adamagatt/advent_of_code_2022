#ifndef __READ_UTILS_H
#define __READ_UTILS_H

#include <fstream>
#include <string>
#include <vector>

namespace ReadUtils {
    [[nodiscard]] std::vector<std::string> lines(const char* path);
}

#endif