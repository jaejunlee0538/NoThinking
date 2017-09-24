#include "stdafx.h"
#include "ComponentBase.h"

namespace qwer {

	ComponentBase::ComponentBase()
	{
	}

	ComponentBase::~ComponentBase()
	{
	}

	void ComponentBase::SetEnable(bool bEnabled) {
		m_isEnabled = bEnabled;
	}
	bool ComponentBase::GetEnabled() const {
		return m_isEnabled;
	}

	void ComponentBase::SetOwner(GameObject * owner) {
		m_owner = owner;
	}
	GameObject * ComponentBase::GetOwner() {
		return m_owner;
	}
}