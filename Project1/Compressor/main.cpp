#include "Compress.h"
#include <string>

int main()
{

	Compress test;

	//bool kanske = test.zipFile("testFile.zip", impData);

	string arc = "bajsFile.zip";
	string fileName = "Ap/APoppo";
	//bool ds = test.zipTest(arc,fileName);


	char* d = test.unZip(arc, fileName);
	std::cout << "This is what comes back: " << d << endl;
	getchar();
	return 0;
}