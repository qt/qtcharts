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

QT_CHARTS_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT EditableAxisLabel : public QGraphicsTextItem
{
    Q_OBJECT
public:
    EditableAxisLabel(QGraphicsItem *parent = nullptr);

    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    bool sceneEvent(QEvent *event);
    void setEditable(bool editable);
    void reloadBeforeEditContent();

    QRectF boundingRect() const;

protected:
    QString m_htmlBeforeEdit;
    bool m_editing = false;
    bool m_editable = false;

    virtual void setInitialEditValue() = 0;
    virtual void finishEditing() = 0;
    virtual void resetBeforeEditValue() = 0;

    bool isEditEndingKeyPress(QKeyEvent *event);
};

QT_CHARTS_END_NAMESPACE

#endif // EDITABLEAXISLABEL_P_H
