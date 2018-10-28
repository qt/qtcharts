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
#include "datetimeaxislabel_p.h"

#include <QtCore/qdatetime.h>

QT_CHARTS_BEGIN_NAMESPACE

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

QT_CHARTS_END_NAMESPACE

#include "moc_datetimeaxislabel_p.cpp"
