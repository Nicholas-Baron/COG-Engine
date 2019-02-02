#include "precomp/precomp.h"
#include "TextUtil.h"
namespace COG {
	bool loadTextFromFile(const std::string& location, std::vector<std::string>& data) {
		std::ifstream file(location.c_str());
		if(!file) {
			return false;
		}

		std::string current;

		while(getline(file, current)) {
			data.push_back(current);
		}

		file.close();
		return true;
	}

	std::string appendWithSeperator(const std::vector<std::string>& lines, const std::string & sep) {
		if(lines.size() == 1) {
			return lines[0];
		} else if(lines.size() == 0) {
			return "";
		}

		std::string toRet;

		for(size_t i = 0; i < lines.size(); i++) {
			toRet.append(lines[i]);

			if(i != lines.size() - 1) {
				toRet.append(sep);
			}
		}

		return toRet;
	}
}