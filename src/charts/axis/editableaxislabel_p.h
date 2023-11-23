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

#ifndef EDITABLEAXISLABEL_P_H
#define EDITABLEAXISLABEL_P_H

#include <QtCharts/private/qchartglobal_p.h>

#include <QtWidgets/qgraphicsitem.h>
#include <QtGui/qevent.h>
#include <QtGui/qtextdocument.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT EditableAxisLabel : public QGraphicsTextItem
{
    Q_OBJECT
public:
    EditableAxisLabel(QGraphicsItem *parent = nullptr);

    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    bool sceneEvent(QEvent *event) override;
    void setEditable(bool editable);
    void reloadBeforeEditContent();

    QRectF boundingRect() const override;

protected:
    QString m_htmlBeforeEdit;
    bool m_editing = false;
    bool m_editable = false;

    virtual void setInitialEditValue() = 0;
    virtual void finishEditing() = 0;
    virtual void resetBeforeEditValue() = 0;

    bool isEditEndingKeyPress(QKeyEvent *event);
};

QT_END_NAMESPACE

#endif // EDITABLEAXISLABEL_P_H
