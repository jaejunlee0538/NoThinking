#pragma once
#include <NT_Common/Singleton.h>
#include <NT_Common/HashedString.h>
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