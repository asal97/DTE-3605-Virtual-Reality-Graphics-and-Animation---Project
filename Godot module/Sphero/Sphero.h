#pragma once
/* summator.h */

#ifndef SPHERO_H
#define SPHERO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <cmath>
#include "core/reference.h"
#include "struct.h"


class Sphero : public Reference {
	GDCLASS(Sphero, Reference);

	Vector<SpheroData> data;


protected:
	static void _bind_methods();

public:
	void readFiles();
	std::vector<std::vector<std::string>> read(std::string path);
	float speedSmootherX(int index1, int index2);
	float speedSmootherY(int index1, int index2);

	int getSize();
	float getVX(int index);
	float getTime(int index);
	float getVY(int index);
	float getVT(int index);

	float getDX(int index);
	float getDY(int index);
	float getDT(int index);

	float getAT(int index);

	float getOP(int index);

	float getOR(int index);

	bool isCollision(int index);

	Sphero();

	const float frameRate = 1.0 / 60.0;
 float threshHold = 1.0;

};

#endif // SUMMATOR_H
