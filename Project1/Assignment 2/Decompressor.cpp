#include "Decompressor.h"

Decompressor::Decompressor()
{


}

Decompressor::~Decompressor()
{


}

char* Decompressor::decompress(string Path,string fileName)
{

	FILE* retFile;
	int error = 0;
	zip* temp = zip_open(Path.c_str(), 0, &error);

	struct zip_stat stats;
	zip_stat_init(&stats);
	zip_stat(temp, fileName.c_str(), 0, &stats);

	zip_file* readData = zip_fopen(temp, fileName.c_str(), 0);
	zip_fread(readData, retFile, stats.size);
	zip_fclose(readData);
	zip_close(temp);

	//XMFLOAT3* retVal = new XMFLOAT3[stats.size];
/*
	zip_file *readVal = zip_fopen(temp, fileName.c_str(), 0);
	zip_fread(readVal, retVal, stats.size);
	zip_fclose(readVal);

	zip_close(temp);
*/
}