#include <COG.h>

class TestLayer : public COG::Layer{
	
	COG::Game_Object teapot;

	public:
	TestLayer() : Layer("Test Layer") {}

	virtual ~TestLayer() override {
		info("Cleaned the test layer");
	}

	virtual void on_detach() override {
		info("Detached the test layer");
		teapot.~Game_Object();
		COG::RenderResourceManager::unload_model("teapot");
		COG::RenderResourceManager::unload_shader("basic");
	}

	virtual void on_attach() override {
		info("Attached the test layer");
		COG::RenderResourceManager::load_model("res/models/teapot.obj", "teapot");
		COG::RenderResourceManager::load_shader("res/shaders/basic.shader", "basic");
	
		teapot = COG::Game_Object("teapot", "basic");
	}

	virtual void on_update(double delta) override{	
		teapot.update(delta);
	}

	virtual void on_event(COG::Event& e) override {
		if(e.type() == COG::EventType::MousePress) {
			//Mouse press
			const auto& mp = COG::event_cast<COG::MouseButtonPressedEvent>(e);
			info(mp.mouse_button());
			e.handled = true;
		} else if(e.type() == COG::EventType::KeyTyped) {
			//Key Press
			const auto& kp = COG::event_cast<COG::KeyTypedEvent>(e);
			e.handled = true;
			info(kp.keycode());
		}
	}
};

int main() {

	COG::COG_Engine cog;

	cog.layer_stack().push_layer(std::make_shared<TestLayer>());

	info("Engine ready");

	cog.run();

}