#include "../headers/neuro.hpp";

double neuron::a = 0.5;
double neuron::e = 0.15;

double neuron::activation(double x)
{
	return tanh(x);
}

double neuron::derivative(double x)
{
	return 1.0 - x * x;
}

neuron::neuron()
{
	val = (rand() / (RAND_MAX / 2)) - 1;
}

neuron::neuron(layer& _prev)
{
	prev = &_prev;
	int len = prev->size();

	for (int i = 0; i < len; ++i)
	{
		weight.push_back((double)rand() / RAND_MAX);
		delta.push_back(0);
	}

	val = ((double)rand() / (RAND_MAX / 2)) - 1;
}

void neuron::after(layer& _next)
{
	next = &_next;
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
	for (int i = 0; i < prev->size(); ++i)
	{
		sum += (*(prev))[i].value() * weight[i];
	}

	val = neuron::activation(sum);
}

void neuron::outputGrad(double target)
{
	grad = (target - val) * neuron::derivative(val);
}

void neuron::hiddenGrad()
{
	double sum = 0.0;

	int len = (next->size() - 1);
	for (int i = 0; i< len; ++i)
	{
		sum += (*next)[i].weight[idx] * (*next)[i].grad;
	}

	grad = sum * neuron::derivative(val);
}

void neuron::update()
{
	for (int i = 0; i < prev->size(); ++i)
	{
		delta[i] = neuron::e * (*prev)[i].val * grad + neuron::a * delta[i];
		weight[i] += delta[i];
	}
}


