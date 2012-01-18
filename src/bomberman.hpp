#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "precomp.hpp"

class Bomberman{

private:
	bool is_running;
	CL_GraphicContext *gc;
	CL_DisplayWindow *window;
	CL_ResourceManager *recourses;

public:
	Bomberman();
	int start(const std::vector<CL_String> &args);
	void on_quit()	{is_running=false;}
};

#endif //BOMBERMAN_HPP
