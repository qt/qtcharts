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

#ifndef DECLARATIVEAREASERIES_H
#define DECLARATIVEAREASERIES_H

#include <QtCharts/QAreaSeries>
#include <QtQml/qqmlregistration.h>
#include <private/declarativechartglobal_p.h>
#include <private/declarativeaxes_p.h>
#include <private/declarativelineseries_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeAreaSeries : public QAreaSeries
{
    Q_OBJECT
    Q_PROPERTY(DeclarativeLineSeries *upperSeries READ upperSeries WRITE setUpperSeries)
    Q_PROPERTY(DeclarativeLineSeries *lowerSeries READ lowerSeries WRITE setLowerSeries)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisAngular READ axisAngular WRITE setAxisAngular NOTIFY axisAngularChanged REVISION(1, 3))
    Q_PROPERTY(QAbstractAxis *axisRadial READ axisRadial WRITE setAxisRadial NOTIFY axisRadialChanged REVISION(1, 3))
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged REVISION(1, 1))
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION(1, 4))
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged REVISION(1, 4))
    QML_NAMED_ELEMENT(AreaSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeAreaSeries(QObject *parent = 0);
    void setUpperSeries(DeclarativeLineSeries *series);
    DeclarativeLineSeries *upperSeries() const;
    void setLowerSeries(DeclarativeLineSeries *series);
    DeclarativeLineSeries *lowerSeries() const;
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QAbstractAxis *axisAngular() { return m_axes->axisX(); }
    void setAxisAngular(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisRadial() { return m_axes->axisY(); }
    void setAxisRadial(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    qreal borderWidth() const;
    void setBorderWidth(qreal borderWidth);
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);
    void setBrush(const QBrush &brush);
    QBrush brush() const;

Q_SIGNALS:
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void borderWidthChanged(qreal width);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);
    Q_REVISION(1, 3) void axisAngularChanged(QAbstractAxis *axis);
    Q_REVISION(1, 3) void axisRadialChanged(QAbstractAxis *axis);
    Q_REVISION(1, 4) void brushChanged();
    Q_REVISION(1, 4) void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

public:
    DeclarativeAxes *m_axes;

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

QT_END_NAMESPACE

#endif // DECLARATIVEAREASERIES_H
