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

#ifndef DECLARATIVECANDLESTICKSERIES_H
#define DECLARATIVECANDLESTICKSERIES_H

#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QCandlestickSet>
#include <QtQml/QQmlParserStatus>
#include <QtQuick/QQuickItem>
#include <private/declarativechartglobal_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class DeclarativeAxes;
class QAbstractAxis;

class Q_QMLCHARTS_PRIVATE_EXPORT DeclarativeCandlestickSet : public QCandlestickSet
{
    Q_OBJECT
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged)

public:
    explicit DeclarativeCandlestickSet(qreal timestamp = 0.0, QObject *parent = nullptr);
    void setBrushFilename(const QString &brushFilename);
    QString brushFilename() const;

Q_SIGNALS:
    void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class DeclarativeCandlestickSeries : public QCandlestickSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QtCharts::QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeCandlestickSeries(QQuickItem *parent = nullptr);
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    QQmlListProperty<QObject> seriesChildren();
    void setBrushFilename(const QString &brushFilename);
    QString brushFilename() const;

public:
    Q_INVOKABLE DeclarativeCandlestickSet *at(int index);
    Q_INVOKABLE bool append(DeclarativeCandlestickSet *set);
    Q_INVOKABLE bool remove(DeclarativeCandlestickSet *set);
    Q_INVOKABLE bool append(qreal open, qreal high, qreal low, qreal close, qreal timestamp);
    Q_INVOKABLE bool remove(qreal timestamp);
    Q_INVOKABLE bool insert(int index, DeclarativeCandlestickSet *set);
    Q_INVOKABLE void clear();

public: // from QDeclarativeParserStatus
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);
    void axisXTopChanged(QAbstractAxis *axis);
    void axisYRightChanged(QAbstractAxis *axis);
    void clicked(DeclarativeCandlestickSet *set);
    void hovered(bool status, DeclarativeCandlestickSet *set);
    void pressed(DeclarativeCandlestickSet *set);
    void released(DeclarativeCandlestickSet *set);
    void doubleClicked(DeclarativeCandlestickSet *set);
    void brushFilenameChanged(const QString &brushFilename);

public Q_SLOTS:
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);
    void onClicked(QCandlestickSet *set);
    void onHovered(bool status, QCandlestickSet *set);
    void onPressed(QCandlestickSet *set);
    void onReleased(QCandlestickSet *set);
    void onDoubleClicked(QCandlestickSet *set);

private Q_SLOTS:
    void handleBrushChanged();

public:
    DeclarativeAxes *m_axes;

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

QT_CHARTS_END_NAMESPACE

#endif // DECLARATIVECANDLESTICKSERIES_H
