/*
 * Copyright (c) 2024, Aliaksandr Kalenik <kalenik.aliaksandr@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Painting/SVGForeignObjectPaintable.h>
#include <LibWeb/SVG/SVGSVGElement.h>

namespace Web::Painting {

JS_DEFINE_ALLOCATOR(SVGForeignObjectPaintable);

JS::NonnullGCPtr<SVGForeignObjectPaintable> SVGForeignObjectPaintable::create(Layout::SVGForeignObjectBox const& layout_box)
{
    return layout_box.heap().allocate_without_realm<SVGForeignObjectPaintable>(layout_box);
}

SVGForeignObjectPaintable::SVGForeignObjectPaintable(Layout::SVGForeignObjectBox const& layout_box)
    : PaintableWithLines(layout_box)
{
}

Layout::SVGForeignObjectBox const& SVGForeignObjectPaintable::layout_box() const
{
    return static_cast<Layout::SVGForeignObjectBox const&>(layout_node());
}

TraversalDecision SVGForeignObjectPaintable::hit_test(CSSPixelPoint position, HitTestType type, Function<TraversalDecision(HitTestResult)> const& callback) const
{
    if (type == HitTestType::Test) {
        dbgln("SVGForeignObjectPaintable::hit_test {} ({})", class_name(), layout_node().debug_description());
        for (auto const* child = last_child(); child; child = child->previous_sibling()) {
            dbgln("    {} ({})", child->class_name(), child->layout_node().debug_description());
        }
    }
    return PaintableWithLines::hit_test(position, type, callback);
}

void SVGForeignObjectPaintable::paint(PaintContext& context, PaintPhase phase) const
{
    PaintableWithLines::paint(context, phase);
}

}
