#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>;
#include "neuro.hpp";


class network {
private:
	std::vector<layer> layers;

	double error;
	double avgError;
	static double lastAvgError;
public:
	network(std::vector<int> topology);
	void feed(std::vector<double> input);
	std::vector<double> run();
	void correct(double* target);
	double getAvgError() const { return lastAvgError; }
};

#endif