/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
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

#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QScatterSeries>
#include <private/declarativechartglobal_p.h>
#include <private/declarativexyseries_p.h>
#include <private/declarativeaxes_p.h>

#include <QtQml/QQmlListProperty>
#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE

class Q_QMLCHARTS_PRIVATE_EXPORT DeclarativeScatterSeries : public QScatterSeries, public DeclarativeXySeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged REVISION(1, 1))
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged REVISION(1, 2))
    Q_PROPERTY(QAbstractAxis *axisAngular READ axisAngular WRITE setAxisAngular NOTIFY axisAngularChanged REVISION(1, 3))
    Q_PROPERTY(QAbstractAxis *axisRadial READ axisRadial WRITE setAxisRadial NOTIFY axisRadialChanged REVISION(1, 3))
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged REVISION(1, 1))
    Q_PROPERTY(QQmlListProperty<QObject> declarativeChildren READ declarativeChildren)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION(1, 4))
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush NOTIFY brushChanged REVISION(1, 4))
    Q_CLASSINFO("DefaultProperty", "declarativeChildren")
    QML_NAMED_ELEMENT(ScatterSeries)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeScatterSeries(QObject *parent = 0);
    QXYSeries *xySeries() override { return this; }
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
    QQmlListProperty<QObject> declarativeChildren();
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);
    void setBrush(const QBrush &brush) override;
    QBrush brush() const;

public: // from QDeclarativeParserStatus
    void classBegin() override { DeclarativeXySeries::classBegin(); }
    void componentComplete() override { DeclarativeXySeries::componentComplete(); }

public:
    Q_INVOKABLE void append(qreal x, qreal y) { DeclarativeXySeries::append(x, y); }
    Q_INVOKABLE void replace(qreal oldX, qreal oldY, qreal newX, qreal newY) { DeclarativeXySeries::replace(oldX, oldY, newX, newY); }
    Q_REVISION(1, 3) Q_INVOKABLE void replace(int index, qreal newX, qreal newY) { DeclarativeXySeries::replace(index, newX, newY); }
    Q_INVOKABLE void remove(qreal x, qreal y) { DeclarativeXySeries::remove(x, y); }
    Q_REVISION(1, 3) Q_INVOKABLE void remove(int index) { DeclarativeXySeries::remove(index); }
    Q_REVISION(2, 1) Q_INVOKABLE void removePoints(int index, int count) { DeclarativeXySeries::removePoints(index, count); }
    Q_INVOKABLE void insert(int index, qreal x, qreal y) { DeclarativeXySeries::insert(index, x, y); }
    Q_INVOKABLE void clear() { DeclarativeXySeries::clear(); }
    Q_INVOKABLE QPointF at(int index) { return DeclarativeXySeries::at(index); }

Q_SIGNALS:
    void countChanged(int count);
    Q_REVISION(1, 1) void axisXChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void axisYChanged(QAbstractAxis *axis);
    Q_REVISION(1, 1) void borderWidthChanged(qreal width);
    Q_REVISION(1, 2) void axisXTopChanged(QAbstractAxis *axis);
    Q_REVISION(1, 2) void axisYRightChanged(QAbstractAxis *axis);
    Q_REVISION(1, 3) void axisAngularChanged(QAbstractAxis *axis);
    Q_REVISION(1, 3) void axisRadialChanged(QAbstractAxis *axis);
    Q_REVISION(1, 4) void brushFilenameChanged(const QString &brushFilename);
    Q_REVISION(1, 4) void brushChanged();

public Q_SLOTS:
    static void appendDeclarativeChildren(QQmlListProperty<QObject> *list, QObject *element);
    void handleCountChanged(int index);

private Q_SLOTS:
    void handleBrushChanged();

public:
    DeclarativeAxes *m_axes;

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

QT_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
