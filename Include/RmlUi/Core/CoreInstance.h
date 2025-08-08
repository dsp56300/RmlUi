#pragma once

/*
Added by DSP56300:

As we are audio plugins, and these plugins may be different instances of the same plugin, with a different UI skin, but
run in the same process, we are in desperate need of separating all global variables and static data. This includes
font manager, rml plugins, file interface, etc.

*/

#include "Core/ControlledLifetimeResource.h"

namespace Rml
{
	struct XmlParserData;
	struct PluginVectors;
	struct ElementInstancerPools;
	struct ComputedPropertyData;
	struct LayoutPoolsData;
	struct FactoryData;
	struct ElementMetaPool;

	class CoreInstance final : NonCopyMoveable
	{
	public:
		CoreInstance();
		~CoreInstance();

		RenderInterface* render_interface = nullptr;
		SystemInterface* system_interface = nullptr;
		FileInterface* file_interface = nullptr;
		FontEngineInterface* font_interface = nullptr;
		TextInputHandler* text_input_handler = nullptr;

		struct CoreData {
			// Default interfaces should be created and destroyed on Initialise and Shutdown, respectively.
			UniquePtr<SystemInterface> default_system_interface;
			UniquePtr<FileInterface> default_file_interface;
			UniquePtr<FontEngineInterface> default_font_interface;
			UniquePtr<TextInputHandler> default_text_input_handler;

			SmallUnorderedMap<RenderInterface*, UniquePtr<RenderManager>> render_managers;
			UnorderedMap<String, ContextPtr> contexts;
		};

		ControlledLifetimeResource<CoreData> core_data;

		ControlledLifetimeResource<ElementInstancerPools> element_instancer_pools;
		ControlledLifetimeResource<ElementMetaPool> element_meta_pool;

		ControlledLifetimeResource<LayoutPoolsData> layout_pools_data;

		ControlledLifetimeResource<ComputedPropertyData> computed_property_data;

		ControlledLifetimeResource<PluginVectors> plugin_vectors;

		ControlledLifetimeResource<XmlParserData> xml_parser_data;

		Factory factory;

		StyleSheetSpecification* styleSheetSpecification = nullptr;

		bool initialised = false;
	};
}
