#include "Compress.h"
#include <stdio.h>
#include <string>


bool checkVal(XMFLOAT3 a, XMFLOAT3 b);


int main()
{


Compress test;
XMFLOAT3 impData[250];
XMFLOAT3* readData;
for (int i = 0; i < 250; i++)
{

	impData[i] = XMFLOAT3((float)i, (float)i*2, (float)i*3);

}

//bool kanske = test.zipFile("testFile.zip", impData);

readData = test.unZip("testFile.zip", "SomeVertexShit");
	
for (int i = 0; i < 250; i++)
{
	if (!checkVal(readData[i], impData[i]))
		return -1;
}
return 1;
}

bool checkVal(XMFLOAT3 a, XMFLOAT3 b)
{
	if (a.x != b.x || a.y != b.y || a.z != b.z)
		return false;
	else 
		return true;

}