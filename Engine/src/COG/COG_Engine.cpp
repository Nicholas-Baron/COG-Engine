#include "precomp/precomp.h"

#include "COG_Engine.h"
#include "Log.h"
#include "Platform/Windows/WindowsWindow.h"

namespace COG {
	COG_Engine::COG_Engine(const WindowDetails& details) {
		Log::init(details.title);

#ifdef COG_PLATFORM_WINDOWS
	window = create_window<WindowsWindow>(details);
#endif
	}


	COG_Engine::~COG_Engine() {}
}