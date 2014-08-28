#include <string>
#include <iostream>

#include "../lib/libuv/include/uv.h"
#include "libuvHandlers.hpp"
#include "Package.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

namespace libuvHandlers {

void renamedSpcFile(uv_fs_t* req) {
    if (req->result < 0) {
        cerr << "There was an error renaming file "
            << req->path
            << endl;
    }

    // clean up internal req structure
    uv_fs_req_cleanup(req);
    // free memory taken up by req since we no longer need it
    free(req);
}

void readDir(uv_fs_t* req) {
    if (req->result < 0) {
        cerr << "There was an error reading the directory: " << req->path << endl;
    } else {
        uv_dirent_t dent;

        while (UV_EOF != uv_fs_readdir_next(req, &dent)) {
            string name = dent.name;

            if (dent.type != UV_DIRENT_FILE || name.substr(name.size() - 3) != "spc") {
                continue;
            }

            name = req->path;
            name += "/";
            name += dent.name;

            Package* package = static_cast<Package*>(req->data);
            string newFilename = package->getSpcTitle(name);

            if (!newFilename.empty()) {
                // allocate memory for new req
                uv_fs_t* renameReq;
                renameReq = (uv_fs_t*) malloc(sizeof(uv_fs_t));

                uv_fs_rename(uv_default_loop(), renameReq, name.c_str(), newFilename.c_str(), renamedSpcFile);
            }
        }
    }

    // clean up internal req structure
    uv_fs_req_cleanup(req);
}

}
