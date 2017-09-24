#pragma once
#include <NT_Component/ComponentBase.h>
#include <NT_Math\Math.h>
namespace qwer
{
	enum LightTypes {
		NT_LIGHT_DIRECTIONAL,	//Directional Light
		NT_LIGHT_POINT,			//Point Light
		NT_LIGHT_SPOT			//Spot Light
	};

	enum ShadowModes {
		NT_SHADOW_NONE, //그림자를 생성하지 않는다
		NT_SHADOW_NORMAL //그림자를 생성한다
	};

	class LightComponent 
		: public ComponentBase
	{
	public:
		LightComponent();
		virtual ~LightComponent();

		//공유 설정(빛의 위치/방향은 GameObject의 Transform을 사용)
		LightTypes m_lightType;
		Vector4 m_lightColor;

		//Point/Spot Light 설정
		float m_range;		//Point/Spot Light
		float m_coneAngle;	//Spot Light only

		//그림자 관련 설정
		ShadowModes m_shadowMode;
	};
}