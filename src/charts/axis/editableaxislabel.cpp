// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/editableaxislabel_p.h>

#include <QtGui/qtextcursor.h>
#include <QtGui/qtextdocument.h>

QT_BEGIN_NAMESPACE

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
    if (event->text().size() >= 1) {
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

QT_END_NAMESPACE

#include "moc_editableaxislabel_p.cpp"
