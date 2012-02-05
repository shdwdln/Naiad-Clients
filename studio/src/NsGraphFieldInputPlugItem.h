// -----------------------------------------------------------------------------
//
// NsGraphFieldInputPlugItem.h
//
// Class for Op field input plug items, header file.
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

#ifndef NS_GRAPH_FIELD_INPUT_PLUG_ITEM_H
#define NS_GRAPH_FIELD_INPUT_PLUG_ITEM_H

#include "NsGraphInputPlugItem.h"
#include "NsFieldInputPlugObject.h"
#include "NsPreferences.h"
#include <QDebug>

// -----------------------------------------------------------------------------

// NsGraphFieldInputPlugItem
// -------------------------
//! Class for field input plug items in the graph view.

class NsGraphFieldInputPlugItem : public NsGraphInputPlugItem
{
    Q_OBJECT

public:     // Base interface.

    //! DTOR.
    virtual
    ~NsGraphFieldInputPlugItem()
    { qDebug() << "~NsGraphFieldInputPlugItem"; }

    virtual QPointF
    plugPos() const
    { return _plugPos; }

    //! Covariant return type.
    virtual NsFieldInputPlugObject* 
    plugObject() const
    { return _fipo; }

#ifdef NS_GRAPH_VIEW_DEBUG
    virtual QString
    plugType() const
    { return QString("Field Input"); }
#endif  // NS_GRAPH_VIEW_DEBUG

public:

    explicit
    NsGraphFieldInputPlugItem(
        NsFieldInputPlugObject *fipo,
        NsGraphOpItem          &parent,
        const qreal             diameter,
        const QPointF          &plugPos,
        const QLineF           &line,
        const QPointF          &expTextPos,
        const QPointF          &minTextPos,
        const QString          &text,
        const qreal             xRadius       = 2.,
        const qreal             yRadius       = 2.,
        const qreal             sigPenWidth   = 2.)
        : NsGraphInputPlugItem(fipo, parent, diameter)
        , _fipo(fipo)
        , _plugPos(plugPos)
        , _text(text)
        , _textFont("sansserif", 8)
        , _expTextPos(expTextPos)
        , _minTextPos(minTextPos)
        , _expTextRect(computeTextRect(_text, _textFont, _expTextPos))
        , _minTextRect(computeTextRect(_text, _textFont, _minTextPos))
        , _line(line)
        , _expShapePath(computeFieldPlugPath(plugPos, diameter, 
                                             xRadius, yRadius))
        , _expBoundingRect(computeBoundingRect(_expShapePath, 
                                               _expTextRect, 
                                               0.5*2))
        , _minShapePath(computeFieldPlugPath(_minTextPos, diameter, 
                                             xRadius, yRadius))
        , _minBoundingRect(computeBoundingRect(_minShapePath,   
                                               _minTextRect, 
                                               0.5*2))
        , _sigPenWidth(sigPenWidth)
        , _sigPath(computeSigPath(*_fipo, plugPos, diameter))
    {}

protected:

    virtual QRectF
    boundingRect() const
    { return _boundingRect(); }

    virtual QPainterPath
    shape() const
    { return _shape(); }

    virtual void
    paint(QPainter                       *painter,
          const QStyleOptionGraphicsItem *option,
          QWidget                        *widget)
    {
        const QPen shapePen =    
            QPen(NsPreferences::instance()->graphViewPlugLineColor(), 2);
        const QBrush shapeBrush =
            QBrush(NsPreferences::instance()->graphViewPlugBackground());
        const bool group = _fipo->isGroup();
        const QColor sigColor = 
           NsPreferences::instance()->graphViewSignatureColor(_fipo->sigName());
        const QPen   sigPen = group ? QPen(sigColor, _sigPenWidth) : Qt::NoPen;
        const QBrush sigBrush = group ? Qt::NoBrush : QBrush(sigColor);
        const QPen textPen = 
            QPen(NsPreferences::instance()->graphViewPlugTextColor());

        if (_fipo->isSmacked()) {
            paintSmacked(painter, _minShapePath, shapePen, shapeBrush);
            paintText(painter, textPen, _textFont, _minTextRect, _text);
        }
        else {
            paintUnsmacked(painter,
                           _expShapePath, _line, shapePen, shapeBrush,
                           _sigPath, sigPen, sigBrush);
            paintText(painter, textPen, _textFont, _expTextRect, _text);
        }
    }

private:

    QRectF
    _boundingRect() const
    { return _expBoundingRect.united(_minBoundingRect); }

    const QPainterPath&
    _shape() const
    { return (_fipo->isSmacked() ? _minShapePath : _expShapePath); }

private:    // Member variables.

    NsFieldInputPlugObject *_fipo; //!< Resource.

    QPointF      _plugPos;    

    QString      _text;
    QFont        _textFont;
    QPointF      _expTextPos;
    QPointF      _minTextPos;
    QRectF       _expTextRect;
    QRectF       _minTextRect;

    QLineF       _line;
    QPainterPath _expShapePath;
    QRectF       _expBoundingRect;
    QPainterPath _minShapePath;
    QRectF       _minBoundingRect;

    qreal        _sigPenWidth;
    QPainterPath _sigPath;
};

#endif // NS_GRAPH_FIELD_INPUT_PLUG_ITEM_H