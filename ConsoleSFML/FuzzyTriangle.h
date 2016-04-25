#ifndef FUZZYTRIANGLE_H
#define FUZZYTRIANGLE_H

#include <iostream>
#include <string>

class FuzzyTriangle {

protected:
	double left, right, middle;
	std::string type;

public:
	void setInterval(double left_, double right_);
	void setMiddle(double left_);
	void setType(std::string type_);
	double isInInterval(double value_);
	double getValue(double value_);

};

#endif