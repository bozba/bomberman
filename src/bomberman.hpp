#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

class Bomberman{

private:
	bool is_running;

public:
	Bomberman();
	int start(const std::vector<CL_String> &args);
};

#endif //BOMBERMAN_HPP