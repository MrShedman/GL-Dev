
#include "entity.h"
#include "entityComponent.h"
#include "coreEngine.h"

int Entity::count = 0;

Entity::~Entity()
{
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		if(m_components[i])
		{	
			delete m_components[i];
		}
	}
	
	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		if(m_children[i]) 
		{
			delete m_children[i];
		}
	}
}

Entity* Entity::AddChild(Entity* child)
{
	m_children.push_back(child); 
	child->GetTransform()->SetParent(&m_transform);
	child->SetEngine(m_coreEngine);
	return this;
}

Entity* Entity::AddComponent(EntityComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void Entity::ProcessInputAll(const Event& event, float delta)
{
	ProcessInput(event, delta);

	for (unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->ProcessInputAll(event, delta);
	}
}

void Entity::UpdateAll(float delta)
{
	Update(delta);

	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->UpdateAll(delta);
	}
}

void Entity::RenderAll(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
	Render(shader, renderingEngine, camera);

	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		m_children[i]->RenderAll(shader, renderingEngine, camera);
	}
}

void Entity::ProcessInput(const Event& event, float delta)
{
	m_transform.Update();

	for (unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->ProcessInput(event, delta);
	}
}

void Entity::Update(float delta)
{
	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Update(delta);
	}
}

void Entity::Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
{
	Frustum f(camera.GetViewProjection());

	for(unsigned int i = 0; i < m_components.size(); i++)
	{
		BoundingSphere sphere(m_components[i]->GetTransform()->GetTransformedPos(), 1.f);

		if (f.cubeIntersection(sphere))
		{
			m_components[i]->Render(shader, renderingEngine, camera);
			count++;
		}

		//m_components[i]->Render(shader, renderingEngine, camera);
	}
}

void Entity::SetEngine(CoreEngine* engine)
{
	if(m_coreEngine != engine)
	{
		m_coreEngine = engine;
		
		for(unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->AddToEngine(engine);
		}

		for(unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->SetEngine(engine);
		}
	}
}

std::vector<Entity*> Entity::GetAllAttached()
{
	std::vector<Entity*> result;
	
	for(unsigned int i = 0; i < m_children.size(); i++)
	{
		std::vector<Entity*> childObjects = m_children[i]->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}
	
	result.push_back(this);
	return result;
}