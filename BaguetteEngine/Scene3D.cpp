#include "Scene3D.hpp"

Scene3D::Scene3D(void)
{
	SceneNode *node = ensureDrawableExistance(0);

	lightShader_.load();
}

Scene3D::~Scene3D(void)
{
}

void Scene3D::update(float dt)
{
	AScene::update(dt);
	cc_.update(dt);
}

void Scene3D::render(ARenderer & renderer)
{
	if (lights_.size() > 0)
		lightShader_.setLights(&lights_);
	else
		lightShader_.setLights(nullptr);
	cc_.render(renderer, graph_, lightShader_);
}

void Scene3D::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos, bool save)
{
	AScene::setDrawablePosition(drawableId, pos, save);

	SceneNode *node = ensureDrawableExistance(drawableId);
	if (node) {
		cc_.setTarget(node->getDrawable()->getPosition());
	}
}

const Identifiable & Scene3D::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	ensureDrawableExistance(parent);
	SceneNode::Ptr node = nullptr;

	if (type == "sphere")
		node = SceneGraph::CreateSceneNodeFromGenerator<SphereGenerator>();
	else if (type == "portails") {
		node = SceneGraph::CreateSceneNodeFromGenerator<PlaneGenerator>();
		SceneNode::Ptr nodeDst = SceneGraph::CreateSceneNodeFromGenerator<PlaneGenerator>();
		cc_.createPortail(node, nodeDst);
		graph_.attachTo(std::move(nodeDst), parent);
	}
	else if (type == "light")
	{
		Light::Ptr light = nullptr;
		node = SceneGraph::CreateSceneLight<>(light);
		lights_.push_back(light);
	}
	else if (type == "directionalLight")
	{
		Light::Ptr light = nullptr;
		node = SceneGraph::CreateSceneLight<>(light);
		light->setLightType(Light::LightType::directional);
		//light->setLightModel(Light::LightMode);
		lights_.push_back(light);
	}
	else if (type == "spotLight")
	{
		Light::Ptr light = nullptr;
		node = SceneGraph::CreateSceneLight<>(light);
		light->setLightType(Light::LightType::spotlight);
		lights_.push_back(light);
	}
	else if (type == "ponctualLight")
	{
		Light::Ptr light = nullptr;
		node = SceneGraph::CreateSceneLight<>(light);
		light->setLightType(Light::LightType::ponctual);
		lights_.push_back(light);
	}
	else if (type == "plane")
		node = SceneGraph::CreateSceneNodeFromGenerator<PlaneGenerator>();
	else if (type == "cube")
		node = SceneGraph::CreateSceneNodeFromGenerator<CubeGenerator>();
	else if (type == "cone")
		node = SceneGraph::CreateSceneNodeFromGenerator<ConeGenerator>();
	else if (type.find("/") != std::string::npos
				|| type.find("\\") != std::string::npos
				|| type.find(".") != std::string::npos)
		node = SceneGraph::CreateSceneNodeFromGenerator<Model3DGenerator>(type);
	else
		std::cerr << type << " not found !" << std::endl;
	try {
		const Identifiable & id = graph_.attachTo(std::move(node), parent);
		historic_.pushTransformation(std::make_pair(id, ofMatrix4x4::newIdentityMatrix()));
		return id;
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}

std::string Scene3D::getName(void) const
{
	return "Editeur 3D";
}

int Scene3D::getNbDimensions(void) const
{
	return 3;
}

void Scene3D::setFocusedDrawable(const Identifiable & drawableId)
{
	AScene::setFocusedDrawable(drawableId);

	SceneNode *node = ensureDrawableExistance(drawableId);
	if (node) {
		cc_.setTarget(node->getDrawable()->getPosition());
	}
}

CameraController & Scene3D::getCameraController(void)
{
	return cc_;
}