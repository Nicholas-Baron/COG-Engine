#pragma once

#include "Core.h"

namespace COG {

	constexpr unsigned short major_version = 0;
	constexpr unsigned short minor_version = 2;
	constexpr unsigned short revision = 0;

	constexpr unsigned release_code = 190209;

	static const std::string release_name = "Ogre";

	COG_API inline std::string version_print(){
		std::stringstream stream;
		stream << major_version << '.' << minor_version; 
		
		if constexpr (revision != 0) { 
			stream << '.' << revision;
		}
		
		stream << '_' << release_code << " codenamed " << release_name;
		return stream.str();
	}
}