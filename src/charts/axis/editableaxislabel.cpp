/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <private/editableaxislabel_p.h>

#include <QtGui/qtextcursor.h>
#include <QtGui/qtextdocument.h>

QT_CHARTS_BEGIN_NAMESPACE

EditableAxisLabel::EditableAxisLabel(QGraphicsItem *parent) :
    QGraphicsTextItem(parent)
{

}

void EditableAxisLabel::focusInEvent(QFocusEvent *event)
{
    m_htmlBeforeEdit = toHtml();
    setTextWidth(-1);
    setInitialEditValue();
    m_editing = true;
    QGraphicsTextItem::focusInEvent(event);
}

void EditableAxisLabel::focusOutEvent(QFocusEvent *event)
{
    // perform the modifications before calling finishEditing
    // because finishEditing emits signals that can trigger
    // range change which might invalidate the current label
    QGraphicsTextItem::focusOutEvent(event);
    setTextInteractionFlags(Qt::NoTextInteraction);
    m_editing = false;

    finishEditing();
}

bool EditableAxisLabel::sceneEvent(QEvent *event)
{
    if (m_editable && event->type() == QEvent::GraphicsSceneMouseDoubleClick) {
        setTextInteractionFlags(Qt::TextEditorInteraction);

        bool ret = QGraphicsTextItem::sceneEvent(event);
        // QGraphicsTextItem::sceneevent needs to be processed before
        // the focus and text selection
        setFocus(Qt::MouseFocusReason);
        QTextCursor cursor = textCursor();
        cursor.select(QTextCursor::Document);
        setTextCursor(cursor);
        return ret;
    }
    return QGraphicsTextItem::sceneEvent(event);
}

void EditableAxisLabel::setEditable(bool editable)
{
    m_editable = editable;
}

void EditableAxisLabel::reloadBeforeEditContent()
{
    resetBeforeEditValue();
    setHtml(m_htmlBeforeEdit);
}

QRectF EditableAxisLabel::boundingRect() const
{
    QRectF ret = QGraphicsTextItem::boundingRect();

    // add 2px margin to allow the cursor to
    // show up properly when editing
    if (m_editing)
        ret.setWidth(ret.width() + 2);
    return ret;
}

bool EditableAxisLabel::isEditEndingKeyPress(QKeyEvent *event)
{
    if (event->text().length() >= 1) {
        // finish editing with enter or ESC
        if (event->key() == Qt::Key_Enter ||
                event->key() == Qt::Key_Return) {
            clearFocus();
            return true;
        } else if (event->key() == Qt::Key_Escape) {
            document()->setHtml(m_htmlBeforeEdit);
            clearFocus();
            return true;
        }
    }
    return false;
}

QT_CHARTS_END_NAMESPACE

#include "moc_editableaxislabel_p.cpp"
