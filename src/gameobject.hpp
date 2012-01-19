#include "precomp.hpp"

class Bomberman;

class GameObject
{
public:
	GameObject(Bomberman *bomberman)	{this->bomberman=bomberman;}
	virtual void draw(CL_GraphicContext *gc){}
	
protected:
	Bomberman *bomberman;
};
