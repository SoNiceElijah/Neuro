#include "../headers/network.hpp";

network::network(std::vector<int> t)
{
	int n = t.size();
	if (n < 2)
		throw std::exception("net with 1 layer or less != network");

	for (int i = 0; i < n; ++i)
	{
		if (t[i] == 0)
			throw std::exception("zero size layer? R u f*cking kiddin me?");

		layers.push_back(layer());
	}

	int k = 0;
	for (; k < t[0] + 1; ++k)
	{
		layers[0].push_back(neuron());
	}

	layers[0][k - 1].value(1.0);

	for (int i = 1; i < n; ++i)
	{
		int j = 0;
		for (; j < t[i] + 1; ++j)
		{
			layers[i].push_back(neuron(layers[i - 1]));
		}

		layers[i][j - 1].value(1.0);
	}

	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = 0; j < t[i]; ++j)
		{
			layers[i][j].after(layers[i + 1]);
		}
	}
}

void network::feed(std::vector<double> input)
{
	if (input.size() + 1 != layers[0].size())
		throw std::exception("wrong input size");

	for (int i = 0; i < input.size(); ++i)
	{
		layers[0][i].value(input[i]);
	}
}

std::vector<double> network::run()
{
	std::vector<double> result;

	int i = 1;
	for (; i < layers.size(); ++i)
	{
		for (int j = 0; j < layers[i].size() - 1; ++j)
		{
			layers[i][j].calculate();
		}
	}

	--i;
	for (int j = 0; j < layers[i].size() - 1; ++j)
	{
		result.push_back(layers[i][j].value());
	}

	return result;
}