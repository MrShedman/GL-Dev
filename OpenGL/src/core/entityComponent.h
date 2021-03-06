#pragma once

#include "transform.h"
#include "entity.h"

class RenderingEngine;
class Shader;

class EntityComponent
{
public:
	EntityComponent() :
		m_parent(0) {}
	virtual ~EntityComponent() {}

	virtual void ProcessInput(const Event& event, float delta) {}
	virtual void Update(float delta) {}
	virtual void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const {}
	
	virtual void AddToEngine(CoreEngine* engine) const { }
	
	inline Transform* GetTransform()             { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return *m_parent->GetTransform(); }
	
	virtual void SetParent(Entity* parent) { m_parent = parent; }
private:
	Entity* m_parent;
	
	EntityComponent(const EntityComponent& other) {}
	void operator=(const EntityComponent& other) {}
};