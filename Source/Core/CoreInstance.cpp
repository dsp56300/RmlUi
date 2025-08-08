#include "../../Include/RmlUi/Core/CoreInstance.h"

namespace Rml
{
	CoreInstance::CoreInstance() : factory(*this)
	{
	}

	CoreInstance::~CoreInstance()
	{
		ElementInstancerElement::CheckPoolsOnShutdown(*this);
	}
}
