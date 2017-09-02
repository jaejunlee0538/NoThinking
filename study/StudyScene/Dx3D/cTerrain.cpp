#include "stdafx.h"
#include "cTerrain.h"
#include "cMtlTex.h"

cTerrain::cTerrain()
	: m_pMesh(NULL)
	, m_pMtlTex(NULL)
	, m_fBrightness(0.7f)
	, m_ft(0)
	, m_fHeightRadio(0.1f)
{
}

cTerrain::~cTerrain()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_DELETE(m_pMtlTex);

	for (size_t i = 0; i < m_vecvecVertex.size(); ++i) { m_vecvecVertex[i].clear(); }
}

void cTerrain::Setup()
{
	BuildMesh(m_vecVertex);

	//머테리얼
	m_pMtlTex = new cMtlTex;
	m_pMtlTex->AddRef();
	ZeroMemory(&m_pMtlTex->GetMtl(), sizeof(m_pMtlTex->GetMtl()));
	mtl.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	mtl.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	mtl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	mtl.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.f);
	m_pMtlTex->SetMtl(mtl);
	string sTexturePath = string("HeightMapData/") + string("terrain.jpg");
	m_pMtlTex->SetTexture(g_pTextureManager->GetTexture(sTexturePath));
	

}
void cTerrain::BuildMesh(vector<ST_PNT_VERTEX>& vecVertex)
{
	ST_PNT_VERTEX vertex;
	vertex.n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex.t = D3DXVECTOR2( 0.0f, 0.0f);

	//버텍스
	m_vecV.clear();
	vecVertex.clear();
	D3DXVECTOR3 v3;
	size_t fHeigthNum = 0;

	for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
	{
		for (size_t j = 0; j < ROOM_LENGTH + 1; ++j)
		{
			v3 = D3DXVECTOR3((float)j, m_vecHeight[fHeigthNum++] * m_fHeightRadio, (float)i);
			vertex.p = v3;
			vertex.t.x = ((float)j / ROOM_LENGTH + 1);
			vertex.t.y = ((float)i / ROOM_LENGTH + 1);
			vecVertex.push_back(vertex);
		}
	}
	//인덱스
	m_vecI.clear();
	int nVertexNum = -1;
	int nCnt = 0;
	for (size_t i = 0; i < ROOM_LENGTH; ++i)
	{
		for (size_t j = 0; j < ROOM_LENGTH; j++)
		{
			//좌하단
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + (ROOM_LENGTH + 1) + j);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + j + 1);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + j);
			//우상단
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + (ROOM_LENGTH + 1) + j);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + (ROOM_LENGTH + 1) + j + 1);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + j + 1);
		}
	}
	//노멀 계산용 2차원 벡터
	vector<vector<D3DXVECTOR3>> vecvec;
	for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
	{
		vector<D3DXVECTOR3> vec;
		vec.resize(ROOM_LENGTH + 1);
		vecvec.push_back(vec);
	}
	for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
	{
		for (size_t j = 0; j < ROOM_LENGTH + 1; ++j)
		{
			if (j == 0 || j == ROOM_LENGTH ||
				i == 0 || i == ROOM_LENGTH)
			{
				vecvec[i][j] = D3DXVECTOR3(0, 1, 0);
			}
			else
			{
				D3DXVECTOR3 vx1 = m_vecVertex[(ROOM_LENGTH + 1)*i + (j - 1)].p;
				D3DXVECTOR3 vx2 = m_vecVertex[(ROOM_LENGTH + 1)*i + (j + 1)].p;
				D3DXVECTOR3 vz1 = m_vecVertex[(ROOM_LENGTH + 1)*(i + 1) + j].p;
				D3DXVECTOR3 vz2 = m_vecVertex[(ROOM_LENGTH + 1)*(i - 1) + j].p;

				D3DXVec3Cross(&vecvec[i][j], &(vx2 - vx1), &(vz2 - vz1));
			}

			D3DXVec3Normalize(&vecvec[i][j], &vecvec[i][j]);
			vecVertex[((ROOM_LENGTH + 1)*i) + j].n = vecvec[i][j];
		}
	}
	vecvec.clear();

	//메쉬 구성 시작
	HRESULT hr = (D3DXCreateMeshFVF(m_vecI.size() / 3,
		vecVertex.size(),
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh));

	assert(m_pMesh != NULL);

	//버텍스 버퍼
	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	//인덱스 버퍼
	DWORD* pI = nullptr;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &m_vecI[0], m_vecI.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

}

void cTerrain::Update()
{
	
}

void cTerrain::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->LightEnable(0, true);
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		//g_pD3DDevice->SetTexture(0, NULL);
	}

	if (m_pMesh)
		m_pMesh->DrawSubset(0);

	g_pD3DDevice->SetTexture(0, nullptr);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}


float cTerrain::GetHeight(const D3DXVECTOR3 & vPos)
{
	float ret = 0;
	if (m_vecvecVertex.empty())
	{
		m_vecvecVertex.reserve((ROOM_LENGTH + 1)*(ROOM_LENGTH + 1));
		for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
		{
			vector<D3DXVECTOR3> vec;
			vec.resize(ROOM_LENGTH + 1);
			m_vecvecVertex.push_back(vec);
		}

		for (size_t z = 0; z <= ROOM_LENGTH; ++z)
		{
			for (size_t x = 0; x <= ROOM_LENGTH; ++x)
			{
				D3DXVECTOR3 v = m_vecVertex[z*(ROOM_LENGTH + 1) + x].p;
				m_vecvecVertex[z][x] = v;
			}
		}
	}
	//벡터 인덱스역할. 좌하단 인덱스가 나오게 된다.
	float x = floorf(vPos.x);
	float z = floorf(vPos.z);

	//A-B
	//|\|
	//C-D

	D3DXVECTOR3 vA = m_vecvecVertex[z + 1][x];
	D3DXVECTOR3 vB = m_vecvecVertex[z + 1][x + 1];
	D3DXVECTOR3 vC = m_vecvecVertex[z][x];
	D3DXVECTOR3 vD = m_vecvecVertex[z][x + 1];

	D3DXVECTOR3 vDU = vA - vC;
	D3DXVECTOR3 vLR = vD - vC;
	D3DXVECTOR3 vRL = vA - vB;
	D3DXVECTOR3 vUD = vD - vB;

	float fTempZ = (vPos.z - vC.z) / vDU.z;
	float fTempX = (vPos.x - vC.x) / vLR.x;

	//윗면인지 아랫면인지
	bool isDown = false;

	if (fTempZ + fTempX <= 1)
	{
		isDown = true;
	}
	else { isDown = false; }

	if (isDown == true)
	{
		D3DXVECTOR3 vH = (vDU*fTempZ);
		D3DXVECTOR3 vW = (vLR*fTempX);

		ret = ((vH + vW) + vC).y;
	}
	else if (isDown == false)
	{
		fTempZ = (vPos.z - vB.z) / vUD.z;
		fTempX = (vPos.x - vB.x) / vRL.x;
		D3DXVECTOR3 vH = (vUD*fTempZ);
		D3DXVECTOR3 vW = (vRL*fTempX);

		ret = ((vH + vW) + vB).y;
	}

	return ret;
}

