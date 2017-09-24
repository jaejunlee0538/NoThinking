#pragma once
#include "NT_Component\ComponentBase.h"
#include <NT_Common\MacroUtils.h>
namespace qwer
{
	struct Viewport {
		float x;
		float y;
		float w;
		float h;
	};

	enum CameraProjectionTypes {
		PERSPECTIVE_PROJ,
		ORTHOGONAL_PROJ
	};

	struct CameraParamters {
		CameraProjectionTypes m_projType;
		Viewport m_viewport;
		float m_fovRad;
		float m_zNear;
		float m_zFar;
	};

	class CameraComponent :
		public ComponentBase
	{
	public:

	private:
		CameraParamters m_params;
		bool m_isDirty;
	public:
		CameraComponent();
		virtual ~CameraComponent();

		virtual void LateUpdate() override{}

		void SetParameter(const CameraParamters& params);
		const CameraParamters& GetParameter() const;
	};
}

