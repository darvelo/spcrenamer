#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include "../lib/game-music-emu-0.6.0/gme/gme.h"
#include "../lib/game-music-emu-0.6.0/gme/Music_Emu.h"
#include "../lib/libuv/include/uv.h"

class Package {
public:
    /* constructors */
    Package() : valid(false) { };
    Package(std::string fname);

    /* variables */
    static std::string baseDir;
    static std::string extension;

    /* functions */
    inline void process() { unrar(); renameFiles(); };
    std::string getSpcInfo(const std::string& spcFilename);
    inline bool isValid() { return valid; }
private:
    /* functions */
    inline bool isFile() const;
    inline bool isFile(const std::string&) const;
    friend int unrarFile(const Package&, std::string outputDir);
    int unrar() const;
    void renameFiles();

    // invalid if not a rar file
    bool valid = true;
    // libuv request object
    uv_fs_t dirReq;
    // rar filename
    std::string filename;
    // output dir of unpacked rar
    std::string packageDir;
    // libgme structs/vars
    static Music_Emu* emu;
};

#endif
