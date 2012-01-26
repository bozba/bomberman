#include "precomp.hpp"

class GameObject
{
public:
	GameObject(CL_ResourceManager *resources,CL_GraphicContext *gc) :
		resources(resources),gc(gc){}
	virtual void draw(int pos_x,int pos_y,CL_GraphicContext *gc){}
	void set_pos(float x,float y);
	
protected:
	CL_ResourceManager *resources;
	CL_GraphicContext *gc;
	float pos_x;
	float pos_y;
};
