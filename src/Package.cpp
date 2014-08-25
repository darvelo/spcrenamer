#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include "Package.hpp"
#include "../extlib/game-music-emu-0.6.0/gme/gme.h"
#include "../extlib/game-music-emu-0.6.0/gme/Music_Emu.h"

using std::cout;
using std::endl;
using std::string;
using std::ostream;

/*************
 * variables *
 *************/
string Package::baseDir;
string Package::extension = ".rsn";
Music_Emu* Package::emu;

/*************
 * functions *
 *************/
Package::Package(string fname)
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

bool Package::isFile(const string &filename) const {
    struct stat info;
    // stat succeeds && not a directory
    return !stat(filename.c_str(), &info) && !(info.st_mode & S_IFDIR);
}

bool Package::isFile() const {
    return isFile(filename);
}

void Package::output(ostream& os = cout) {
    // Determine file type
    gme_type_t file_type;
    handle_error( gme_identify_file( filename.c_str(), &file_type ) );
    if ( !file_type )
        handle_error( "Unsupported music type" );

    gme_open_file(filename.c_str(), &emu, sample_rate);

    gme_info_t* trackInfo;
    gme_track_info( emu, &trackInfo, 0 );

    cout
        /* times in milliseconds; -1 if unknown */
        << trackInfo->length << endl
        << trackInfo->intro_length << endl
        << trackInfo->loop_length << endl
        /* empty string if not available */
        << trackInfo->system << endl
        << trackInfo->game  << endl
        << trackInfo->song << endl
        << trackInfo->author  << endl
        << trackInfo->copyright  << endl
        << trackInfo->comment   << endl
        << trackInfo->dumper   << endl
        << endl;

    gme_free_info( trackInfo );
    delete emu;

    if (valid) os << baseDir << "/" << packageDir << endl;
    else os << filename << " not valid!" << endl;
}

int Package::unrar() const {
    if (!valid) {
        cout << "The file " << filename << " was not valid!" << endl;
        return -1;
    }

    string outputDir = baseDir + '/' + packageDir;

    // make dir for this SPC's songs in the baseDir
    int err = mkdir(outputDir.c_str(), 0777);
    if (err) {
        cout << "There was an error making the output directory: " << outputDir << endl;
        return 1;
    }

    return unrarFile(*this, outputDir);
}
