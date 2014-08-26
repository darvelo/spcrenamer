#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include "../extlib/game-music-emu-0.6.0/gme/gme.h"
#include "../extlib/game-music-emu-0.6.0/gme/Music_Emu.h"
#include "../extlib/libuv/include/uv.h"

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
    void output(std::ostream&);
    int unrar() const;
    friend int unrarFile(const Package&, std::string outputDir);
    bool isValid() { return valid; }
    void renameFiles();
private:
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
    const static long sample_rate = 44100;
};

#endif
