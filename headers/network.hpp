#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <fstream>
#include "neuro.hpp";
#include <sstream>


class network {
private:
	std::vector<layer> layers;

	double error;
	double avgError;
	static double smooth;
public:
	network(std::vector<int> topology);
	void feed(std::vector<double> input);
	std::vector<double> run();
	void correct(std::vector<double> target);
	double getAvgError() const { return avgError; }

	void store(const char* name);
	static network load(const char* name);
};

#endif