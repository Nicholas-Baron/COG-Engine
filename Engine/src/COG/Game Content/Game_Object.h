#pragma once

#include "COG/Core.h"
#include "COG/Utils/Vec3d.h"
#include "Model.h"
#include "Rendering/Shader.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace COG {

	inline glm::vec3 vector_cast(const Vec3d& data){
		return {data.x_val(), data.y_val(), data.z_val()};
	}

	class  Game_Object {

		private:
		Vec3d pos = Vec3d();
		Vec3d scale = Vec3d(1);

		glm::mat4 rotation;
		std::shared_ptr<Model> model;
		std::shared_ptr<Shader>	shader;

		public:
		COG_API Game_Object() noexcept {}
		//Use the names
		COG_API Game_Object(const std::string& model, const std::string& shader);

		COG_API virtual ~Game_Object() {}

		inline glm::mat4 translate_mat() const { 
			return glm::translate(glm::mat4(), vector_cast(pos));
		}
		inline glm::mat4 scale_mat() const { 
			return glm::scale(glm::mat4(), vector_cast(scale));
		}
		inline glm::mat4 rotation_mat() const noexcept { return rotation; }
		inline glm::mat4 model_mat() const noexcept { 
			return translate_mat() * rotation_mat() * scale_mat();
		}

		COG_API inline void set_position(const Vec3d& loc) noexcept { pos = loc; }
		COG_API inline void set_scale(const Vec3d& axes) noexcept { scale = axes; }
		COG_API inline void set_rotation(float rads, const Vec3d& axis)	{
			rotation = glm::rotate(glm::mat4(), rads, vector_cast(axis));
		}

		COG_API virtual void shader_settings(const glm::mat4& vpmat) const;
		COG_API virtual void update(double delta);
	};
}