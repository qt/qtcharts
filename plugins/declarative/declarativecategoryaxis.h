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

#ifndef DECLARATIVECATEGORYAXIS_H
#define DECLARATIVECATEGORYAXIS_H

#include "qcategoryaxis.h"
#include "shared_defines.h"

#ifdef CHARTS_FOR_QUICK2
#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>
#else
#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative/QDeclarativeParserStatus>
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeCategoryRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal endValue READ endValue WRITE setEndValue)
    Q_PROPERTY(QString label READ label WRITE setLabel)

public:
    explicit DeclarativeCategoryRange(QObject *parent = 0);
    qreal endValue() { return m_endValue; }
    void setEndValue(qreal endValue) { m_endValue = endValue; }
    QString label() { return m_label; }
    void setLabel(QString label) { m_label = label; }

private:
    qreal m_endValue;
    QString m_label;
};

class DeclarativeCategoryAxis : public QCategoryAxis, public QDECLARATIVE_PARSER_STATUS
{
    Q_OBJECT
#ifdef CHARTS_FOR_QUICK2
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> axisChildren READ axisChildren)
#else
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QDeclarativeListProperty<QObject> axisChildren READ axisChildren)
#endif
    Q_CLASSINFO("DefaultProperty", "axisChildren")

public:
    explicit DeclarativeCategoryAxis(QObject *parent = 0);
    QDECLARATIVE_LIST_PROPERTY<QObject> axisChildren();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    Q_INVOKABLE void append(const QString &label, qreal categoryEndValue);
    Q_INVOKABLE void remove(const QString &label);
    Q_INVOKABLE void replace(const QString &oldLabel, const QString &newLabel);
    static void appendAxisChildren(QDECLARATIVE_LIST_PROPERTY<QObject> *list, QObject *element);

private:
    static bool endValueLessThan(const QPair<QString, qreal> &value1, const QPair<QString, qreal> &value2);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVECATEGORYAXIS_H
