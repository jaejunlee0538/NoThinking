#pragma once
#include <NT_Common/Singleton.h>
#include <NT_Common/HashedString.h>
#include <unordered_map>
#include "GraphicSystem.h"

namespace qwer {
	class TextureManager : public Singleton<TextureManager>
	{
	public:
		TextureManager();
		~TextureManager();

		bool Startup(DirectXDevicePtr pDevice);
		void Shutdown();

		void ReleaseTexture(HashedString name);
		void ReleaseUnusedTexture();
		void Release();

		DirectXTexturePtr CreateTexture(HashedString name);
	private:
		typedef std::unordered_map<HashedString, DirectXTexturePtr, HashedStringHashFunc, HashedStringHashFunc> TextureMap;
		TextureMap m_textures;
		DirectXDevicePtr m_pDevice;
	};
}