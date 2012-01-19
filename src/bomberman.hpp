#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "precomp.hpp"
#include "gameobject.hpp"

class Bomberman{

private:
	bool is_running;
	CL_DisplayWindow window;
	CL_ResourceManager resources;

public:
	Bomberman();
	~Bomberman();
	int start(const std::vector<CL_String> &args);
	void on_quit()	{is_running=false;}
};

#endif //BOMBERMAN_HPP
