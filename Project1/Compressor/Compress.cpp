#include "Compress.h"


Compress::Compress()
{

}

Compress::~Compress()
{

}

bool Compress::zipTest(string Path, string file)
{

	int error = 0;
	zip* temp = zip_open(Path.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &error);
	if (temp == NULL)
	{
		printf("Fuckin could not open filepath");
	}

	string td = "Ap Suger So Mkt \n Oscar suger lika mycket som ap";
	unsigned long int test = td.size();
	zip_source* source = zip_source_buffer(temp, td.c_str(), test, 1);

	if (source == NULL)
	{
		printf("Fucking could not create SourceBuffer");
	}

	zip_file_add(temp,file.c_str(), source, ZIP_FL_OVERWRITE);
	zip_close(temp);

	return true;
}

bool Compress::zipFile(string Path,string file,string fileName)
{

	//File shit
	ifstream inFile;
	inFile.open(file, ifstream::in);
	vector<char> tempChar;

	while (inFile.eof())
	{
		tempChar.push_back(inFile.get());
	}



	int error = 0;
	zip* temp = zip_open(Path.c_str(), ZIP_CREATE|ZIP_TRUNCATE, &error);
	if (temp==NULL)
	{
		printf("Fuckin could not open filepath");
	}

	unsigned long int test = sizeof(char)*tempChar.size();
	zip_source* source = zip_source_buffer(temp,reinterpret_cast<char*>(tempChar.data()),test, 1);

	if (source == NULL)
	{
		printf("Fucking could not create SourceBuffer");
	}

	zip_file_add(temp,fileName.c_str(), source, ZIP_FL_OVERWRITE);
	
	//if (NULL == zip_close(temp))
	//	return false;
	return true;
	
}

char* Compress::unZip(string Path,string fileName)
{
	int error = 0;
	zip* temp = zip_open(Path.c_str(), 0, &error);

	struct zip_stat stats;
	zip_stat_init(&stats);
	zip_stat(temp, fileName.c_str(), 0, &stats);

	char* retVal = new char[stats.size];
	zip_file *readVal = zip_fopen(temp, fileName.c_str(), 0);
	zip_fread(readVal, retVal,stats.size);
	zip_fclose(readVal);
	zip_close(temp);
	retVal[stats.size] = '\0';
	return retVal;
}