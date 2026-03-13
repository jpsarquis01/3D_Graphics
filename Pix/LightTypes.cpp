#include "LightTypes.h"
#include "MaterialManager.h"
#include "Camera.h"

// Directional Light =========================================================================
X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// Calculate the ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	// Calculate the diffuse color
	// Directional light iL is 1.0f so we can ignore
	Vector3 L = -mDirection;
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot;

	// Calculate the specular
	// Directional light iL is 1.0f so we can ignore
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * fallOff;

	return ambient + diffuse + specular;
}
void DirectionalLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}

// Point Light ==================================================================================
X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// Direction to the light
	Vector3 L = mPosition - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	// Calculate the iL
	float attenuation = 1.0f / (mAttenConst + (mAttenLinear * distance) + (mAttenQuad * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);

	// Calculate the ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	// Calculate the diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * iL;

	// Calculate the specular
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * fallOff * iL;

	return ambient + diffuse + specular;
}
void PointLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}
void PointLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	mAttenConst = kConstant;
	mAttenLinear = kLinear;
	mAttenQuad = kQuadratic;
}

// Spot Light ===================================================================================
X::Color SpotLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// Direction to the light
	Vector3 L = mPosition - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	// Calculate the ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	// Check to see if in the cone of the spotlight
	Vector3 lightDir = -L;
	float dotDir = MathHelper::Dot(lightDir, mDirection);
	if (dotDir < mCosAngle)
	{
		return ambient;
	}

	// Calculate the iL
	float spot = pow(dotDir, mDecay);
	float attenuation = 1.0f / (mAttenConst + (mAttenLinear * distance) + (mAttenQuad * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);

	// Calculate the diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * iL;

	// Calculate the specular
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.0f);
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * fallOff * iL;

	return ambient + diffuse + specular;
}
void SpotLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}
void SpotLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}
void SpotLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	mAttenConst = kConstant;
	mAttenLinear = kLinear;
	mAttenQuad = kQuadratic;
}
void SpotLight::SetAngle(float angle)
{
	mCosAngle = cos(angle);
}
void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}