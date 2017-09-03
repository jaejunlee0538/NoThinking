#pragma once
namespace qwer {
	class GameObject;
	//TODO : 각각의 컴포넌트들은 각자 맞는 System클래스에 등록되어야 한다.
	//게임 오브젝트가 파괴되면서 컴포넌트가 파괴되면 컴포넌트가 등록된 System에 컴포넌트가 파괴되었다는 것이 전달되어야 한다.
	//컴포넌트 파괴는 메시지로 전달할까 아니면 System의 해제 함수를 직접 호출할까?
	class ComponentBase
	{
	protected:
		HashedString m_name;
		GameObject* m_pOwner;
		bool m_bEnabled;
	public:
		ComponentBase();
		virtual ~ComponentBase();

		//업데이트 과정에서 수행되어야 하는 작업들을 구현한다.
		virtual void Update() {}

		//모든 오브젝트들이 업데이트 되고 나서 수행되어야 하는 작업들을 구현한다.
		virtual void LateUpdate() {}

		//GameObject를 활성화/비활성화 시킨다.
		MAKE_SETTER(m_bEnabled, Enabled);
		MAKE_GETTER(m_bEnabled, Enabled);

		//this 컴포넌트를 소유하고 있는 게임 오브젝트를 설정한다.
		MAKE_SETTER(m_pOwner, Owner);
		MAKE_GETTER(m_pOwner, Owner);
	};
}