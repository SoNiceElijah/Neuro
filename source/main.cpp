#include "../headers/network.hpp";

int main(int argc, char** argv)
{
	int a[3] = {2, 3, 1};
	network n(std::vector<int>(a, a + 3));

	double start[2] = { 1.0, 0.0 };
	n.feed(std::vector<double>(start, start + 2));

	std::vector<double> res = n.run();

	std::cout << "-- RESULT --\n";
	for (int i = 0; i < res.size(); ++i)
		std::cout << "output: " << res[i] << '\n';

	std::getchar();
	return 0;
}