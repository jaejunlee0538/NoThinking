#pragma once
#include <NT_Common\Singleton.h>
namespace qwer
{
	class MaterialManager
		: public Singleton<MaterialManager>
	{
	public:
		MaterialManager();
		~MaterialManager();
	};
}