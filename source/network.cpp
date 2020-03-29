#include "../headers/network.hpp";

double network::smooth = 100.0;

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
		layers[0][k].index(k);
	}

	layers[0][k - 1].value(1.0);

	for (int i = 1; i < n; ++i)
	{
		int j = 0;
		for (; j < t[i] + 1; ++j)
		{
			layers[i].push_back(neuron(layers[i - 1]));
			layers[i][j].index(j);
		}

		layers[i][j - 1].value(1.0);
	}

	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = 0; j < t[i] + 1; ++j)
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

void network::correct(std::vector<double> target)
{
	//backpropagation

	error = 0.0;

	int n = layers.size() - 1;
	for (int i = 0; i < layers[n].size() - 1; ++i)
	{
		double d = target[i] - layers[n][i].value();
		error += d * d;
	}

	error = (error / (layers[n].size() - 1));
	error = sqrt(error);

	avgError = (avgError * smooth + error) / (smooth + 1.0);

	for (int i = 0; i < layers[n].size() - 1; ++i)
		layers[n][i].outputGrad(target[i]);

	for (int i = layers.size() - 2; i > 0; --i)
	{
		for (int j = 0; j < layers[i].size(); ++j)
		{
			layers[i][j].hiddenGrad();
		}
	}

	for (int i = layers.size() - 1; i > 0; --i)
	{
		for (int j = 0; j < layers[i].size() - 1; ++j)
		{
			layers[i][j].update();
		}
	}
}

void network::store(const char* name)
{
	std::ofstream file;
	file.open(name);
	
	for (int i = 0; i < layers.size(); ++i)
	{
		file << layers[i].size() - 1 << " ";
	}

	file << "\n";

	for (int i = 0; i < layers.size(); ++i)
	{
		for (int j = 0; j < layers[i].size() - 1; ++j)
		{
			file << layers[i][j];
			file << '\n';
		}
	}

	file.close();
}

network network::load(const char* name)
{

	std::ifstream file;
	file.open(name);

	std::vector<int> topology;

	int first = 0;
	while(first == 0)
	{
		std::string line;
		std::getline(file, line);
		std::stringstream stream(line);

		double number;
		while (stream >> number)
			topology.push_back(number);

		first++;
	}

	network net(topology);
	for (int i = 0; i < net.layers.size(); ++i)
	{
		for (int j = 0; j < net.layers[i].size() - 1; ++j)
		{
			std::string line;
			std::getline(file, line);
			std::stringstream stream(line);

			if (line == "" && !file.eof())
			{
				continue;
			}

			std::vector<double> buffer;

			double number;
			while (stream >> number)
				buffer.push_back(number);

			net.layers[i][j].load(buffer);
		}
	}

	return net;
}
	