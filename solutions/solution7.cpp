#include "solution7.h"
#include "solutions.h"

#include "../utils/read.h"

#include <cassert>
#include <numeric>
#include <functional>
#include <iostream>

auto Solutions::solution7() -> Answers {
    auto lines = Utils::readTokens<3>("inputs/input7.txt");

    Directory root = buildTree(lines);

    int answerA = root.totalSizeOfAllSubdirsWithAtMostMaxSize(100000);

    return { std::to_string(answerA), "" };

}

auto buildTree(const std::vector<Line>& lines) -> Directory {
    Directory root{nullptr}; // No parent

    Directory* cwd = &root;
    for (auto it = lines.cbegin(); it != lines.cend();) {

        const auto& line = *it;

        //std::cout << (it-lines.cbegin()+1) << ": " << line[0] << " " << line[1] << " " << line[2] << std::endl;

        assert(("Attempting to process non-instruction", isInstruction(line)));
        
        const std::string& command = line[1];
        if (command == "cd") {
            const std::string& dest = line[2];
            cwd = changeDir(&root, *cwd, dest);
            ++it; // Next instruction
        } else if (command == "ls") {
            handleListDir(*cwd, it);
            // Required ++it occurs at last iteration of function call for-loop
        } else {
            assert("Unknown command encountered");
        }
    }

    return root;
}

auto isInstruction(const Line& line) -> bool {
    return line[0] == "$";
}

auto isBlank(const Line& line) -> bool {
    return line[0].empty();
}

auto changeDir(Directory* const root, const Directory& cwd, const std::string& dest) -> Directory* {
    if (dest == "/") {
        return root;
    } else if (dest == "..") {
        assert(("Attempting to cd to non-existent parent", cwd.parent != nullptr));
        return cwd.parent;
    } else {
        assert(("Attempting to cd to subdir that doesn't exist", cwd.subdirs.contains(dest)));
        return cwd.subdirs.at(dest);
    }
}

auto handleListDir(Directory& cwd, std::vector<Line>::const_iterator& it) -> void {
    for (++it; !isInstruction(*it) && !isBlank(*it) ; ++it) {
        auto response = *it;
        if (response[0] == "dir") {
            cwd.subdirs[response[1]] = new Directory(&cwd);
        } else {
            cwd.files.emplace_back(response[1], std::stoi(response[0]));
        }
    }
}

Directory::Directory(Directory* parent) : parent(parent) { }

auto Directory::getIncludedFileSize() const -> int {
    return std::transform_reduce(
        files.cbegin(), files.cend(),
        0, std::plus{},
        [](const File& file){ return file.size; }
    );
}

auto Directory::getTotalSize() const -> int {
    return getIncludedFileSize() + std::transform_reduce(
        subdirs.cbegin(), subdirs.cend(),
        0, std::plus{},
        [](const auto& subdir) { return subdir.second->getTotalSize(); }
    );
}

// This is an insane metric to calculate. I also can't see how it's easier if calculated while progressing linearly through the raw input.
auto Directory::totalSizeOfAllSubdirsWithAtMostMaxSize(int subdirMaxSize) const -> int {
    // Get sizes of all subdirs, according to both metrics
    int qualifyingSubdirSizes = std::transform_reduce(
        subdirs.cbegin(), subdirs.cend(),
        0, std::plus{},
        [subdirMaxSize](const auto& subdir) {
            return subdir.second->totalSizeOfAllSubdirsWithAtMostMaxSize(subdirMaxSize);
        }
    );

    // Get own total size (according to normal definition)
    int totalSize = getTotalSize();

    return (totalSize <= subdirMaxSize ? totalSize : 0) + qualifyingSubdirSizes;
}

auto Directory::createSubdir(const std::string& name) {
    Directory* subDir = new Directory{this};
}