#pragma once
#include <NT_Common\HashedString.h>
#include <NT_Common\MacroUtils.h>
namespace qwer {
	class GameObject;
	//TODO : ������ ������Ʈ���� ���� �´� SystemŬ������ ��ϵǾ�� �Ѵ�.
	//���� ������Ʈ�� �ı��Ǹ鼭 ������Ʈ�� �ı��Ǹ� ������Ʈ�� ��ϵ� System�� ������Ʈ�� �ı��Ǿ��ٴ� ���� ���޵Ǿ�� �Ѵ�.
	//������Ʈ �ı��� �޽����� �����ұ� �ƴϸ� System�� ���� �Լ��� ���� ȣ���ұ�?
	class ComponentBase
	{
	protected:
		HashedString m_name;
		GameObject* m_owner;
		bool m_isEnabled;
	public:
		ComponentBase();
		virtual ~ComponentBase();

		//������Ʈ �������� ����Ǿ�� �ϴ� �۾����� �����Ѵ�.
		virtual void Update() {}

		//��� ������Ʈ���� ������Ʈ �ǰ� ���� ����Ǿ�� �ϴ� �۾����� �����Ѵ�.
		virtual void LateUpdate() {}

		//GameObject�� Ȱ��ȭ/��Ȱ��ȭ ��Ų��.
		void SetEnable(bool bEnabled);
		bool GetEnabled() const;

		//this ������Ʈ�� �����ϰ� �ִ� ���� ������Ʈ�� �����Ѵ�.
		void SetOwner(GameObject* owner);
		GameObject* GetOwner();
	};
}