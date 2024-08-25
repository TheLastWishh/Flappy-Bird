#include "flappy.hpp"

int main() {
	std::srand(time(0));
	FlappyBird flappy;
	flappy.run();
	return 0;
}