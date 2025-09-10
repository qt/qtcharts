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

#ifndef DECLARATIVEBOXPLOT_H
#define DECLARATIVEBOXPLOT_H

#include <QtQml/qqmlregistration.h>
#include <QtCharts/QBoxSet>
#include <private/declarativeaxes_p.h>
#include <QtCharts/QBoxPlotSeries>
#include <private/declarativechartglobal_p.h>

#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>

QT_BEGIN_NAMESPACE

class Q_CHARTSQML_EXPORT DeclarativeBoxSet : public QBoxSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION(1, 4))
    Q_ENUMS(ValuePositions)
    QML_NAMED_ELEMENT(BoxSet)
    QML_ADDED_IN_VERSION(1, 3)
    QML_EXTRA_VERSION(2, 0)

public: // duplicate from QBoxSet
    enum ValuePositions {
        LowerExtreme = 0x0,
        LowerQuartile,
        Median,
        UpperQuartile,
        UpperExtreme
    };

public:
    explicit DeclarativeBoxSet(const QString label = QString(), QObject *parent = 0);
    QVariantList values();
    void setValues(QVariantList values);
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

public: // From QBoxSet
    Q_INVOKABLE void append(qreal value) { QBoxSet::append(value); }
    Q_INVOKABLE void clear() {QBoxSet::clear(); }
    Q_INVOKABLE qreal at(int index) { return QBoxSet::at(index); }
    Q_INVOKABLE void setValue(int index, qreal value) { QBoxSet::setValue(index, value); }

Q_SIGNALS:
    void changedValues();
    void changedValue(int index);
    Q_REVISION(1, 4) void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class Q_CHARTSQML_EXPORT DeclarativeBoxPlotSeries : public QBoxPlotSeries, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION(1, 4))
    Q_CLASSINFO("DefaultProperty", "seriesChildren")
    QML_NAMED_ELEMENT(BoxPlotSeries)
    QML_ADDED_IN_VERSION(1, 3)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit DeclarativeBoxPlotSeries(QQuickItem *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QQmlListProperty<QObject> seriesChildren();
    QString brushFilename() const;
    void setBrushFilename(const QString &brushFilename);

public:
    Q_INVOKABLE DeclarativeBoxSet *at(int index);
    Q_INVOKABLE DeclarativeBoxSet *append(const QString label, QVariantList values) { return insert(count(), label, values); }
    Q_INVOKABLE void append(DeclarativeBoxSet *box) { QBoxPlotSeries::append(box); }
    Q_INVOKABLE DeclarativeBoxSet *insert(int index, const QString label, QVariantList values);
    Q_INVOKABLE bool remove(DeclarativeBoxSet *box) { return QBoxPlotSeries::remove(qobject_cast<QBoxSet *>(box)); }
    Q_INVOKABLE void clear() { return QBoxPlotSeries::clear(); }

public: // from QDeclarativeParserStatus
    void classBegin() override;
    void componentComplete() override;

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);
    void axisXTopChanged(QAbstractAxis *axis);
    void axisYRightChanged(QAbstractAxis *axis);
    void clicked(DeclarativeBoxSet *boxset);
    void hovered(bool status, DeclarativeBoxSet *boxset);
    void pressed(DeclarativeBoxSet *boxset);
    void released(DeclarativeBoxSet *boxset);
    void doubleClicked(DeclarativeBoxSet *boxset);
    Q_REVISION(1, 4) void brushFilenameChanged(const QString &brushFilename);

public Q_SLOTS:
    void onHovered(bool status, QBoxSet *boxset);
    void onClicked(QBoxSet *boxset);
    void onPressed(QBoxSet *boxset);
    void onReleased(QBoxSet *boxset);
    void onDoubleClicked(QBoxSet *boxset);

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

#endif // DECLARATIVEBOXPLOT_H
