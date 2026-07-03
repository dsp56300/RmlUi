/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019- The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RMLUI_SVG_ELEMENT_SVG_H
#define RMLUI_SVG_ELEMENT_SVG_H

#include "../Core/Element.h"
#include "../Core/Header.h"

namespace Rml {
namespace SVG {
	struct SVGData;
}

class RMLUICORE_API ElementSVG : public Element {
public:
	RMLUI_RTTI_DefineWithParent(ElementSVG, Element)

	ElementSVG(CoreInstance& core_instance, const String& tag);
	virtual ~ElementSVG();

	/// Returns the element's inherent size.
	bool GetIntrinsicDimensions(Vector2f& dimensions, float& ratio) override;

	/// Loads the current source file if needed. This normally happens automatically during layouting.
	void EnsureSourceLoaded();

protected:
	/// Renders the image.
	void OnRender() override;

	/// Regenerates the element's geometry.
	void OnResize() override;

	/// Checks for changes to the image's source or dimensions.
	/// @param[in] changed_attributes A list of attributes changed on the element.
	void OnAttributeChange(const ElementAttributes& changed_attributes) override;

	/// Called when properties on the element are changed.
	/// @param[in] changed_properties The properties changed on the element.
	void OnPropertyChange(const PropertyIdSet& changed_properties) override;

	void OnChildAdd(Element* child) override;
	void OnChildRemove(Element* child) override;


private:
	void UpdateCachedData();

	// Starts dirty so the very first GetIntrinsicDimensions/OnRender loads the source, even for
	// inline SVG (no `src` attribute change to key off of -- content comes from child markup).
	bool svg_dirty = true;

	SharedPtr<SVG::SVGData> handle;
};

} // namespace Rml

#endif
