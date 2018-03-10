#pragma once

#include <vector>
#include <sstream>
#include <memory>
#include <functional>

#include "Image.h" 
#include "CacheManager.hpp"

#include "Identifiable.hpp"
#include "SceneNode.hpp"

#include "AScene.hpp"
#include "Scene2D.hpp"
#include "Scene3D.hpp"

class ARenderer;

class SceneController
{
public:
	enum class Mode : int {
		Mode3D = 0,
		Mode2D = 1
	};

public:
	SceneController(void);
	~SceneController(void);

	void swapMode(void);
	void setOnSceneChanged(std::function<void(int)> callback);
	void setOnGraphSceneChanged(std::function<void(void)> callback);
	void setOnFocusChanged(std::function<void(const Identifiable &)> callback);
	void setOnImageImported(std::function<void(void)> callback);

	void update(float dt);
	void render(ARenderer & renderer);

	const Identifiable & instanciateDrawable(const std::string & type, const Identifiable & parent = Identifiable());
	void removeDrawable(const Identifiable & drawableId);

	void setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos);
	void setDrawableRotation(const Identifiable & drawableId, const ofVec3f & orientation);
	void setDrawableScale(const Identifiable & drawableId, const ofVec3f & scale);
	void setDrawableColor(const Identifiable & drawableId, const ofColor & color);

	void graphContent(SceneNode::TreeData & data) const;

	void undo(void);
	void redo(void);

	void setFocusedDrawable(const Identifiable & drawableId);
	const Identifiable * getFocusedDrawable(void) const;

	void AddImage(const Image & img);
	void refreshImage();
	const CacheManager<string, ofImage> & getCache() const;
	SceneNode * ensureDrawableExistance(const Identifiable & drawableId);

private:
	// TriangleVector triangle_;
	std::vector<std::unique_ptr<AScene> > scenes_;
	std::vector<std::unique_ptr<AScene> >::const_iterator currentScene_;
	std::function<void(int)> onSceneChanged_;
	std::function<void(void)> onGraphSceneChanged_;
	std::function<void(const Identifiable &)> onFocusChanged_;
	std::function<void(void)> onImageImported_;

	CacheManager<string, ofImage> cacheManager;
};