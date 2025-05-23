/*
 * Copyright (c) 2023, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Forward.h>
#include <LibWeb/HTML/BrowsingContext.h>
#include <LibWeb/Layout/ReplacedBox.h>

namespace Web::Layout {

class AudioBox final : public ReplacedBox {
    GC_CELL(AudioBox, ReplacedBox);
    GC_DECLARE_ALLOCATOR(AudioBox);

public:
    virtual void prepare_for_replaced_layout() override;

    HTML::HTMLAudioElement& dom_node();
    HTML::HTMLAudioElement const& dom_node() const;

    virtual GC::Ptr<Painting::Paintable> create_paintable() const override;

    bool should_paint() const;

private:
    AudioBox(DOM::Document&, DOM::Element&, GC::Ref<CSS::ComputedProperties>);
};

}
