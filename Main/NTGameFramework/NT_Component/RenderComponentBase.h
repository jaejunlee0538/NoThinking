#pragma once
#include "ComponentBase.h"
namespace qwer {
	class RenderComponentBase :
		public ComponentBase
	{
	public:
		RenderComponentBase();
		virtual ~RenderComponentBase();
		virtual void Render() = 0;
	};
}
