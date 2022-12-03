#ifndef __READ_H
#define __READ_H

#include <string>
#include <vector>

namespace Utils {
    [[nodiscard]] std::vector<std::string> readLines(const char* path);
}

#endif