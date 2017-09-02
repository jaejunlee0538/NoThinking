#pragma once
#include "Singleton.h"
namespace qwer {
	class TextureManager : public Singleton<TextureManager>
	{
	public:
		TextureManager();
		~TextureManager();
	};
}