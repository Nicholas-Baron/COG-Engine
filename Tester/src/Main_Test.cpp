#include <COG.h>

#include <iostream>

int main() {
	using COG::COG_Engine;
	
	COG_Engine cog;

	COG::Log::Init("Tester");

	info("Engine ready");

	std::cin.get();

}