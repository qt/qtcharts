/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#ifndef DECLARATIVE_AXIS_H
#define DECLARATIVE_AXIS_H

#include "qchartglobal.h"
#include <QAxis>
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeAxis: public QAxis, public QDeclarativeParserStatus
{
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_OBJECT
    Q_PROPERTY(AxisRole role READ role WRITE setRole /*NOTIFY roleChanged*/)
    Q_ENUMS(AxisRole)

public:
    enum AxisRole {
        RoleX = 0,
        RoleY
    };

public:
    explicit DeclarativeAxis(QObject *parent = 0);

public: // from QDeclarativeParserStatus
    virtual void classBegin();
    virtual void componentComplete();

public:
    void setRole(AxisRole role);
    AxisRole role() { return m_role; }
    AxisRole m_role;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_AXIS_H
