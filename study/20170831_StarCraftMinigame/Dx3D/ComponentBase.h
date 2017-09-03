#pragma once
namespace qwer {
	class GameObject;
	//TODO : ������ ������Ʈ���� ���� �´� SystemŬ������ ��ϵǾ�� �Ѵ�.
	//���� ������Ʈ�� �ı��Ǹ鼭 ������Ʈ�� �ı��Ǹ� ������Ʈ�� ��ϵ� System�� ������Ʈ�� �ı��Ǿ��ٴ� ���� ���޵Ǿ�� �Ѵ�.
	//������Ʈ �ı��� �޽����� �����ұ� �ƴϸ� System�� ���� �Լ��� ���� ȣ���ұ�?
	class ComponentBase
	{
	protected:
		HashedString m_name;
		GameObject* m_pOwner;
		bool m_bEnabled;
	public:
		ComponentBase();
		virtual ~ComponentBase();

		//������Ʈ �������� ����Ǿ�� �ϴ� �۾����� �����Ѵ�.
		virtual void Update() {}

		//��� ������Ʈ���� ������Ʈ �ǰ� ���� ����Ǿ�� �ϴ� �۾����� �����Ѵ�.
		virtual void LateUpdate() {}

		//GameObject�� Ȱ��ȭ/��Ȱ��ȭ ��Ų��.
		MAKE_SETTER(m_bEnabled, Enabled);
		MAKE_GETTER(m_bEnabled, Enabled);

		//this ������Ʈ�� �����ϰ� �ִ� ���� ������Ʈ�� �����Ѵ�.
		MAKE_SETTER(m_pOwner, Owner);
		MAKE_GETTER(m_pOwner, Owner);
	};
}