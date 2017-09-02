#pragma once

struct ST_BONE;


enum CrtAction {

	CrtAction_Idle,
	CrtAction_Run,
	CrtAction_Attack,
	CrtAction_end

};


class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//�ϳ��� ����
	ST_BONE*					m_pRootFrame;			
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;

	// ��ü���� ����
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(ST_SPHERE, m_stSphere, BoundingSphere);

public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	~cSkinnedMesh(void);
	
	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition(); // �׽�Ʈ��
private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();

private:
	LPD3DXFRAME					m_pRoot;
	CrtAction					m_eActionAttack;
	CrtAction					m_eActionRun;
	float						changeActionTime;
	float						m_TrackWeight0;
	float						m_TrackWeight1;
	int							m_PrevAnimationIndex;
	bool						m_playAni;
	double						m_dPrevPosition;
public:

	D3DXMATRIX					m_matFace;
	D3DXMATRIX					m_matTail;
	D3DXMATRIXA16					m_matRoot;
};

