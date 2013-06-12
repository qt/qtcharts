/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DECLARATIVEMODEL_H
#define DECLARATIVEMODEL_H

#include "customtablemodel.h"
#include <QDeclarativeListProperty>
#include <QVariant>
#include <QDeclarativeParserStatus>

class DeclarativeTableModelElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)

public:
    explicit DeclarativeTableModelElement(QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);
private:
    QVariantList m_values;
};

class DeclarativeTableModel : public CustomTableModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QObject> modelChildren READ modelChildren)
    Q_PROPERTY(QStringList verticalHeaders READ verticalHeaders WRITE setVerticalHeaders)
    Q_CLASSINFO("DefaultProperty", "modelChildren")

public:
    explicit DeclarativeTableModel(QObject *parent = 0);
    QDeclarativeListProperty<QObject> modelChildren();
    void setVerticalHeaders(QStringList headers);
    QStringList verticalHeaders();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    void append(QVariantList slices);
    static void appendModelChild(QDeclarativeListProperty<QObject> *list,
                                 QObject *element);
};

#endif // DECLARATIVEMODEL_H
