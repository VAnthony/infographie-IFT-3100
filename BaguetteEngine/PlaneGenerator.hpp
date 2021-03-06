#pragma once

#include "IBasicMeshGenerator.hpp"
#include "PlanePrimitive.hpp"

class PlaneGenerator : IBasicMeshGenerator
{
public:
	PlaneGenerator();
	PlaneGenerator(const ofVec2f pos, const float width, const float height);

	virtual AMesh * operator()(void) const;
	virtual AMesh * generate() const;
	
	void setSize(const float width, const float height);
	void setPosition(const ofVec3f pos);

private:
	PlanePrimitive *plan_;
};