// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DATETIMEAXISLABEL_H
#define DATETIMEAXISLABEL_H

#include <private/editableaxislabel_p.h>

#include <QtCore/qdatetime.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT DateTimeAxisLabel : public EditableAxisLabel
{
    Q_OBJECT
public:
    DateTimeAxisLabel(QGraphicsItem *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    QDateTime value() const;
    void setValue(const QDateTime &value);
    void setFormat(const QString &format);

private:
    QDateTime m_dateTime;
    QDateTime m_dateTimeBeforeEdit;
    QString m_format;

    void setInitialEditValue() override;
    void finishEditing() override;
    void resetBeforeEditValue() override;

Q_SIGNALS:
    void dateTimeChanged(const QDateTime &oldDateTime, const QDateTime &newDateTime);
};

QT_END_NAMESPACE

#endif // VALUEAXISLABEL_H
