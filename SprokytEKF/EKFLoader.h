#pragma once

#include <vector>
#include <string>

using namespace std;

struct Pose
{
	int time;
	float uwb_x;
	float dd_x;
	float uwb_z;
	float dd_z;
	float imu_yaw;
	float dd_yaw;
};

class EKFLoader
{
public:
	EKFLoader();
	~EKFLoader();

	int LoadFile(const char *filename, const char *file_out);
	void Simulate();

private:	
	vector<Pose> m_posVec;
	string m_fileOut;
};