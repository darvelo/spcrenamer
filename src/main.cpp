#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Package.hpp"
#include "../lib/libuv/include/uv.h"
#include "unrar.hpp"

using std::cout;
using std::cerr;
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
        cerr << "There was an error making the output directory: " << baseDir << endl;
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

    for (unsigned int i = 1; i != argc; ++i) {
        if (strcmp(argv[i], "-o") == 0) {
            // cache baseDir and skip next arg
            baseDir = argv[++i];
        } else {
            Package game(argv[i]);

            if (game.isValid()) {
                games.push_back(game);
            }
        }
    }

    makeBaseDir(baseDir);
    Package::baseDir = baseDir;

    for (auto& game : games) {
        game.process();
    }

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}
