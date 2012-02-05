// -----------------------------------------------------------------------------
//
// NsBodyHeaderBox.h
//
// Naiad Studio body header box, header file.
//
// Copyright (c) 2011 Exotic Matter AB. All rights reserved.
//
// This file is part of Open Naiad Studio.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// * Neither the name of Exotic Matter AB nor its contributors may be used to
// endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// -----------------------------------------------------------------------------

#ifndef NS_BODY_HEADER_BOX_H
#define NS_BODY_HEADER_BOX_H

#include "NsValueHeaderBox.h"   // Base.
#include "NsBodyObject.h"

namespace Nb { class TileLayout; }

// -----------------------------------------------------------------------------

// NsBodyHeaderBox
// -------------
//! The NsBodyHeaderBox class, representing a collapsible group box showing
//! basic information about a body.

class NsBodyHeaderBox : public NsValueHeaderBox
{
    Q_OBJECT

public:

    explicit
    NsBodyHeaderBox(NsBodyObject  *bo,
                    const QString &title  = "Header",
                    QWidget       *parent = 0);
};

// -----------------------------------------------------------------------------

class NsTileLayoutBox : public NsGroupBox
{
    Q_OBJECT

public:

    explicit
    NsTileLayoutBox(const Nb::TileLayout &tl, NsBodyHeaderBox &parent);
};

// -----------------------------------------------------------------------------

class NsShapeBox : public NsGroupBox
{
    Q_OBJECT

public:

    explicit
    NsShapeBox(const NsBodyObject::ShapeInfo &si, NsBodyHeaderBox &parent);
};

// -----------------------------------------------------------------------------

class NsChannelBox : public NsGroupBox
{
    Q_OBJECT

public:

    explicit
    NsChannelBox(const NsBodyObject::ShapeInfo::ChannelInfo &ci,
                 NsShapeBox                                 &parent);
};

// -----------------------------------------------------------------------------

#endif // NS_BODY_HEADER_BOX_H