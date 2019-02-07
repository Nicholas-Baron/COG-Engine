#include "precomp/precomp.h"
#include "Game_Object.h"
#include "Game_Object_Internal.h"
#include "RenderResourceManager.h"

#include "Rendering/RenderUtil.h"
#include "COG/COG_Engine.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

COG::Game_Object::Game_Object(const std::string & model_name, const std::string & shader) {

	model = RenderResourceManager::get_model(model_name);
	set_scale(Vec3d(model->scale_factor()));

	this->shader = RenderResourceManager::get_shader(shader);
}
namespace COG {
	inline void set_mvp(std::shared_ptr<Shader> shader, const Game_Object* go) {
		auto cast = [] (double x){ return static_cast<float>(x); };
		
		//projection * translation
		const auto vpmat = [cast]() -> glm::mat4 {
			auto proj_info = COG_Engine::get_proj_info();
			auto proj = (proj_info.first == ProjectionMode::ORTHO)
				? glm::ortho(cast(proj_info.second[0]), cast(proj_info.second[1]),
							 cast(proj_info.second[2]), cast(proj_info.second[3]))
				: glm::perspective(cast(proj_info.second[0]), cast(proj_info.second[1]),
								   cast(proj_info.second[2]), cast(proj_info.second[3]));

			auto camera = COG_Engine::get_camera_pos();
			auto translate = glm::translate(vector_cast(camera));
			return proj * translate;
		}();

		auto model = COG::model_mat(go);
		auto matrix = vpmat * model;
		/*for(int i = 0; i < model.length(); i++) {
			for(int j = 0; j < model[i].length(); j++) {
				debug_internal(model[i][j]);
			}
		}  */
		GLCALL(glUniformMatrix4fv(shader->uniform_loc("u_mvp"), 1, GL_FALSE, &matrix[0][0]));
	}
}
void COG::Game_Object::update(double delta) {
	//shader->use();
	if(shader->uses_mvp()) { set_mvp(shader, this); }
	model->draw();
}
