//Simple functions
#include <vector>

typedef std::vector<std::vector<double>> set;
typedef std::vector<double> sline;

set generate_xor(int n)
{
	set res;

	int i = 0;
	while (i++ < n)
	{
		int a = rand() % 2;
		int b = rand() % 2;

		sline input;
		input.push_back(a);
		input.push_back(b);

		sline output;
		output.push_back(a ^ b);

		res.push_back(input);
		res.push_back(output);
	}

	return res;
}

set generate_or(int n)
{
	set res;

	int i = 0;
	while (i++ < n)
	{
		int a = rand() % 2;
		int b = rand() % 2;

		sline input;
		input.push_back(a);
		input.push_back(b);

		sline output;
		output.push_back(a | b);

		res.push_back(input);
		res.push_back(output);
	}

	return res;
}

set generate_and(int n)
{
	set res;

	int i = 0;
	while (i++ < n)
	{
		int a = rand() % 2;
		int b = rand() % 2;

		sline input;
		input.push_back(a);
		input.push_back(b);

		sline output;
		output.push_back(a & b);

		res.push_back(input);
		res.push_back(output);
	}

	return res;
}

void train()
{
	//Simple topology

	srand(time(NULL));
	std::ofstream log;
	log.open("log.neuro");

	int a[3] = { 2, 3, 1 };
	network n(std::vector<int>(a, a + 3));

	std::cout << "Generating...";
	set train = generate_xor(100000);
	std::cout << "Learning...";
	for (int i = 0; i < train.size() / 2; i += 2)
	{
		log << "input:";
		for (int j = 0; j < train[i].size(); j++)
			log << " " << train[i][j];

		n.feed(train[i]);

		log << "\noutput:";
		for (int j = 0; j < train[i + 1].size(); j++)
			log << " " << train[i + 1][j];

		sline res = n.run();
		log << "\nresult:";
		for (int j = 0; j < res.size(); j++)
			log << " " << res[j];

		n.correct(train[i + 1]);
		log << "\navg: " << n.getAvgError();
		log << "\n----\n";
	}

	std::cout << "\nDone with " << n.getAvgError() << " error";
	n.store("xor.nconf");
	log.close();
	std::getchar();
}

