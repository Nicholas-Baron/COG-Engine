#include <COG.h>

class TestLayer : public COG::Layer{

	public:
	TestLayer() : Layer("Test Layer") {}

	virtual ~TestLayer() override {
		info("Cleaned the test layer");
	}

	virtual void detach() override {
		info("Detached the test layer");
	}

	virtual void attach() override {
		info("Attached the test layer");
	}
};

int main() {

	COG::COG_Engine cog;

	cog.layer_stack().push_layer(std::make_shared<TestLayer>());

	info("Engine ready");

	cog.run();

}