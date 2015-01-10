#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "Package.hpp"
#include "../lib/game-music-emu-0.6.0/gme/gme.h"
#include "../lib/game-music-emu-0.6.0/gme/Music_Emu.h"
#include "../lib/libuv/include/uv.h"
#include "libuvHandlers.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

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
    auto slash = filename.rfind('/');
    // move past the slash
    ++slash;

    size_t extensionSize = extension.size();
    if (filename.substr(filename.size() - extension.size()) != extension) {
        extensionSize = 0;
    }

    packageDir = filename.substr(slash, filename.size() - slash - extensionSize);
}

string Package::getSpcTitle(const string& spcFilename) {
    // new filename based on track name
    string song;

    // Determine file type
    gme_type_t file_type;
    const char* err = gme_identify_file(spcFilename.c_str(), &file_type);
    if (err || !file_type) {
        cerr << "Unsupported music type in filename " << spcFilename;
        return song;
    }

    // a sample rate would be passed as the second arg here (unsigned long sample_rate = 44100),
    // *if* we needed access to the actual data in the spc file, e.g. transcoding to wav
    gme_open_file(spcFilename.c_str(), &emu, gme_info_only);

    gme_info_t* trackInfo;
    gme_track_info( emu, &trackInfo, 0 );

    // possible trackInfo values...
    /* cout */
    /*     /1* times in milliseconds; -1 if unknown *1/ */
    /*     << trackInfo->length << endl */
    /*     << trackInfo->intro_length << endl */
    /*     << trackInfo->loop_length << endl */
    /*     /1* empty string if not available *1/ */
    /*     << trackInfo->system << endl */
    /*     << trackInfo->game  << endl */
    /*     << trackInfo->song << endl */
    /*     << trackInfo->author  << endl */
    /*     << trackInfo->copyright  << endl */
    /*     << trackInfo->comment   << endl */
    /*     << trackInfo->dumper   << endl */
    /*     << endl; */

    // add track number designation from original filename, e.g. "s07" in filename "dkc-s07.spc"
    auto trackNumBegin = spcFilename.rfind('-');
    // move past dash
    ++trackNumBegin;

    song += spcFilename.substr(
            trackNumBegin,
            // the null byte takes care of the '.' in ".spc"
            spcFilename.size() - trackNumBegin - sizeof("spc")
    );

    song += '-';
    song += trackInfo->song;

    // replace any slashes with underscores
    for (auto &c : song) {
        if (c == '/') {
            c = '_';
        }
    }

    string newFilename = baseDir + '/' + packageDir + '/' + song + ".spc";

    gme_free_info( trackInfo );
    delete emu;

    return newFilename;
}

int Package::unrar() const {
    if (!valid) {
        cerr << "The file " << filename << " was not valid!" << endl;
        return -1;
    }

    string outputDir = baseDir + '/' + packageDir;

    // make dir for this SPC's songs in the baseDir
    int err = mkdir(outputDir.c_str(), 0777);
    if (err) {
        cerr << "There was an error making the output directory: " << outputDir << endl;
        return 1;
    }

    return unrarFile(*this, outputDir);
}

void Package::renameFiles() {
    const char* outputDir = (baseDir + '/' + packageDir).c_str();

    dirReq.data = this;

    uv_fs_readdir(uv_default_loop(), &dirReq, outputDir, O_RDONLY, libuvHandlers::readDir);
}
