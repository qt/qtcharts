/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DECLARATIVE_MARGINS_H
#define DECLARATIVE_MARGINS_H

#include "qchartglobal.h"
#include <QObject>
#include <QMargins>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeMargins : public QObject, public QMargins
{
    Q_OBJECT
    Q_PROPERTY(int top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(int bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(int left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(int right READ right WRITE setRight NOTIFY rightChanged)

public:
    explicit DeclarativeMargins(QObject *parent = 0);
    void setTop(int top);
    void setBottom(int bottom);
    void setLeft(int left);
    void setRight(int right);

Q_SIGNALS:
    void topChanged(int top, int bottom, int left, int right);
    void bottomChanged(int top, int bottom, int left, int right);
    void leftChanged(int top, int bottom, int left, int right);
    void rightChanged(int top, int bottom, int left, int right);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_MARGINS_H
