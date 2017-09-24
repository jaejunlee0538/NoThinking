#pragma once
#include <d3dx9.h>
#include <NT_Component\ComponentBase.h>
#include <NT_Common\HashedString.h>
namespace qwer
{
	class MeshRenderComponent :
		public ComponentBase
	{
	public:
		MeshRenderComponent();
		~MeshRenderComponent();

		bool m_castShadow;
		bool m_receiveShadow;
		//TODO : Material *
		//TODO : Mesh *
	};
}
