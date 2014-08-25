#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include "../extlib/game-music-emu-0.6.0/gme/gme.h"
#include "../extlib/game-music-emu-0.6.0/gme/Music_Emu.h"

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
    void handle_error(const char* str) const {
        if (str) {
            printf( "Error: %s\n", str ); getchar();
            exit( EXIT_FAILURE );
        }
    }
    int unrar() const;
    friend int unrarFile(const Package&, std::string outputDir);
    bool isValid() { return valid; }
private:
    bool valid = true;
    std::string filename;
    std::string packageDir;
    static Music_Emu* emu;
    const static long sample_rate = 44100;
};

#endif
