// http://stackoverflow.com/questions/2327784/using-unrar-library-extracting-files-into-a-filestream-buffer
// Unofficial UNRAR API: http://goahomepage.free.fr/article/2000_09_17_unrar_dll/UnRARDLL.html

/*
 * compile the unrar library (libunrar.so) with:
 *   make clean
 *   make lib
 *
 * then include the library with something like:
 *   g++ projectmain.cpp thisfile.hpp ./libunrar.so -Wl,-rpath,'$ORIGIN'
 */

#include <iostream>
#include <cstring>
#include <string>

#include "Package.hpp"
#include "unrar.hpp"

#define _UNIX
#define  RARDLL
#include "../extlib/unrar-5.1.7/dll.hpp"

// same as HANDLE in dll.hpp
#define RARHANDLE void *

using std::cout;
using std::endl;
using std::string;

int unrarFile(const Package& spcPackage, string spcOutputDir = ".") {
  // the directory we'll extract the archives to
  char* outputDir = const_cast<char*>(spcOutputDir.c_str());
  char* filename = const_cast<char*>(spcPackage.filename.c_str());

  // declare and set parameters
  RARHANDLE rarFile;
  RARHANDLE rarFile2;
  RARHeaderDataEx fileInfo;
  RAROpenArchiveDataEx archiveInfo;

  // zero out allocated memory
  memset(&archiveInfo, 0, sizeof(archiveInfo));

  // don't read comments
  archiveInfo.CmtBuf = NULL;
  archiveInfo.OpenMode = RAR_OM_EXTRACT;
  archiveInfo.ArcName = filename;

  // Open file
  rarFile = RAROpenArchiveEx(&archiveInfo);
  rarFile2 = RAROpenArchiveEx(&archiveInfo);

  if (archiveInfo.OpenResult != 0) {
    RARCloseArchive(rarFile);
    cout  << "unrar couldn't open" << endl;
    return 2;
  }

  // don't read comments
  fileInfo.CmtBuf = NULL;

  // loop through archive
  int RHCode;
  while((RHCode = RARReadHeaderEx(rarFile, &fileInfo)) == 0) {
    RARReadHeaderEx(rarFile2, &fileInfo);

    // extracts to a directory
    // if the last param (*DestName) is NULL, the previous one (*DestPath) will be the output dir
    if (RARProcessFile(rarFile, RAR_EXTRACT, outputDir, NULL) != 0) {
      RARCloseArchive(rarFile);
      cout  << "error processing this file\n" << endl;
      return 3;
    }

  }

  if (RHCode != ERAR_END_ARCHIVE) {
    cout  << "error traversing through archive: " << RHCode << endl;
  }

  RARCloseArchive(rarFile);

  return 0;
}
