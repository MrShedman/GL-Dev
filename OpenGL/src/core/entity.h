#pragma once

#include <vector>
#include "transform.h"
#include "window\Event.h"
#include "math\Quaternion.h"
#include "math\Vector.h"

class Camera;
class CoreEngine;
class EntityComponent;
class Shader;
class RenderingEngine;

class Entity
{
public:
	Entity(const Vector3f& pos = Vector3f(0,0,0), const Quaternion& rot = Quaternion(0,0,0,1), float scale = 1.0f) : 
		m_transform(pos, rot, scale),
		m_coreEngine(0) {}
		
	static int count;
	static inline void out() {} //std::cout << "rendered: " << count << std::endl; count = 0; }

	virtual ~Entity();
	
	Entity* AddChild(Entity* child);
	Entity* AddComponent(EntityComponent* component);
	
	void ProcessInputAll(const Event& event, float delta);
	void UpdateAll(float delta);
	void RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;
	
	std::vector<Entity*> GetAllAttached();
	
	inline const Transform& GetTransform() const { return m_transform; }
	inline Transform* GetTransform() { return &m_transform; }
	void SetEngine(CoreEngine* engine);
protected:
private:
	std::vector<Entity*>          m_children;
	std::vector<EntityComponent*> m_components;
	Transform                     m_transform;
	CoreEngine*                   m_coreEngine;

	void ProcessInput(const Event& event, float delta);
	void Update(float delta);
	void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const;
	
	Entity(const Entity& other) {}
	void operator=(const Entity& other) {}
};