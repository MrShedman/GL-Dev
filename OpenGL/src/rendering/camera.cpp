
#include "camera.h"
#include "renderingEngine.h"
#include "math\MathHelper.h"
#include "core\coreEngine.h"
#include "window\Mouse.h"
#include "core\game.h"
#include <iostream>

Matrix4f Camera::GetViewProjection() const
{
	//This comes from the conjugate rotation because the world should appear to rotate
	//opposite to the camera's rotation.
	Matrix4f cameraRotation = GetTransform().GetTransformedRot().Conjugate().ToRotationMatrix();
	
	//Similarly, the translation is inverted because the world appears to move opposite
	//to the camera's movement.
	Matrix4f cameraTranslation = Matrix4f().InitTranslation(GetTransform().GetTransformedPos() * -1);
	
	return m_projection * cameraRotation * cameraTranslation;
}

void CameraComponent::AddToEngine(CoreEngine* engine) const
{
	//TODO: This is probably not the correct solution in the case of multiple cameras,
	//and should be investigated in the future.
	engine->GetRenderingEngine()->SetMainCamera(m_camera);
}

void CameraComponent::Update(float delta)
{

}

void CameraComponent::ProcessInput(const Event& event, float delta)
{
	if (event.type == Event::Resized)
	{
		glViewport(0, 0, event.size.width, event.size.height);

		float aspect = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);

		SetProjection(Matrix4f().InitPerspective(ToRadians(70.0f), aspect, 0.1f, 1000.0f));
	}
}

void CameraComponent::SetParent(Entity* parent)
{
	EntityComponent::SetParent(parent);
	
	//The camera's transform is initialized here because this is the first point where
	//there is a parent object with a transform.
	m_camera.SetTransform(GetTransform());
}
