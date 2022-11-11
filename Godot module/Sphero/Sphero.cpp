
/* summator.cpp */

#include "Sphero.h"


void Sphero::readFiles() {
	std::vector<std::vector<std::string>> velocities = read("C:/Users/Asal/godot/modules/Sphero/Velocity.csv");
	std::vector<std::vector<std::string>> distances = read("C:/Users/Asal/godot/modules/Sphero/Distance.csv");
	std::vector<std::vector<std::string>> Accelarations = read("C:/Users/Asal/godot/modules/Sphero/Accelerometer.csv");
	std::vector<std::vector<std::string>> Gyro = read("C:/Users/Asal/godot/modules/Sphero/Gyroscope.csv");
	std::vector<std::vector<std::string>> Location = read("C:/Users/Asal/godot/modules/Sphero/Location.csv");
	std::vector<std::vector<std::string>> Orientations= read("C:/Users/Asal/godot/modules/Sphero/Orientation.csv");
	SpheroData datas;
	for (int i = 0; i < velocities.size(); i++) {
		datas.time = std::stof(velocities.at(i).at(0));

		datas.V_X = std::stof(velocities.at(i).at(1));
		datas.V_Y = std::stof(velocities.at(i).at(2));
		datas.V_total = std::stof(velocities.at(i).at(3));
		
		datas.D_X = std::stof(distances.at(i).at(1));
		datas.D_Y = std::stof(distances.at(i).at(2));
		datas.D_total = std::stof(distances.at(i).at(3));

		datas.A_X = std::stof(Accelarations.at(i).at(1));
		datas.A_Y = std::stof(Accelarations.at(i).at(2));
		datas.A_Z = std::stof(Accelarations.at(i).at(3));
		datas.A_total = std::stof(Accelarations.at(i).at(4));

		datas.G_P = std::stof(Gyro.at(i).at(1));
		datas.G_R = std::stof(Gyro.at(i).at(2));
		datas.G_Y = std::stof(Gyro.at(i).at(3));

		datas.L_X = std::stof(Location.at(i).at(1));
		datas.L_Y = std::stof(Location.at(i).at(2));

		datas.O_P = std::stof(Orientations.at(i).at(1));
		datas.O_R = std::stof(Orientations.at(i).at(2));
		datas.O_Y = std::stof(Orientations.at(i).at(3));

		data.insert(i, datas);
	}

}

std::vector<std::vector<std::string>> Sphero::read(std::string path)
{
	std::vector<std::vector<std::string>> content;
	std::vector<std::string> row;
	std::string line, word;
	std::string notinfile = "cannot read";
	std::fstream file(path, std::ios::in);
	if (file.is_open()) {
		int count = 1;
		while (getline(file, line)) {
			if (count > 1) {
				row.clear();

				std::stringstream str(line);
				while (getline(str, word, ',')) 
					row.push_back(word);
				
				content.push_back(row);
			} else
				count++;
		}

	} else
		print_line(notinfile.c_str());
	return content;
}

float Sphero::speedSmootherX(int index1, int index2) {
	
	float sp1x = data.get(index1).V_X;
	float sp2x = data.get(index2).V_X;
	float difX = sp2x - sp1x;
	float framePer = (data.get(index2).time - data.get(index1).time)/frameRate;
	float speed = difX / framePer;

	return speed;
}

float Sphero::speedSmootherY(int index1, int index2) {
	float sp1y = data.get(index1).V_Y;
	float sp2y = data.get(index2).V_Y;
	float difY = sp2y - sp1y;
	float framePer = (data.get(index2).time - data.get(index1).time) / frameRate;
	float speed = difY / framePer;
	return speed;
}




int Sphero::getSize() {
	return data.size();
}
float Sphero::getTime(int index) {
	return data.get(index).time;
}
float Sphero::getVX(int index) {
	return data.get(index).V_X;
}
float Sphero::getVY(int index) {
	return data.get(index).V_Y;
}
float Sphero::getVT(int index) {
	return data.get(index).V_total;
}
float Sphero::getDX(int index) {
	return data.get(index).D_X;
}
float Sphero::getDY(int index) {
	return data.get(index).D_Y;
}
float Sphero::getDT(int index) {
	return data.get(index).D_total;
}
float Sphero::getAT(int index) {
	return data.get(index).A_total;
}

float Sphero::getOP(int index) {
	return data.get(index).O_P;
}

float Sphero::getOR(int index) {
	return data.get(index).O_R;
}


bool Sphero::isCollision(int index) {
	if (data.get(index).A_total >= 1.0 && (data.get(index - 1).A_total < data.get(index).A_total) && (data.get(index - 1).V_total > data.get(index).V_total)) {
		return true;
	}
	else
		return false;
}

void Sphero::_bind_methods() {
	ClassDB::bind_method(D_METHOD("readFiles"), &Sphero::readFiles);
	ClassDB::bind_method(D_METHOD("getSize"), &Sphero::getSize);
	ClassDB::bind_method(D_METHOD("getTime", "index"), &Sphero::getTime);

	ClassDB::bind_method(D_METHOD("getVX", "index"), &Sphero::getVX);
	ClassDB::bind_method(D_METHOD("getVT", "index"), &Sphero::getVT);
	ClassDB::bind_method(D_METHOD("getVY", "index"), &Sphero::getVY);

	ClassDB::bind_method(D_METHOD("getAT", "index"), &Sphero::getAT);
	
	ClassDB::bind_method(D_METHOD("getOP", "index"), &Sphero::getOP);
	ClassDB::bind_method(D_METHOD("getOR", "index"), &Sphero::getOR);

	ClassDB::bind_method(D_METHOD("getDT", "index"), &Sphero::getDT);
	ClassDB::bind_method(D_METHOD("getDX", "index"), &Sphero::getDX);
	ClassDB::bind_method(D_METHOD("getDY", "index"), &Sphero::getDY);

	ClassDB::bind_method(D_METHOD("speedSmootherX", "index1", "index2"), &Sphero::speedSmootherX);
	ClassDB::bind_method(D_METHOD("speedSmootherY", "index", "index2"), &Sphero::speedSmootherY);
	ClassDB::bind_method(D_METHOD("isCollision", "index"), &Sphero::isCollision);
}




Sphero::Sphero() {
	data = {};
}
