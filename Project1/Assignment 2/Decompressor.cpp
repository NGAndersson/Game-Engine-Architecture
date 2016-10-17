#include "Decompressor.h"

Decompressor::Decompressor()
{


}

Decompressor::~Decompressor()
{


}

char* Decompressor::decompress(string Path, string fileName)
{

	char* retFile;
	int error = 0;
	zip* temp = zip_open(Path.c_str(), 0, &error);

	struct zip_stat stats;
	zip_stat_init(&stats);
	zip_stat(temp, fileName.c_str(), 0, &stats);

	retFile = new char[stats.size];

	zip_file* readData = zip_fopen(temp, fileName.c_str(), 0);
	zip_fread(readData, retFile, stats.size);
	zip_fclose(readData);
	zip_close(temp);

	return retFile;
}