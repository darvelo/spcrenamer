#include <iostream>
#include <string>
#include <vector>
// fork() and exec()
#include <unistd.h>
// strcmp() for argv[]
#include <cstring>
// for mkdir()
#include <sys/stat.h>
#include <sys/types.h>

#include "Package.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

// directory where other directories are created to hold songs
void makeOutputDir(string& outputDir) {
    if (outputDir.empty()) {
        outputDir = "processed";
    }

    // umask is 0220 by default.
    // setting to 0 makes the mkdir `mode` arg easier to read.
    mode_t um = umask(0);

    // set output directory mode to 0755 (since umask is now 000);
    int err = mkdir(outputDir.c_str(), 0755);
    if (err) {
        cout << "There was an error making the output directory: " << outputDir << endl;
        exit(2);
    }

    // reset umask to default
    um = umask(um);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "usage: "
             << argv[0]
             << " [-o outputDir]"
             << " rsn_files..."
             << endl;

        exit(1);
    }

    string outputDir;
    // a list of files to unrar into folders of the same name,
    // where they contain song files that need to be renamed
    // based on their internal metadata.
    vector<Package> games;

    for (unsigned int i = 1; i != argc; ++i) {
        if (strcmp(argv[i], "-o") == 0) {
            // cache outputDir and skip next arg
            outputDir = argv[++i];
        } else {
            games.push_back(argv[i]);
        }
    }

    makeOutputDir(outputDir);
    Package::baseDir = outputDir;

    for (auto& game : games) {
        game.outputName();
    }

    return 0;
}
