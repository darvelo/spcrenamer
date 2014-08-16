#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

class Package {
public:
    /* constructors */
    Package() : valid(false) { };
    Package(std::string fname);

    /* variables */
    static std::string baseDir;
    static std::string extension;

    /* functions */
    inline bool isFile() const;
    inline bool isFile(const std::string&) const;
    void output(std::ostream& os = std::cout) const
        {
            if (valid) os << baseDir << "/" << packageDir << std::endl;
            else os << filename << " not valid!" << std::endl;
        }
    int unrar() const;
    bool isValid() { return valid; }
private:
    std::string filename;
    std::string packageDir;
    bool valid = true;
};

/*************
 * variables *
 *************/
std::string Package::baseDir;
std::string Package::extension = ".rsn";

/*************
 * functions *
 *************/
Package::Package(std::string fname)
    : filename(fname)
{
    if (!isFile(filename)) {
        valid = false;
        return;
    }

    // if not found, string::npos + 1 == 0
    auto slash = filename.find_last_of('/');
    // move past the slash
    ++slash;

    size_t extensionSize = extension.size();
    if (filename.substr(filename.size() - extension.size()) != extension) {
        extensionSize = 0;
    }

    packageDir = filename.substr(slash, filename.size() - slash - extensionSize);
}

bool Package::isFile(const std::string &filename) const {
    struct stat info;
    // stat succeeds && not a directory
    return !stat(filename.c_str(), &info) && !(info.st_mode & S_IFDIR);
}

bool Package::isFile() const {
    return isFile(filename);
}

int Package::unrar() const {
}

#endif
