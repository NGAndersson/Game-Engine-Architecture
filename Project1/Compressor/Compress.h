#ifndef Compressor_H
#define Compressor_H

#define ZIP_STATIC

#include <stdio.h>
#include <string>
#include <assert.h>
#include <zlib.h>
#include <zip.h>
#include <DirectXMath.h>

//--------------------------------------------------------------------------------
//Some hack required when using zlib to avoid JENS of input/output on windows.
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

using namespace std;
using namespace DirectX;

struct vektTest
{
	XMFLOAT3 pos;
	XMFLOAT3 nor;
	XMFLOAT2 tex;
};
class Compress
{
private:

public:

	Compress();
	~Compress();
	bool zipFile(string Path,XMFLOAT3* data);
	XMFLOAT3* unZip(string Path,string fileName);
};


#endif
