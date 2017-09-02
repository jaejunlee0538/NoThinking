#pragma once
#include "ComponentBase.h"
#include "Viewport.h"
namespace qwer
{
	class CameraComponent :
		public ComponentBase
	{
	public:
		enum ProjectionTypes{
			PERSPECTIVE_PROJ,
			ORTHOGONAL_PROJ
		};
	private:
		ProjectionTypes m_projType;
		float m_fovRad;
		float m_zNear;
		float m_zFar;
		Viewport m_viewport;
		bool m_isDirty;
	public:
		CameraComponent();
		virtual ~CameraComponent();

		virtual void LateUpdate() override;

		MAKE_GETTER(m_projType, Projection);
		MAKE_SETTER_REF_CODE(m_projType, Projection, m_isDirty = true);
		MAKE_GETTER(m_fovRad, FOVRad);
		MAKE_SETTER_REF_CODE(m_fovRad, FOVRad, m_isDirty = true);
		MAKE_GETTER(m_zNear, ZNear);
		MAKE_SETTER_REF_CODE(m_zNear, ZNear, m_isDirty = true);
		MAKE_GETTER(m_zFar, ZFar);
		MAKE_SETTER_REF_CODE(m_zFar, ZFar, m_isDirty = true);
		MAKE_GETTER(m_viewport, Viewport);
		MAKE_SETTER_REF_CODE(m_viewport, Viewport, m_isDirty = true);
	};
}

