
#include "EKFLoader.h"
#include <stdio.h> 
#include <iostream>
#include <fstream>

extern "C" {
#include "TinyEKF\TinyEKF.h"
}

static char* strsep(char **stringp, const char *delim);
static TinyEKF m_ekf;

EKFLoader::EKFLoader()
{
	TinyEKF_init(&m_ekf);
}

EKFLoader::~EKFLoader()
{

}

int EKFLoader::LoadFile(const char *filename, const char *file_out)
{
	int size = 0;
	FILE *f = fopen(filename, "r");
	if (f == NULL)
	{
		return -1; // -1 means file opening fail 
	}

	m_fileOut = file_out;

	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* result = (char *)malloc(size + 1);
	memset(result, 0, size + 1);
	int readSz = fread(result, sizeof(char), size, f);
	//if (size != readSz)
	//{
	//	free(result);
	//	return -2; // -2 means file reading fail 
	//}

	char* lineToken = NULL;
	char* valueToken = NULL;
	char* curr = result;
	while ((lineToken = strsep(&curr, "\n")))
	{
		Pose p;
		valueToken = strsep(&lineToken, ",");
		p.time = atoi(valueToken);

		valueToken = strsep(&lineToken, ",");
		p.uwb_x = (float)atof(valueToken);

		valueToken = strsep(&lineToken, ",");
		p.dd_x = (float)atof(valueToken);

		valueToken = strsep(&lineToken, ",");
		p.uwb_z = (float)atof(valueToken);

		valueToken = strsep(&lineToken, ",");
		p.dd_z = (float)atof(valueToken);

		valueToken = strsep(&lineToken, ",");
		p.imu_yaw = (float)atof(valueToken);

		valueToken = strsep(&lineToken, ",");
		p.dd_yaw = (float)atof(valueToken);

		m_posVec.push_back(p);

		printf("\n");
	}

	free(result);

	fclose(f);
	result[size] = 0;
	return size;
}

void EKFLoader::Simulate()
{
	ofstream outFile(m_fileOut);

	for (size_t i = 0; i < m_posVec.size(); ++i)
	{
		Pose& p = m_posVec[i];
		double z[] = { p.uwb_x, p.dd_x, p.uwb_z, p.dd_z, p.imu_yaw, p.dd_yaw };
		TinyEKF_step(&m_ekf, z);

		double _x = TinyEKF_getX(&m_ekf, 0);
		double _z = TinyEKF_getX(&m_ekf, 1);
		double _yaw = TinyEKF_getX(&m_ekf, 2);

		outFile << p.time << ',' << p.uwb_x << ',' << p.dd_x << ',' << p.uwb_z << ',' << p.dd_z << ',' << p.imu_yaw << ',' << p.dd_yaw << ',' << _x << ',' << _z << ',' << _yaw << endl;
	}
	
	outFile.close();
}

char* strsep(char **stringp, const char *delim)
{
	if (*stringp == NULL) { return NULL; }
	char *token_start = *stringp;
	*stringp = strpbrk(token_start, delim);
	if (*stringp)
	{
		**stringp = '\0';
		(*stringp)++;
	}
	return token_start;
}