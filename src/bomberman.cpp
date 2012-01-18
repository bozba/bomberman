#include "bomberman.hpp"

Bomberman::Bomberman() : is_running(true){}

int Bomberman::start(const std::vector<CL_String> &args)
	{
		window=new CL_DisplayWindow("Bomberman", 800, 600, false, true);
		gc=&window->get_gc();
		CL_ResourceManager resources;
		CL_Slot slot_quit = window->sig_window_close().connect(this, &Bomberman::on_quit);
		
		// main loop
		while(is_running)
			{
				window->flip();
				CL_KeepAlive::process();
				CL_System::sleep(10);
			}
	}
