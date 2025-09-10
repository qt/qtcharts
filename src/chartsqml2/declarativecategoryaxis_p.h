// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef DECLARATIVECATEGORYAXIS_H
#define DECLARATIVECATEGORYAXIS_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QCategoryAxis>
#include <private/declarativechartglobal_p.h>

#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeCategoryRange : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal endValue READ endValue WRITE setEndValue)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    QML_NAMED_ELEMENT(CategoryRange)
    QML_ADDED_IN_VERSION(1, 1)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeCategoryRange(QObject *parent = 0);
    qreal endValue() { return m_endValue; }
    void setEndValue(qreal endValue) { m_endValue = endValue; }
    QString label() { return m_label; }
    void setLabel(const QString &label);

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
    Q_PROPERTY(AxisLabelsPosition labelsPosition READ labelsPosition WRITE setLabelsPosition NOTIFY labelsPositionChanged REVISION(2, 1))
    Q_ENUMS(AxisLabelsPosition)
    QML_NAMED_ELEMENT(CategoryAxis)
    QML_ADDED_IN_VERSION(1, 1)
    QML_EXTRA_VERSION(2, 0)

public:
    // duplicating enums from QChart to make the QML api namings 1-to-1 with the C++ api
    enum AxisLabelsPosition {
        AxisLabelsPositionCenter = 0x0,
        AxisLabelsPositionOnValue = 0x1
    };

    explicit DeclarativeCategoryAxis(QObject *parent = 0);
    QQmlListProperty<QObject> axisChildren();


public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

public:
    AxisLabelsPosition labelsPosition() const;
    void setLabelsPosition(AxisLabelsPosition position);

Q_SIGNALS:
    Q_REVISION(2, 1) void labelsPositionChanged(AxisLabelsPosition position);

public Q_SLOTS:
    Q_INVOKABLE void append(const QString &label, qreal categoryEndValue);
    Q_INVOKABLE void remove(const QString &label);
    Q_INVOKABLE void replace(const QString &oldLabel, const QString &newLabel);

private:
    static bool endValueLessThan(const QPair<QString, qreal> &value1, const QPair<QString, qreal> &value2);

private:
    static void appendAxisChildren(QQmlListProperty<QObject> *list, QObject *element);

    AxisLabelsPosition m_labelsPosition;
};

QT_END_NAMESPACE

#endif // DECLARATIVECATEGORYAXIS_H
