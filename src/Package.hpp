#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <iostream>

class Package {
public:
    Package(char* filename) : filename(filename) { }
    static std::string baseDir;
    void outputName(std::ostream& os = std::cout)
        { os << baseDir << "/" << filename << std::endl; }
private:
    std::string filename;
};

std::string Package::baseDir;

#endif
