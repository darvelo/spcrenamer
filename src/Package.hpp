#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include "../lib/game-music-emu-0.6.0/gme/gme.h"
#include "../lib/game-music-emu-0.6.0/gme/Music_Emu.h"
#include "../lib/libuv/include/uv.h"
#include "libuvHandlers.hpp"

class Package {
    friend int unrarFile(const Package&, std::string outputDir);
    friend void libuvHandlers::readDir(uv_fs_t* req);

public:
    /* constructors */
    Package() : valid(false) { };
    Package(std::string fname);

    /* variables */
    static std::string baseDir;
    static std::string extension;

    /* functions */
    void process() { unrar(); renameFiles(); };
    bool isValid() { return valid; }
private:
    /* functions */
    inline bool isFile() const;
    inline bool isFile(const std::string&) const;
    int unrar() const;
    std::string getSpcTitle(const std::string& spcFilename);
    void renameFiles();

    // invalid if not a rar file
    bool valid = true;
    // libuv request object
    uv_fs_t dirReq;
    // rar filename
    std::string filename;
    // output dir of unpacked rar
    std::string packageDir;
    // libgme class
    static Music_Emu* emu;
};

inline bool
Package::isFile(const std::string &fname) const {
    struct stat info;
    // stat succeeds && not a directory
    return !stat(fname.c_str(), &info) && !(info.st_mode & S_IFDIR);
}

inline bool
Package::isFile() const {
    return isFile(filename);
}

#endif
