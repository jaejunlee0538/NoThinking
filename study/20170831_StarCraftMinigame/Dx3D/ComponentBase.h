#pragma once
namespace qwer {
	class GameObject;
	class ComponentBase
	{
	public:
		ComponentBase();
		virtual ~ComponentBase();

		virtual void Update() = 0;

		void SetEnabled(bool enabled);
		bool GetEnabled() const;

		void SetOwner(GameObject* pOwner);
		GameObject* GetOwner();
	protected:
		GameObject* m_pOwner;
		bool m_bEnabled;
	};
}