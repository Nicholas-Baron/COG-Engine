#pragma once

#include "Core.h"

namespace COG {

	constexpr unsigned short major_version = 0;
	constexpr unsigned short minor_version = 1;
	constexpr unsigned short revision = 0;

	constexpr unsigned release_code = 190126;

	const std::string release_name = "First";

	COG_API inline std::string version_print(){
		std::stringstream stream;
		stream << major_version << '.' << minor_version <<	'.' << revision 
		<< '_' << release_code << " codenamed " << release_name;
		return stream.str();
	}
}