#ifndef __SOLUTION7_H_
#define __SOLUTION7_H_

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int TOTAL_DISK_SPACE = 70000000;
constexpr int UNUSED_DISK_SPACE_REQUIRED = 30000000;

struct File {
    std::string name;
    int size;
};

class Directory {
public:
    explicit Directory(Directory* parent);

    auto createSubdir(const std::string& name);
    auto getIncludedFileSize() const -> int;
    auto getTotalSize() const -> int;
    auto totalSizeOfAllSubdirsWithAtMostMaxSize(int maxSize) const -> int;
    auto smallestDeletionOfAtLeast(int minSize) const -> int;

    Directory* parent = nullptr;
    std::vector<File> files;
    std::unordered_map<std::string, Directory*> subdirs;
};

auto changeDir(Directory* const root, const Directory& cwd, const std::string& dest) -> Directory*;

using Line = std::array<std::string, 3>;

auto handleListDir(Directory& cwd, std::vector<Line>::const_iterator& it) -> void; // void apparently needed for auto deduction in this case

[[nodiscard]] auto buildTree(const std::vector<Line>& lines) -> Directory;

[[nodiscard]] auto isInstruction(const Line& line) -> bool;

[[nodiscard]] auto isBlank(const Line& line) -> bool;

#endif