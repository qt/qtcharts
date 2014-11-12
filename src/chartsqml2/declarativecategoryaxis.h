/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef DECLARATIVECATEGORYAXIS_H
#define DECLARATIVECATEGORYAXIS_H

#include <QtCharts/QCategoryAxis>

#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>

QT_CHARTS_BEGIN_NAMESPACE

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

class DeclarativeCategoryAxis : public QCategoryAxis, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QQmlListProperty<QObject> axisChildren READ axisChildren)
    Q_CLASSINFO("DefaultProperty", "axisChildren")

public:
    explicit DeclarativeCategoryAxis(QObject *parent = 0);
    QQmlListProperty<QObject> axisChildren();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

public Q_SLOTS:
    Q_INVOKABLE void append(const QString &label, qreal categoryEndValue);
    Q_INVOKABLE void remove(const QString &label);
    Q_INVOKABLE void replace(const QString &oldLabel, const QString &newLabel);
    static void appendAxisChildren(QQmlListProperty<QObject> *list, QObject *element);

private:
    static bool endValueLessThan(const QPair<QString, qreal> &value1, const QPair<QString, qreal> &value2);
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVECATEGORYAXIS_H
