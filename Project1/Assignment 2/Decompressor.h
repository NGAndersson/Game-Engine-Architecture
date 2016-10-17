#ifndef Decompressor_H
#define Decompressor_H

#include <stdio.h>
#include <string>
#include <assert.h>
#include <zlib.h>
#include <zip.h>
#include <sstream>

//--------------------------------------------------------------------------------
//Some hack required when using zlib to avoid JENS of input/output on windows.
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif
//--------------------------------------------------------------------------------

using namespace std;

class Decompressor
{
private:

public:
	Decompressor();
	~Decompressor();

	//Path is the name of the archive And FileName is the name of the file we want to read from.
	char* decompress(string Path,string fileName);


};



#endif


