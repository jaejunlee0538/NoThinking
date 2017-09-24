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
		NT_SHADOW_NONE, //�׸��ڸ� �������� �ʴ´�
		NT_SHADOW_NORMAL //�׸��ڸ� �����Ѵ�
	};

	class LightComponent 
		: public ComponentBase
	{
	public:
		LightComponent();
		virtual ~LightComponent();

		//���� ����(���� ��ġ/������ GameObject�� Transform�� ���)
		LightTypes m_lightType;
		Vector4 m_lightColor;

		//Point/Spot Light ����
		float m_range;		//Point/Spot Light
		float m_coneAngle;	//Spot Light only

		//�׸��� ���� ����
		ShadowModes m_shadowMode;
	};
}