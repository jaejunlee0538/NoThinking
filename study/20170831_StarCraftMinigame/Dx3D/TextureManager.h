#pragma once
#include "Singleton.h"
namespace qwer {
	class TextureManager : public Singleton<TextureManager>
	{
	public:
		TextureManager();
		~TextureManager();

		bool Startup();
		void Shutdown();

		void ReleaseUnusedTexture();
		void ReleaseTexture(HashedString name);
		
	};
}