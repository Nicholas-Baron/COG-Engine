#include "precomp/precomp.h"
#include "Game_Object.h"
#include "Game_Object_Internal.h"
#include "RenderResourceManager.h"

#include "Rendering/RenderUtil.h"
#include "COG/COG_Engine.h"

#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

COG::Game_Object::Game_Object(const std::string & model_name, const std::string & shader)
	: move_vector(0), pos(0), axis(0, 0, 1), rads(0) {

	model = RenderResourceManager::get_model(model_name);
	set_scale(Vec3d(model->scale_factor()));

	this->shader = RenderResourceManager::get_shader(shader);
}
namespace COG {
	inline void set_mvp(std::shared_ptr<Shader> shader, const Game_Object* go) {

		//projection * translation
		const auto vpmat = [ ]() -> glm::mat4 {

			auto cast = [ ](double x) { return static_cast<float>(x); };

			auto proj_info = COG_Engine::get_proj_info();

			//using namespace glm::gtc::matrix_transform;
			auto proj = (proj_info.first == ProjectionMode::ORTHO)
				? glm::ortho(cast(proj_info.second[0]), cast(proj_info.second[1]),
							 cast(proj_info.second[2]), cast(proj_info.second[3]), 0.1f, 100.0f)
				: glm::perspective(cast(proj_info.second[0]), cast(proj_info.second[1]),
								   cast(proj_info.second[2]), cast(proj_info.second[3]));

			auto camera = COG_Engine::get_camera_pos();
			auto view = glm::translate(vector_cast(camera));
			return proj * view;
		}();

		auto model = COG::model_mat(go);
		auto matrix = vpmat * model;

		static const auto zero_mat = glm::mat4() - glm::mat4();

		if(matrix == zero_mat) {
			if(vpmat == matrix) {
				warn_internal("VP Matrix is 0!");
			} else if(model == matrix) {
				warn_internal("Model Matrix is 0!");
			}
		}

		GLCALL(glUniformMatrix4fv(shader->uniform_loc("u_mvp"), 1, GL_FALSE, &matrix[0][0]));
	}
}
void COG::Game_Object::update(double delta) {

	constexpr double speed = 3.5;
	Vec3d will_move = move_vector.normalized() * speed * delta;

	if(move_vector.sqr_magnitude() >= speed && will_move.valid()) {
		move_vector -= will_move;
		pos += will_move;
	} else {
		move_vector = {0};
	}

	shader->use();
	if(shader->uses_mvp()) { set_mvp(shader, this); }
	model->draw();
}
