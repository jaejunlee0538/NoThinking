#include "stdafx.h"
#include "SphereCollider.h"

LPD3DXMESH	SphereCollider::m_pSphere = NULL;
SphereCollider::SphereCollider(float radius, D3DXVECTOR3 offsetFromParent)
	:m_radius(radius), m_offsetFromParent(offsetFromParent)
{
	if (m_pSphere==NULL) {
		D3DXCreateSphere(g_pD3DDevice, radius, 10, 10, &m_pSphere, NULL);
	}
}

SphereCollider::~SphereCollider()
{
	SAFE_RELEASE(m_pSphere);
}

bool SphereCollider::CheckRayCollision(D3DXVECTOR3 rayPos, D3DXVECTOR3 rayDir, float * distance) const
{
	//������ ��ġ�� ���� ���� ��ǥ��� �����Ѵ�.
	D3DXVECTOR3 sphereWorldPos = m_offsetFromParent;
	if (m_parentObject) {
		sphereWorldPos += m_parentObject->getWorldPosition();
	}
	rayPos = rayPos - sphereWorldPos;
	
	//a*t*t + b*t + c = 0;
	float a, b, c;
	a = D3DXVec3Dot(&rayDir, &rayDir);
	b = 2 * D3DXVec3Dot(&rayPos, &rayDir);
	c = D3DXVec3Dot(&rayPos, &rayPos) - m_radius*m_radius;
	
	//���� ����
	float test = b*b - 4*a*c;//�Ǻ���
	if (test < 0.0f)//�Ǻ����� 0���� ������ �������� �ذ� �������� �ʴ´�!
		return false;

	float t = (-b - test) / (2 * a);
	if (t < 0.0f) //t�� 0���� �۴ٴ� ���� �浹�ϴ� ���� ������ ���ʿ� �ִٴ� ��!
		return false;
	if (distance) //�Ÿ��� �ʿ��ϸ� �浹�������� �Ÿ��� ����ؼ� ��ȯ���ش�.
		*distance = D3DXVec3Length(&(rayDir*t));
	return true;
}

void SphereCollider::Render() const
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pSphere->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}
