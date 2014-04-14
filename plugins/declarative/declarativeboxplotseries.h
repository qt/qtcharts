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

#ifndef DECLARATIVEBOXPLOT_H
#define DECLARATIVEBOXPLOT_H

#include "qboxset.h"
#include "declarativeaxes.h"
#include "qboxplotseries.h"
#ifdef CHARTS_FOR_QUICK2
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlParserStatus>
#else
#include <QtDeclarative/QDeclarativeItem>
#include <QtDeclarative/QDeclarativeParserStatus>
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeBoxSet : public QBoxSet
{
    Q_OBJECT
    Q_PROPERTY(QVariantList values READ values WRITE setValues)
    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION 1)
    Q_ENUMS(ValuePositions)

public: // duplicate from QBoxSet
    enum ValuePositions {
        LowerExtreme = 0x0,
        LowerQuartile,
        Median,
        UpperQuartile,
        UpperExtreme
    };

public:
    explicit DeclarativeBoxSet(const QString label = "", QObject *parent = 0);
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
    Q_REVISION(1) void brushFilenameChanged(const QString &brushFilename);

private Q_SLOTS:
    void handleBrushChanged();

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

class DeclarativeBoxPlotSeries : public QBoxPlotSeries, public QDECLARATIVE_PARSER_STATUS
{
    Q_OBJECT
#ifdef CHARTS_FOR_QUICK2
    Q_INTERFACES(QQmlParserStatus)
#else
    Q_INTERFACES(QDeclarativeParserStatus)
#endif
    Q_PROPERTY(QAbstractAxis *axisX READ axisX WRITE setAxisX NOTIFY axisXChanged)
    Q_PROPERTY(QAbstractAxis *axisY READ axisY WRITE setAxisY NOTIFY axisYChanged)
    Q_PROPERTY(QAbstractAxis *axisXTop READ axisXTop WRITE setAxisXTop NOTIFY axisXTopChanged)
    Q_PROPERTY(QAbstractAxis *axisYRight READ axisYRight WRITE setAxisYRight NOTIFY axisYRightChanged)
#ifdef CHARTS_FOR_QUICK2
    Q_PROPERTY(QQmlListProperty<QObject> seriesChildren READ seriesChildren)
#else
    Q_PROPERTY(QDeclarativeListProperty<QObject> seriesChildren READ seriesChildren)
#endif
    Q_PROPERTY(QString brushFilename READ brushFilename WRITE setBrushFilename NOTIFY brushFilenameChanged REVISION 1)
    Q_CLASSINFO("DefaultProperty", "seriesChildren")

public:
    explicit DeclarativeBoxPlotSeries(QDECLARATIVE_ITEM *parent = 0);
    QAbstractAxis *axisX() { return m_axes->axisX(); }
    void setAxisX(QAbstractAxis *axis) { m_axes->setAxisX(axis); }
    QAbstractAxis *axisY() { return m_axes->axisY(); }
    void setAxisY(QAbstractAxis *axis) { m_axes->setAxisY(axis); }
    QAbstractAxis *axisXTop() { return m_axes->axisXTop(); }
    void setAxisXTop(QAbstractAxis *axis) { m_axes->setAxisXTop(axis); }
    QAbstractAxis *axisYRight() { return m_axes->axisYRight(); }
    void setAxisYRight(QAbstractAxis *axis) { m_axes->setAxisYRight(axis); }
    QDECLARATIVE_LIST_PROPERTY<QObject> seriesChildren();
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
    void classBegin();
    void componentComplete();

Q_SIGNALS:
    void axisXChanged(QAbstractAxis *axis);
    void axisYChanged(QAbstractAxis *axis);
    void axisXTopChanged(QAbstractAxis *axis);
    void axisYRightChanged(QAbstractAxis *axis);
    void clicked(DeclarativeBoxSet *boxset);
    void hovered(bool status, DeclarativeBoxSet *boxset);
    Q_REVISION(1) void brushFilenameChanged(const QString &brushFilename);

public Q_SLOTS:
    static void appendSeriesChildren(QDECLARATIVE_LIST_PROPERTY<QObject> *list, QObject *element);
    void onHovered(bool status, QBoxSet *boxset);
    void onClicked(QBoxSet *boxset);

private Q_SLOTS:
    void handleBrushChanged();

public:
    DeclarativeAxes *m_axes;

private:
    QString m_brushFilename;
    QImage m_brushImage;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEBOXPLOT_H
