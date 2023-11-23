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

#ifndef VALUEAXISLABEL_H
#define VALUEAXISLABEL_H

#include <private/editableaxislabel_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT ValueAxisLabel : public EditableAxisLabel
{
    Q_OBJECT
public:
    ValueAxisLabel(QGraphicsItem *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    qreal value() const;
    void setValue(const qreal &value);

private:
    qreal m_value = 0.0;
    qreal m_valueBeforeEdit = 0.0;

    void setInitialEditValue() override;
    void finishEditing() override;
    void resetBeforeEditValue() override;

Q_SIGNALS:
    void valueChanged(qreal oldValue, qreal newValue);
};

QT_END_NAMESPACE

#endif // VALUEAXISLABEL_H
