/*
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2023, Aliaksandr Kalenik <kalenik.aliaksandr@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Utf16View.h>
#include <LibJS/Runtime/Completion.h>
#include <LibJS/Runtime/Utf16String.h>
#include <LibWeb/Bindings/SVGTextPositioningElementPrototype.h>
#include <LibWeb/CSS/Parser/Parser.h>
#include <LibWeb/DOM/Document.h>
#include <LibWeb/Layout/Node.h>
#include <LibWeb/SVG/AttributeNames.h>
#include <LibWeb/SVG/AttributeParser.h>
#include <LibWeb/SVG/SVGGeometryElement.h>
#include <LibWeb/SVG/SVGTextPositioningElement.h>

namespace Web::SVG {

SVGTextPositioningElement::SVGTextPositioningElement(DOM::Document& document, DOM::QualifiedName qualified_name)
    : SVGTextContentElement(document, move(qualified_name))
{
}

void SVGTextPositioningElement::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(SVGTextPositioningElement);
    Base::initialize(realm);
}

void SVGTextPositioningElement::attribute_changed(FlyString const& name, Optional<String> const& old_value, Optional<String> const& value, Optional<FlyString> const& namespace_)
{
    Base::attribute_changed(name, old_value, value, namespace_);

    if (name == SVG::AttributeNames::x) {
        m_x = AttributeParser::parse_length_percentage_or_number(value.value_or(String {}));
    } else if (name == SVG::AttributeNames::y) {
        m_y = AttributeParser::parse_length_percentage_or_number(value.value_or(String {}));
    } else if (name == SVG::AttributeNames::dx) {
        m_dx = AttributeParser::parse_length_percentage_or_number(value.value_or(String {}));
    } else if (name == SVG::AttributeNames::dy) {
        m_dy = AttributeParser::parse_length_percentage_or_number(value.value_or(String {}));
    }
}

Gfx::FloatPoint SVGTextPositioningElement::get_offset(CSSPixelSize const& viewport_size) const
{
    if (!layout_node())
        return {};

    auto const viewport_width = viewport_size.width();
    auto const viewport_height = viewport_size.height();

    auto const& node = static_cast<Layout::Node const&>(*layout_node());

    auto const x = m_x.value_or(LengthPercentageOrNumber(0)).to_px(node, viewport_width).to_float();
    auto const y = m_y.value_or(LengthPercentageOrNumber(0)).to_px(node, viewport_height).to_float();
    auto const dx = m_dx.value_or(LengthPercentageOrNumber(0)).to_px(node, viewport_width).to_float();
    auto const dy = m_dy.value_or(LengthPercentageOrNumber(0)).to_px(node, viewport_height).to_float();

    return { x + dx, y + dy };
}

}
