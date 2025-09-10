// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#include "datetimeaxislabel_p.h"

#include <QtCore/qdatetime.h>

QT_BEGIN_NAMESPACE

DateTimeAxisLabel::DateTimeAxisLabel(QGraphicsItem *parent) :
    EditableAxisLabel(parent)
{

}

void DateTimeAxisLabel::finishEditing()
{
    QDateTime oldDateTime = m_dateTime;
    QDateTime newDateTime = QDateTime::fromString(document()->toPlainText(), m_format);
    if (newDateTime.isValid() && newDateTime != m_dateTime) {
        m_dateTime = newDateTime;
        emit dateTimeChanged(oldDateTime, newDateTime);
    } else {
        document()->setHtml(m_htmlBeforeEdit);
    }
}

QDateTime DateTimeAxisLabel::value() const
{
    return m_dateTime;
}

void DateTimeAxisLabel::setValue(const QDateTime &value)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    clearFocus();
    m_dateTime = value;
}

void DateTimeAxisLabel::resetBeforeEditValue()
{
    m_dateTime = m_dateTimeBeforeEdit;
}

void DateTimeAxisLabel::setFormat(const QString &format)
{
    m_format = format;
    // Labels should be edited as a single line regardless to their
    // format because enter triggers applying the current text.
    m_format.replace(QChar::fromLatin1('\n'), QChar::fromLatin1(' '));
}

void DateTimeAxisLabel::setInitialEditValue()
{
    m_dateTimeBeforeEdit = m_dateTime;
    setHtml(m_dateTime.toString(m_format));
}

void DateTimeAxisLabel::keyPressEvent(QKeyEvent *event)
{
    if (isEditEndingKeyPress(event)) {
        // prevent further event processing with a return
        // because the focusOutEvent could have triggered
        // a range change which might have invalidated the current label
        return;
    }

    QGraphicsTextItem::keyPressEvent(event);
}

QT_END_NAMESPACE

#include "moc_datetimeaxislabel_p.cpp"
