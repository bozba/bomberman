#include "precomp.hpp"
#include "main.hpp"

// Choose the target renderer
//#define USE_OPENGL_2
//#define USE_OPENGL_1
#define USE_SOFTWARE_RENDERER

#ifdef USE_SOFTWARE_RENDERER
#include <ClanLib/swrender.h>
#endif

#ifdef USE_OPENGL_1
#include <ClanLib/gl1.h>
#endif

#ifdef USE_OPENGL_2
#include <ClanLib/gl.h>
#endif

int Program::main(const std::vector<CL_String> &args)
   {	
       try
       {
		// Initialize ClanLib base components
		CL_SetupCore setup_core;

		// Initialize the ClanLib display component
		CL_SetupDisplay setup_display;

		#ifdef USE_SOFTWARE_RENDERER
			CL_SetupSWRender setup_swrender;
		#endif

		#ifdef USE_OPENGL_1
			CL_SetupGL1 setup_gl1;
		#endif

		#ifdef USE_OPENGL_2
			CL_SetupGL setup_gl;
		#endif

           //PrimitivesExample example;
           //example.run();
       }
       catch(CL_Exception &exception)
       {
           // Create a console window for text-output if not available
           CL_ConsoleWindow console("Console", 80, 160);
           CL_Console::write_line("Error: " + exception.get_message_and_stack_trace());

           console.display_close_message();

           return -1;
       }

       return 0;
   }

// Instantiate CL_ClanApplication, informing it where the Program is located
CL_ClanApplication app(&Program::main);

