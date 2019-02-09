#pragma once

#include "COG/Core.h"
#include "COG/Utils/Vec3d.h"
#include "Model.h"
#include "Rendering/Shader.h"

/*#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"	  */

namespace COG {

	class Game_Object {

		private:
		std::shared_ptr<Model> model;
		std::shared_ptr<Shader>	shader;

		Vec3d move_vector = Vec3d();
		protected:
		Vec3d pos = Vec3d();
		Vec3d scale = Vec3d(1);

		float rads = 0;
		Vec3d axis = {0,0,1};

		public:
		COG_API Game_Object() noexcept {}
		//Use the names
		COG_API Game_Object(const std::string& model, const std::string& shader);

		COG_API virtual ~Game_Object() {
			model.~shared_ptr();
			shader.~shared_ptr();
		}

		COG_API inline Vec3d get_position() const noexcept { return pos; }
		COG_API inline Vec3d get_scale() const noexcept { return scale; }
		COG_API inline std::pair<float, Vec3d> get_rotation() const noexcept {
			return std::make_pair(rads, axis);
		}

		COG_API inline void set_position(const Vec3d& loc) noexcept { pos = loc; }
		COG_API inline void set_scale(const Vec3d& axes) noexcept { scale = axes; }
		//Use Radians for the first parameter
		COG_API inline void set_rotation(float rads, const Vec3d& axis)	{
			this->rads = rads;
			this->axis = axis;
		}

		COG_API inline void move(const Vec3d& amt) noexcept { move_vector += amt; }
		COG_API inline void halt() noexcept { move_vector = {0}; }
		COG_API virtual void update(double delta);
	};
}