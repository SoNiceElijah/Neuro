#include "../headers/network.hpp";
#include <time.h>

#include "../headers/generator.hpp";

int main(int argc, char** argv)
{

	train();

	/* 

	coming soon...
	load still not work

	int topology[3] = {2, 3, 1};
	network net = network::load("xor.nconf");

	double input[] = { 0.0, 0.0 };
	net.feed(std::vector<double>(input, input+2));

	std::cout << net.run()[0];	
	std::getchar();
	

	*/
	return 0;
}