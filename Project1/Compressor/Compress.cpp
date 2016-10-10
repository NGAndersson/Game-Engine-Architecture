#include "Compress.h"


Compress::Compress()
{

}

Compress::~Compress()
{

}

bool Compress::zipFile(string Path,XMFLOAT3* data)
{

	int error = 0;
	zip* temp = zip_open(Path.c_str(), ZIP_CREATE|ZIP_TRUNCATE, &error);

	if (temp==NULL)
	{
		printf("Fuckin could not open filepath");
	}

	unsigned long int test = sizeof(XMFLOAT3)*250;
	zip_source* source = zip_source_buffer(temp,data,test, 1);

	if (error != 0)
	{
		printf("Fucking could not create SourceBuffer");
	}

	zip_file_add(temp,"SomeVertexShit", source, ZIP_FL_OVERWRITE);
	//if (NULL == zip_close(temp))
	//	return false;
	return true;
	
}

XMFLOAT3* Compress::unZip(string Path,string fileName)
{
	int error = 0;
	zip* temp = zip_open(Path.c_str(), 0, &error);

	struct zip_stat stats;
	zip_stat_init(&stats);
	zip_stat(temp, fileName.c_str(), 0, &stats);

	XMFLOAT3* retVal = new XMFLOAT3[stats.size];

	zip_file *readVal = zip_fopen(temp, fileName.c_str(), 0);
	zip_fread(readVal, retVal, stats.size);
	zip_fclose(readVal);

	zip_close(temp);

	return retVal;
}