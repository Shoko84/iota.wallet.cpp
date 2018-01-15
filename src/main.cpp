#include <iostream>
#include "Launcher.hpp"

int main(int ac, char **av)
{
	try {
		nx::Launcher launcher(ac, av);
		return launcher.run();
	} catch (...) {
		std::cerr << "Unexpected error" << std::endl;
		return EXIT_FAILURE;
	}
}
