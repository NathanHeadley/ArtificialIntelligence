#include "FuzzyTriangle.h"

void FuzzyTriangle::setInterval(double left_, double right_) {
	left = left_;
	right = right_;
}

void FuzzyTriangle::setMiddle(double left_) {
	middle = left_;
}

double FuzzyTriangle::getValue(double value_) {
	if (value_ <= left) {
		return 0;
	} else if (value_ < middle) {
		return (value_ - left) / (middle - left);
	} else if (value_ == middle) {
		return 1;
	} else if (value_ < right) {
		return (right - value_) / (right - middle);
	} else {
		return 0;
	}
}

double FuzzyTriangle::isInInterval(double value_) {
	if (value_ >= left && value_ <= right) {
		return getValue(value_);
	}
	return -1;
}