#ifndef UNRAR_H
#define UNRAR_H

#include <string>
#include "Package.hpp"

int unrarFile(const Package& spcPackage, std::string spcOutputDir);

#endif
