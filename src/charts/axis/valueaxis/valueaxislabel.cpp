/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/
#include <private/valueaxislabel_p.h>

#include <QtCore/qlocale.h>

QT_CHARTS_BEGIN_NAMESPACE

ValueAxisLabel::ValueAxisLabel(QGraphicsItem *parent) :
    EditableAxisLabel(parent)
{

}

void ValueAxisLabel::finishEditing()
{
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

void ValueAxisLabel::resetBeforeEditValue()
{
    m_value = m_valueBeforeEdit;
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

void ValueAxisLabel::setInitialEditValue()
{
    m_valueBeforeEdit = m_value;
    setHtml(QString::number(m_value));
}

void ValueAxisLabel::keyPressEvent(QKeyEvent *event)
{
    if (isEditEndingKeyPress(event)) {
        // prevent further event processing with a return
        // because the focusOutEvent could have triggered
        // a range change which might have invalidated the current label
        return;
    }

    if (event->text().length() >= 1) {
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

QT_CHARTS_END_NAMESPACE

#include "moc_valueaxislabel_p.cpp"
