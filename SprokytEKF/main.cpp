
#include <stdio.h> 
#include "EKFLoader.h"

EKFLoader ekfLoader;
static const char* pFile = "E:\\Sprokyt\\Projects\\SprokytEKF\\data\\sensor_data.txt";
static const char* pFileOut = "E:\\Sprokyt\\Projects\\SprokytEKF\\data\\sensor_data_out.txt";

int main()
{
	int result = ekfLoader.LoadFile(pFile, pFileOut);
	if (!result)
		return -1;

	ekfLoader.Simulate();
	return 0;
}




