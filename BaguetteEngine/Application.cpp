#include "Application.hpp"
#include "Image.h"

Application::Application(void) : gui_(scene_)
{
	ofSetVerticalSync(true);
}

Application::~Application(void)
{
}

void Application::setup(void)
{
	gui_.setup();
}

void Application::update(void)
{
	double dt = timer_.restart();

	scene_.update(dt);
}

void Application::draw(void)
{
	scene_.render(window_);

	/*Image img("loutre.jpg");
	img.Draw(0, 0, 300, 300);
	img.DrawPartOfImage(400, 400, 200, 200, 0, 0);*/

	gui_.draw();
	//img.Export("screenshot.jpg");
}

void Application::keyPressed(int key)
{
}

void Application::keyReleased(int key)
{
	switch (key)
	{
	case 'z':
		scene_.undo();
		break;
	case 'y':
		scene_.redo();
		break;
	case 'm':
		scene_.swapMode();
		break;
	default:
		break;
	}
}

void Application::mouseMoved(int x, int y )
{
}

void Application::mouseDragged(int x, int y, int button)
{
}

void Application::mousePressed(int x, int y, int button)
{
	/* int id;

	if ((id = scene_.selected(x, y)) > 0)
		gui_.focus(0); */
}

void Application::mouseReleased(int x, int y, int button)
{
}

void Application::mouseEntered(int x, int y)
{
}

void Application::mouseExited(int x, int y)
{
}

void Application::windowResized(int w, int h)
{
}

void Application::gotMessage(ofMessage msg)
{
}

void Application::dragEvent(ofDragInfo dragInfo)
{ 
}
