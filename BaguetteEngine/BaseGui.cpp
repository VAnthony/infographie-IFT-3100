#include "BaseGui.hpp"

BaseGui::BaseGui(SceneController &scene) : scene_(scene), editMenu_(scene), mainMenu_(scene, editMenu_)
{
}


BaseGui::~BaseGui()
{
}

void BaseGui::draw()
{
	ofDisableDepthTest();
	editMenu_.draw();
	mainMenu_.draw();
	ofEnableDepthTest();
}

void BaseGui::setup()
{
	ofEnableAlphaBlending();
	mainMenu_.setup();
	editMenu_.setup();
}

void BaseGui::focus(int id)
{
	std::cout << "L'user veut le focus" << std::endl;
}
