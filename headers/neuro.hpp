#ifndef __NEURO_H__
#define __NEURO_H__

#include <cmath>
#include <random>
#include <vector>
#include <iostream>;
#define M_PI 3.14159265358979323846


class neuron;

typedef std::vector<neuron> layer;

class neuron {
private:
	double val;

	layer* next;
	layer* prev;

	std::vector<double> weight;
	std::vector<double> delta;

	double grad;

	static double a;
	static double e;

	static double activation(double x);
	static double derivative(double x);

	int idx;
public:
	neuron();
	neuron(layer& _prev);
	void after(layer& _next);
	void index(int i) { idx = i; }

	double value();
	void value(double x);

	void calculate();

	void outputGrad(double target);
	void hiddenGrad();

	void update();

	void load(std::vector<double> _weight)
	{
		for (int i = 0; i < _weight.size(); ++i)
		{
			weight.push_back(_weight[i]);
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const neuron& n)
	{
		for (int i = 0; i < n.weight.size(); ++i)
		{
			out << n.weight[i] << " ";
		}

		return out;
	}
};



#endif 
