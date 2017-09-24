#pragma once

#include <NT_Math\Vector3.h>
namespace qwer
{
	class ShaderMaterial
	{
	public:
		//ambient는 diffuse와 같다.
		Vector4 diffuse;
		Vector4 specular; //w : Specular Power
		Vector4 emissive;
	};
}