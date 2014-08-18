#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
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
    bool isValid() { return valid; }
private:
    std::string filename;
    std::string packageDir;
    bool valid = true;
	long sample_rate = 44100;
    Music_Emu* emu;
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

void Package::output(std::ostream& os = std::cout) {
    // Determine file type
    gme_type_t file_type;
    handle_error( gme_identify_file( filename.c_str(), &file_type ) );
    if ( !file_type )
        handle_error( "Unsupported music type" );

    gme_open_file(filename.c_str(), &emu, sample_rate);

    gme_info_t* trackInfo;
    gme_track_info( emu, &trackInfo, 0 );

    std::cout 
        /* times in milliseconds; -1 if unknown */
        << trackInfo->length << std::endl
        << trackInfo->intro_length << std::endl
        << trackInfo->loop_length << std::endl
        /* empty string if not available */
        << trackInfo->system << std::endl
        << trackInfo->game  << std::endl
        << trackInfo->song << std::endl
        << trackInfo->author  << std::endl
        << trackInfo->copyright  << std::endl
        << trackInfo->comment   << std::endl
        << trackInfo->dumper   << std::endl
        << std::endl;

    gme_free_info( trackInfo );
    delete emu;

    if (valid) os << baseDir << "/" << packageDir << std::endl;
    else os << filename << " not valid!" << std::endl;
}

int Package::unrar() const {
}

#endif
