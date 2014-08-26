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
#include "unrar.hpp"
#include "../extlib/libuv/include/uv.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

// directory where other directories are created to hold songs
void makeBaseDir(string& baseDir) {
    if (baseDir.empty()) {
        baseDir = "processed";
    }

    // set output directory mode to 0755 (since umask is 022);
    int err = mkdir(baseDir.c_str(), 0777);
    if (err) {
        cout << "There was an error making the output directory: " << baseDir << endl;
        exit(2);
    }
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

    string arg;
    for (unsigned int i = 1; i != argc; ++i) {
        arg = argv[i];
        if (arg == "-o") {
            // cache baseDir and skip next arg
            baseDir = argv[++i];
        } else {
            // conversion to class type through constructor
            games.push_back(arg);
        }
    }

    makeBaseDir(baseDir);
    Package::baseDir = baseDir;

    for (auto& game : games) {
        /* game.output(); */
        game.unrar();
        game.renameFiles();
    }

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}
