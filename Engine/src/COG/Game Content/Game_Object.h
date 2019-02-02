#pragma once

#include "COG/Core.h"
#include "COG/Utils/Vec3d.h"

#include "glm/mat4x4.hpp"

namespace COG {
	class COG_API Game_Object {

		private:
		Vec3d pos = Vec3d();
		Vec3d scale = Vec3d(1);

		glm::mat4 rotation;

		public:
		Game_Object();
		virtual ~Game_Object() {}



	};
}