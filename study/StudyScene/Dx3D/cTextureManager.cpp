#include "StdAfx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager(void)
{
}

cTextureManager::~cTextureManager(void)
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( const char* szFullPath )
{
	if(m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		
		HRESULT hr = D3DXCreateTextureFromFile(g_pD3DDevice, szFullPath, &pTexture);
		
		if(hr != D3D_OK)
		{
			switch(hr)
			{
			case D3DERR_NOTAVAILABLE:
				//�� ��ġ��, ��ȸ�� ��ũ���� ���� �ϰ� ���� �ʴ�.
				break;
			case D3DERR_OUTOFVIDEOMEMORY:
				//Microsoft�� Direct3D�� �� ó���� �ǽ��ϴµ� ����� ���÷��� �޸𸮰� ����.
				break;
			case D3DERR_INVALIDCALL:
				//�޼����� ȣ���� ��ȿ�̴�. ���� ���, �޼����� �Ķ���Ϳ� ��ȿ�� ���� �����Ǿ� �ִ� ��� ���̴�.
				break;
			case D3DXERR_INVALIDDATA:
				//�����Ͱ� ��ȿ�̴�.
				break;
			case E_OUTOFMEMORY:
				//Direct3D �� ȣ���� �Ϸ��ϱ� ���� ����� �޸𸮸� �Ҵ��� ���� ������.
				break;
			}
			return NULL;
		}

		m_mapTexture[szFullPath] = pTexture;
	}

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture( const string& sFullPath )
{
	return GetTexture(sFullPath.c_str());
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTextureEx( const char* szFullPath, OUT D3DXIMAGE_INFO* pImageInfo )
{
	if(m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			szFullPath, 
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN, 
			D3DPOOL_MANAGED, 
			D3DX_FILTER_NONE, 
			D3DX_DEFAULT, 
			0,
			&m_mapImageInfo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath] );
	}
	else if(m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		assert(true && "������ �ε���� ����~!");
	}

	if (pImageInfo)
	{
		*pImageInfo = m_mapImageInfo[szFullPath];
	}

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTextureEx( const string& sFullPath, OUT D3DXIMAGE_INFO* pImageInfo )
{
	return GetTextureEx(sFullPath.c_str(), pImageInfo);
}
