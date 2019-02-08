#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"
#include "Layering/LayerStack.h"
#include "Utils/Vec3d.h"

namespace COG{
	
	inline auto time_now() noexcept { return std::chrono::high_resolution_clock::now(); }

	enum struct ProjectionMode : unsigned short {
		ORTHO, PERSPECTIVE
	};

	class COG_Engine {
		
		private:
		
		static COG_Engine* instance;
		std::chrono::high_resolution_clock::time_point start;
		bool running;

		LayerStack layers;

		//Visual stuff

		std::unique_ptr<Window> window;
		std::array<float, 4> clear_color;
		unsigned last_second_frames;
		
		//TODO: Extract to camera class
		Vec3d camera_pos = Vec3d();
		ProjectionMode proj_mode;
		std::array<double, 4> proj_data;

		public:
		COG_API COG_Engine(const WindowDetails& details = WindowDetails());
		
		inline ~COG_Engine() {
			window->destroy();
		}

		static Vec3d get_camera_pos(){ return instance->camera_pos; }

		static std::pair<ProjectionMode, std::array<double, 4>> get_proj_info(){
			return std::make_pair(instance->proj_mode, instance->proj_data);
		}

		COG_API void set_camera_pos(const Vec3d& pos){
			camera_pos = pos;
		}

		COG_API void move_camera(const Vec3d& move){
			camera_pos += move;
		}

		COG_API Vec3d get_camera() const noexcept { return camera_pos; }
		COG_API ProjectionMode projection_mode() const noexcept { return proj_mode; }
		COG_API inline double aspect_ratio(){ return window->aspect_ratio(); }

		COG_API inline unsigned frame_count() const noexcept { 
			return last_second_frames;
		}
		
		COG_API inline double time() const noexcept { 
			using namespace std::chrono;
			using milliD = duration<double, std::milli>;
			return duration_cast<milliD>(time_now() - start).count();
		}

		COG_API inline void set_projection_ortho(double left, double right, double bottom, double top){
			proj_data = {left, right, bottom, top};
			proj_mode = ProjectionMode::ORTHO;
		}

		COG_API inline void set_ortho_from_center(double height){
			const auto half = height / 2;
			set_projection_ortho(-half * window->aspect_ratio(), half * window->aspect_ratio(), -half, half);
			camera_pos = Vec3d(0,0,-5);
		}

		COG_API inline void set_ortho_from_top_left(double height) {
			set_projection_ortho(0, height * window->aspect_ratio(), -height, 0);
			camera_pos = Vec3d(height / 2, height / 2, 0);
		}

		COG_API inline void set_ortho_from_bottom_left(double height) {
			set_projection_ortho(0, height * window->aspect_ratio(), 0, height);
			camera_pos = Vec3d(height / 2, -height / 2, 0);
		}

		COG_API inline void set_projection_perspective(double fov, double aspect, double znear = 0.1, double zfar = 100){
			proj_data = {fov, aspect, znear, zfar};
			proj_mode = ProjectionMode::PERSPECTIVE;
		}

		COG_API void set_clear_color(float red, float green, float blue, float alpha = 1) noexcept{
			clear_color = {red, green, blue, alpha};
		}

		COG_API void run();

		COG_API inline LayerStack& layer_stack() noexcept {
			return layers;
		}

		inline bool on_window_close(WindowCloseEvent& e);
		void on_event(Event& e);
	};

}