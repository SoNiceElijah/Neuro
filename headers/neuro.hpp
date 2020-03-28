#ifndef __NEURO_H__
#define __NEURO_H__

#include <cmath>
#include <random>
#include <vector>
#define M_PI 3.14159265358979323846


class neuron;

typedef std::vector<neuron> layer;

class neuron {
private:
	double val;

	layer next;
	layer prev;

	std::vector<double> weight;
	std::vector<double> delta;

	double grad;

	static double a;
	static double e;

	static double activation(double x);
	static double derivative(double x);
public:
	neuron();
	neuron(layer& _prev);
	void after(layer& _next);

	double value();
	void value(double x);

	void calculate();
};



#endif 
