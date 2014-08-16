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
void makeBaseDir(string& baseDir) {
    if (baseDir.empty()) {
        baseDir = "processed";
    }

    // umask is 0220 by default.
    // setting to 0 makes the mkdir `mode` arg easier to read.
    mode_t um = umask(0);

    // set output directory mode to 0755 (since umask is now 000);
    int err = mkdir(baseDir.c_str(), 0755);
    if (err) {
        cout << "There was an error making the output directory: " << baseDir << endl;
        exit(2);
    }

    // reset umask to default
    um = umask(um);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "usage: "
             << argv[0]
             << " [-o baseDir]"
             << " rsn_files..."
             << endl;

        exit(1);
    }

    string baseDir;
    // a list of files to unrar into folders of the same name,
    // where they contain song files that need to be renamed
    // based on their internal metadata.
    vector<Package> games;
    // can pass this to unrar program
    string allGames;

    string arg;
    for (unsigned int i = 1; i != argc; ++i) {
        arg = argv[i];
        if (arg == "-o") {
            // cache baseDir and skip next arg
            baseDir = arg;
            ++i;
        } else {
            // conversion to class type through constructor
            games.push_back(arg);

            allGames += arg;
            allGames += " ";
        }
    }

    makeBaseDir(baseDir);
    Package::baseDir = baseDir;

    for (auto& game : games) {
        game.output();
    }

    cout << allGames << endl;

    return 0;
}
