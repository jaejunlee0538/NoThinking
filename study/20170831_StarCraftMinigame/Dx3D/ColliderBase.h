#pragma once

namespace qwer
{
	class GameObject;
	/**
	 * \brief 
	 */
	class ColliderBase
	{
	public:
		ColliderBase() :m_pParentObject(nullptr) {}
		virtual ~ColliderBase() {
			//SAFE_RELEASE(m_parentObject);
		}

		void SetParent(GameObject* parentObject) {
			//SAFE_RELEASE(m_parentObject);
			m_pParentObject = parentObject;
			//m_parentObject->AddRef();
			//GameObject�� ColliderBase�� ������ �ְ� GameObject�� �ı��ڿ��� Collider�� �����ϱ� ������
			//Collider�� GameObject�� AddRef�� ȣ���ϸ� �ȵȴ�.
		}

		virtual bool CheckRayCollision(D3DXVECTOR3 rayPos, D3DXVECTOR3 rayDir, float* distance) const = 0;
		virtual void Render() const {}
	protected:
		GameObject* m_pParentObject;
	};
}

