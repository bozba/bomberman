#include "bomberman.hpp"

Bomberman::Bomberman() : 
	is_running(true),
	window("Bomberman", 1024, 768, false, true),
	resources("resources.xml")
	{}

Bomberman::~Bomberman(){}

int Bomberman::start(const std::vector<CL_String> &args)
	{
		CL_GraphicContext gc=window.get_gc();
		//Connect the on_quit() function to the main windows close button.
		CL_Slot slot_quit = window.sig_window_close().connect(this, &Bomberman::on_quit);
		
		//main loop
		while(is_running)
			{	
				window.flip(1);
				CL_KeepAlive::process();
				CL_System::sleep(GAME_TICK);
			}
			
		return 0;
	}
