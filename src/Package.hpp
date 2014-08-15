#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <iostream>

class Package {
public:
    Package(std::string fname);
    static std::string baseDir;
    void outputName(std::ostream& os = std::cout) const
        { os << baseDir << "/" << filename << std::endl; }
    int unrar() const;
private:
    std::string filename;
};

std::string Package::baseDir;

Package::Package(std::string fname) {
    if (fname[fname.size() - 1] == '/') {
        throw "Error: entered a directory as a filename.";
    }

    auto slashPos = fname.find_last_of('/');

    // don't need to handle the empty case because argv won't send empty strings.
    if (slashPos == std::string::npos) {
        filename = fname;
    } else {
        filename = fname.substr(slashPos + 1, std::string::npos);
    }
}

int Package::unrar() const {
}

#endif
