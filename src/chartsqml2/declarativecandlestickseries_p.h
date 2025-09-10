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

#ifndef DECLARATIVECANDLESTICKSERIES_H
#define DECLARATIVECANDLESTICKSERIES_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QCandlestickSeries>
#include <QtCharts/qabstractaxis.h>
#include <QtCharts/QCandlestickSet>
#include <QtQml/QQmlParserStatus>
#include <QtQuick/QQuickItem>
#include <private/declarativechartglobal_p.h>

QT_BEGIN_NAMESPACE

class DeclarativeAxes;

class Q_CHARTSQML_EXPORT DeclarativeCandlestickSet : public QCandlestickSet
{
    Q_OBJECT
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged)
    QML_NAMED_ELEMENT(CandlestickSet)
    QML_ADDED_IN_VERSION(2, 2)

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
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(CandlestickSeries)
    QML_ADDED_IN_VERSION(2, 2)

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
    void classBegin() override;
    void componentComplete() override;

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
    static void appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element);

    QString m_brushFilename;
    QImage m_brushImage;
};

QT_END_NAMESPACE

#endif // DECLARATIVECANDLESTICKSERIES_H
