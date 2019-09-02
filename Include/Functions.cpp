#include "Functions.h"

#define PI 3.14159265

//Returns length of 2D vector, vec
float length(sf::Vector2f vec) {
	if (sq(vec.x) + sq(vec.y) < 0) return 0;
	return sqrt(sq(vec.x) + sq(vec.y));
}

//returns angle in radians between two 2D vectors, vec1 and vec2, using dotProd function
float angleBetween(sf::Vector2f vec1, sf::Vector2f vec2) {
	if (length(vec1)*length(vec2) == 0) return 0;
	return acos(dotProd(vec1,vec2)/(length(vec1)*length(vec2)));
}

//returns dot product of two 2D vectors, vec 1 and vec2
float dotProd(sf::Vector2f vec1, sf::Vector2f vec2) {
	return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

//Return angle in radians of vec from origin
float angle2f(sf::Vector2f vec) {
	if (vec.x == 0) {
		if (vec.y > 0) return PI;
		else return 0;
	}
	float angle = PI / 2 + atan(vec.y / vec.x);
	if (vec.x < 0) angle += PI;
	return angle;
}

//Returns the square of a num
float sq(float num) {
	return num * num;
}

//Gets connector for body part from specific input currentline = "XX YY" 
sf::Vector2f getConnector(std::string currentLine) {
	return sf::Vector2f((float) std::stoi(currentLine.substr(0,2)),(float) std::stoi(currentLine.substr(3,5)));
}

//Gets 2D Perlin noise vector of values from [0,1] (Make sure size is power of 2?)
std::vector<std::vector<float>> perlin2D(int size) {

	std::vector<std::vector<int>> randNoise;
	for (int i = 0; i < size; i++) {
		std::vector<int> randRow;
		for (int j = 0; j < size; j++) {
			randRow.push_back(rand() % 100);
		}
		randNoise.push_back(randRow);
	}

	std::vector<std::vector<float>> perlin;
	std::vector<float> zeroRow;
	for (int j = 0; j < size; j++) {
		zeroRow.push_back(0.f);
	}
	for (int j = 0; j < size; j++) {
		perlin.push_back(zeroRow);
	}

	for (int i = 2; i <= size; i *= 2) {
		int subDiv = size / i;
		for (int j = 0; j < size; j += subDiv) {
			for (int k = 0; k < size; k += subDiv) {
				perlin[j][k] += (1.f / i) * randNoise[j][k];
				for (int l = k - subDiv; l < k && k > 0 && j > 0; l++) {
					//TOP ROW
					//perlin[j - subDiv][l] += (1.f / i) * interPoint((float)randNoise[j - subDiv][k - subDiv], (float)randNoise[j - subDiv][k], l - k + subDiv, subDiv);
					//BOTTOM ROW
					//perlin[j][l] += (1.f / i) * interPoint((float)randNoise[j][k - subDiv], (float)randNoise[j][k], l - k + subDiv, subDiv);
					//Column Loop
					//for (int m = j - subDiv + 1; m < j; m++) {
					//	perlin[m][l] += (1.f / i) * interPoint((float)randNoise[j - subDiv][l], (float)randNoise[j][l], m - j + subDiv, subDiv);
					//}
					for (int m = j - subDiv; m < j; m++) {
						sf::Vector2u current = sf::Vector2u(m - j + subDiv, l - k + subDiv);
						if (current.x <= (subDiv - current.y)) perlin[m][l] += interPointTriangleTL((float)randNoise[j - subDiv][k - subDiv], (float)randNoise[j - subDiv][k], (float)randNoise[j][k - subDiv], current, subDiv);
						else perlin[m][l] += interPointTriangleBR((float)randNoise[j][k], (float)randNoise[j][k - subDiv], (float)randNoise[j - subDiv][k], current, subDiv);
					}
				}
			}
		}
	}

	float maxNoise = 0;
	for (int i = 0; i < perlin.size(); i++) {
		for (int j = 0; j < perlin[i].size(); j++) {
			if (perlin[i][j] > maxNoise) maxNoise = perlin[i][j];
		}
	}
	for (int i = 0; i < perlin.size(); i++) {
		for (int j = 0; j < perlin[i].size(); j++) {
			perlin[i][j] = perlin[i][j] / maxNoise;
		}
	}

	return perlin;
}

//Returns float intermediary point on a straight line at integer position pos of interval of int length with points at height heightI (initial) and heightF (final)
float interPointLine(float heightI, float heightF, int pos, int length) {
	return (heightF - heightI) * pos / (length - 1) + heightI;
}

//Returns float intermediary height of point in pos in a right triangle plane in 3D, with heights heightOne (right angle), heightTwo (right of heightOne), and heightThree (bottom of heightOne)
//with leg length legLength (This is the top left triangle only between these three points)
float interPointTriangleTL(float heightOne, float heightTwo, float heightThree, sf::Vector2u pos, int legLength) {
	if (pos.x > (legLength - pos.y)) std::cout << "Not in TL triangle, Giving invalid results" << std::endl;
	return heightOne + ((heightTwo - heightOne) / (float)legLength) * pos.x + ((heightThree - heightOne) / (float)legLength) * pos.y;
}

//Returns float intermediary height of point in pos in a right triangle plane in 3D, with heights heightOne (right angle), heightTwo (left of heightOne), and heightThree (top of heightOne)
//with leg length legLength (This is the bottom right triangle only between these three points)
float interPointTriangleBR(float heightOne, float heightTwo, float heightThree, sf::Vector2u pos, int legLength) {
	if (pos.x < (legLength - pos.y)) std::cout << "Not in BR triangle, Giving invalid results" << std::endl;
	return heightThree + heightTwo - heightOne + ((heightOne - heightTwo) / (float)legLength) * pos.x + ((heightOne - heightThree) / (float)legLength) * pos.y;
}

//Returns average float of all floats in arr in circle of radius around point arr[row][column] 
float averageAbout(int row, int column, std::vector<std::vector<float>> &arr, int radius) {
	float avg = 0;
	for (int i = max(0,row - radius); i < min(arr.size(), row + radius + 1); i++) {
		for (int j = max(column - radius,0); j < min(arr[i].size(), column + radius + 1); j++) {
			if (length(sf::Vector2f((float)i - row, (float)j - column)) <= radius) avg += arr[i][j];
		}
	}
	avg = avg / (PI * sq(radius));
	return avg;
}

//returns max between 2 ints
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

//returns min between 2 ints
int min(int a, int b) {
	if (a < b) return a;
	else return b;
}

//Returns float value that is such that passed percent (decimal form - ie 20% passed as .20) of 2D arr has values greater than it (assumes rectangle array), accuracy of increment
float percentBound(float percent, std::vector<std::vector<float>> &arr) {
	int size = arr.size() * arr[0].size();
	float increment = .025;
	float bound = 1;
	int count = 0;
	while (count <= size * percent) {
		count = 0;
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr[i].size(); j++) {
				if (arr[i][j] >= bound) count++;
			}
		}
		bound -= increment;
	}
	bound += increment;
	return bound;
}

/*
TEST MAIN
int main() {

	std::vector<std::vector<float>> perlin = perlin2D(64);

	//std::cout << fixed;
	std::cout.precision(3);

	for (int i = 0; i < perlin.size(); i++) {
		for (int j = 0; j < perlin[i].size(); j++) {
			std::cout << perlin[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
*/