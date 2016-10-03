#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <stdio.h>
#include <string>
#include <assert.h>
#include <zlib.h>

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

class Compressor
{
private:

public:
	Compressor();
	~Compressor();
	void decompress(char* path);
	void compress();




};



#endif


