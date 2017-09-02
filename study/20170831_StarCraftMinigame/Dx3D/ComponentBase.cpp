#include "stdafx.h"
#include "ComponentBase.h"

namespace qwer {

	ComponentBase::ComponentBase()
	{
	}

	ComponentBase::~ComponentBase()
	{
	}

	void ComponentBase::SetEnabled(bool enabled) {
		m_bEnabled = enabled;
	}

	bool ComponentBase::GetEnabled() const {
		return m_bEnabled;
	}

	void ComponentBase::SetOwner(GameObject * pOwner) {
		m_pOwner = pOwner;
	}

	GameObject * ComponentBase::GetOwner() {
		return m_pOwner;
	}
}