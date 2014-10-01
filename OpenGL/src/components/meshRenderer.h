#pragma once

#include "core/entityComponent.h"
#include "rendering/mesh.h"

class MeshRenderer : public EntityComponent
{
public:
	MeshRenderer(const Mesh& mesh, const Material& material) :
		m_mesh(mesh),
		m_material(material),
		polygonMode(false)
		
	{}

	virtual void ProcessInput(const Event& event, float delta)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::P)
			{
				polygonMode = !polygonMode;
			}
		}
	}

	virtual void Render(const Shader& shader, const RenderingEngine& renderingEngine, const Camera& camera) const
	{
		if (polygonMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		shader.Bind();
		shader.UpdateUniforms(GetTransform(), m_material, renderingEngine, camera);
		m_mesh.Draw();

		if (polygonMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
protected:
private:

	bool polygonMode;

	Mesh m_mesh;
	Material m_material;
};