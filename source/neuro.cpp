#include "../headers/neuro.hpp";

double neuron::a = 0.5;
double neuron::e = 0.15;

double neuron::activation(double x)
{
	return (2 / M_PI) * atan(x);
}

double neuron::derivative(double x)
{
	return (2 / M_PI) * (1 / (x * x + 1));
}

neuron::neuron()
{
	val = (rand() / (RAND_MAX / 2)) - 1;
}

neuron::neuron(layer& _prev)
{
	prev = _prev;
	int len = prev.size();

	for (int i = 0; i < len; ++i)
	{
		weight.push_back((double)rand() / RAND_MAX);
		delta.push_back(0);
	}

	val = ((double)rand() / (RAND_MAX / 2)) - 1;
}

void neuron::after(layer& _next)
{
	next = _next;
}

void neuron::value(double v)
{
	val = v;
}

double neuron::value()
{
	return val;
}

void neuron::calculate()
{
	double sum = 0.0;
	for (int i = 0; i < prev.size() - 1; ++i)
	{
		sum += prev[i].value() * weight[i];
	}

	val = neuron::activation(sum);
}