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
#include "valueaxislabel_p.h"

#include <QtCore/qlocale.h>
#include <QtGui/qevent.h>
#include <QtGui/qtextcursor.h>
#include <QtGui/qtextdocument.h>

QT_CHARTS_BEGIN_NAMESPACE

ValueAxisLabel::ValueAxisLabel(QGraphicsItem *parent) :
    QGraphicsTextItem(parent)
{

}

void ValueAxisLabel::focusInEvent(QFocusEvent *event)
{
    m_htmlBeforeEdit = toHtml();
    setTextWidth(-1);
    m_valueBeforeEdit = m_value;
    setHtml(QString::number(m_value));
    m_editing = true;
    QGraphicsTextItem::focusInEvent(event);
}

void ValueAxisLabel::focusOutEvent(QFocusEvent *event)
{
    // perform the modifications before emitting valueChanged
    // because slots attached to valueChanged can trigger
    // a range change which might invalidate the current label
    QGraphicsTextItem::focusOutEvent(event);
    setTextInteractionFlags(Qt::NoTextInteraction);
    m_editing = false;

    bool ok = false;
    QLocale locale;
    qreal oldValue = m_value;
    qreal newValue = locale.toDouble(document()->toPlainText(), &ok);
    if (ok && newValue != m_value) {
        m_value = newValue;
        emit valueChanged(oldValue, newValue);
    } else {
        document()->setHtml(m_htmlBeforeEdit);
    }
}

qreal ValueAxisLabel::value() const
{
    return m_value;
}

void ValueAxisLabel::setValue(const qreal &value)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    clearFocus();
    m_value = value;
}

void ValueAxisLabel::reloadBeforeEditContent()
{
    m_value = m_valueBeforeEdit;
    setHtml(m_htmlBeforeEdit);
}

QRectF ValueAxisLabel::boundingRect() const
{
    QRectF ret = QGraphicsTextItem::boundingRect();

    // add 2px margin to allow the cursor to
    // show up properly when editing
    if (m_editing)
        ret.setWidth(ret.width() + 2);
    return ret;
}

void ValueAxisLabel::setEditable(bool editable)
{
    m_editable = editable;
}

void ValueAxisLabel::keyPressEvent(QKeyEvent *event)
{
    if (event->text().length() >= 1) {
        // finish editing with enter
        if (event->key() == Qt::Key_Enter ||
                event->key() == Qt::Key_Return) {
            clearFocus();
            // prevent further event processing with a return
            // because the focusOutEvent could have triggered
            // a range change which might have invalidated the current label
            return;
        } else if (event->key() == Qt::Key_Escape) {
            document()->setHtml(m_htmlBeforeEdit);
            clearFocus();
            // prevent further event processing with a return
            // because the focusOutEvent could have triggered
            // a range change which might have invalidated the current label
            return;
        }

        QLocale locale;
        if (!event->text().at(0).isDigit()
                && event->text().at(0) != locale.decimalPoint()
                && event->text().at(0) != locale.negativeSign()
                && event->text().at(0) != locale.exponential()
                && event->key() != Qt::Key_Backspace
                && event->key() != Qt::Key_Delete) {
            event->ignore();
            return;
        }
    }
    QGraphicsTextItem::keyPressEvent(event);
}

bool ValueAxisLabel::sceneEvent(QEvent *event)
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

QT_CHARTS_END_NAMESPACE

#include "moc_valueaxislabel_p.cpp"
