// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "declarativebarseries_p.h"
#include <QtCharts/QBarSet>
#include <QtCharts/QVBarModelMapper>
#include <QtCharts/QHBarModelMapper>

QT_BEGIN_NAMESPACE

DeclarativeBarSet::DeclarativeBarSet(QObject *parent) : QBarSet(QString(), parent)
{
    connect(this, SIGNAL(valuesAdded(int,int)), this, SLOT(handleCountChanged(int,int)));
    connect(this, SIGNAL(valuesRemoved(int,int)), this, SLOT(handleCountChanged(int,int)));
    connect(this, SIGNAL(brushChanged()), this, SLOT(handleBrushChanged()));
}

void DeclarativeBarSet::handleCountChanged(int index, int count)
{
    Q_UNUSED(index);
    Q_UNUSED(count);
    emit countChanged(QBarSet::count());
}

qreal DeclarativeBarSet::borderWidth() const
{
    return pen().widthF();
}

void DeclarativeBarSet::setBorderWidth(qreal width)
{
    if (width != pen().widthF()) {
        QPen p = pen();
        p.setWidthF(width);
        setPen(p);
        emit borderWidthChanged(width);
    }
}

QVariantList DeclarativeBarSet::values()
{
    QVariantList values;
    for (int i(0); i < count(); i++)
        values.append(QVariant(QBarSet::at(i)));
    return values;
}

void DeclarativeBarSet::setValues(QVariantList values)
{
    while (count())
        remove(count() - 1);

    if (values.size() > 0 && values.at(0).canConvert<QPoint>()) {
        // Create list of values for appending if the first item is Qt.point
        int maxValue = 0;
        for (int i = 0; i < values.size(); i++) {
            if (values.at(i).canConvert<QPoint>() &&
                    values.at(i).toPoint().x() > maxValue) {
                maxValue = values.at(i).toPoint().x();
            }
        }

        QList<qreal> indexValueList;
        indexValueList.resize(maxValue + 1);

        for (int i = 0; i < values.size(); i++) {
            if (values.at(i).canConvert<QPoint>()) {
                indexValueList.replace(values.at(i).toPoint().x(), values.at(i).toPointF().y());
            }
        }

        for (int i = 0; i < indexValueList.size(); i++)
            QBarSet::append(indexValueList.at(i));

    } else {
        for (int i(0); i < values.size(); i++) {
            if (values.at(i).canConvert<double>())
                QBarSet::append(values[i].toDouble());
        }
    }
}

QString DeclarativeBarSet::brushFilename() const
{
    return m_brushFilename;
}

void DeclarativeBarSet::setBrushFilename(const QString &brushFilename)
{
    QImage brushImage(brushFilename);
    if (QBarSet::brush().textureImage() != brushImage) {
        QBrush brush = QBarSet::brush();
        brush.setTextureImage(brushImage);
        QBarSet::setBrush(brush);
        m_brushFilename = brushFilename;
        m_brushImage = brushImage;
        emit brushFilenameChanged(brushFilename);
    }
}

void DeclarativeBarSet::handleBrushChanged()
{
    // If the texture image of the brush has changed along the brush
    // the brush file name needs to be cleared.
    if (!m_brushFilename.isEmpty() && QBarSet::brush().textureImage() != m_brushImage) {
        m_brushFilename.clear();
        emit brushFilenameChanged(QString());
    }
}

// Declarative bar series ======================================================================================
DeclarativeBarSeries::DeclarativeBarSeries(QQuickItem *parent) :
    QBarSeries(parent),
    m_axes(new DeclarativeAxes(this))
{
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
}

void DeclarativeBarSeries::classBegin()
{
}

void DeclarativeBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if (qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativeBarSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativeBarSeries::appendSeriesChildren(QQmlListProperty<QObject> *list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeBarSeries::at(int index)
{
    QList<QBarSet *> setList = barSets();
    if (index >= 0 && index < setList.size())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative stacked bar series ==============================================================================
DeclarativeStackedBarSeries::DeclarativeStackedBarSeries(QQuickItem *parent) :
    QStackedBarSeries(parent),
    m_axes(0)
{
    m_axes = new DeclarativeAxes(this);
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
}

void DeclarativeStackedBarSeries::classBegin()
{
}

void DeclarativeStackedBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if (qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}


QQmlListProperty<QObject> DeclarativeStackedBarSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativeStackedBarSeries::appendSeriesChildren(QQmlListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeStackedBarSeries::at(int index)
{
    QList<QBarSet *> setList = barSets();
    if (index >= 0 && index < setList.size())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeStackedBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QStackedBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative percent bar series ==============================================================================
DeclarativePercentBarSeries::DeclarativePercentBarSeries(QQuickItem *parent) :
    QPercentBarSeries(parent),
    m_axes(0)
{
    m_axes = new DeclarativeAxes(this);
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
}

void DeclarativePercentBarSeries::classBegin()
{
}

void DeclarativePercentBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if (qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativePercentBarSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeBarSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativePercentBarSeries::appendSeriesChildren(QQmlListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativePercentBarSeries::at(int index)
{
    QList<QBarSet *> setList = barSets();
    if (index >= 0 && index < setList.size())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativePercentBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QPercentBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative horizontal bar series ===========================================================================
DeclarativeHorizontalBarSeries::DeclarativeHorizontalBarSeries(QQuickItem *parent) :
    QHorizontalBarSeries(parent),
    m_axes(0)
{
    m_axes = new DeclarativeAxes(this);
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
}

void DeclarativeHorizontalBarSeries::classBegin()
{
}

void DeclarativeHorizontalBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if (qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativeHorizontalBarSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeHorizontalBarSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativeHorizontalBarSeries::appendSeriesChildren(QQmlListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeHorizontalBarSeries::at(int index)
{
    QList<QBarSet *> setList = barSets();
    if (index >= 0 && index < setList.size())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeHorizontalBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QHorizontalBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative horizontal stacked bar series ===================================================================
DeclarativeHorizontalStackedBarSeries::DeclarativeHorizontalStackedBarSeries(QQuickItem *parent) :
    QHorizontalStackedBarSeries(parent),
    m_axes(0)
{
    m_axes = new DeclarativeAxes(this);
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
}

void DeclarativeHorizontalStackedBarSeries::classBegin()
{
}

void DeclarativeHorizontalStackedBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if (qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativeHorizontalStackedBarSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeHorizontalStackedBarSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativeHorizontalStackedBarSeries::appendSeriesChildren(QQmlListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeHorizontalStackedBarSeries::at(int index)
{
    QList<QBarSet *> setList = barSets();
    if (index >= 0 && index < setList.size())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeHorizontalStackedBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QHorizontalStackedBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

// Declarative horizontal percent bar series ===================================================================
DeclarativeHorizontalPercentBarSeries::DeclarativeHorizontalPercentBarSeries(QQuickItem *parent) :
    QHorizontalPercentBarSeries(parent),
    m_axes(0)
{
    m_axes = new DeclarativeAxes(this);
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
}

void DeclarativeHorizontalPercentBarSeries::classBegin()
{
}

void DeclarativeHorizontalPercentBarSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBarSet *>(child)) {
            QAbstractBarSeries::append(qobject_cast<DeclarativeBarSet *>(child));
        } else if (qobject_cast<QVBarModelMapper *>(child)) {
            QVBarModelMapper *mapper = qobject_cast<QVBarModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHBarModelMapper *>(child)) {
            QHBarModelMapper *mapper = qobject_cast<QHBarModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativeHorizontalPercentBarSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeHorizontalPercentBarSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativeHorizontalPercentBarSeries::appendSeriesChildren(QQmlListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBarSet *DeclarativeHorizontalPercentBarSeries::at(int index)
{
    QList<QBarSet *> setList = barSets();
    if (index >= 0 && index < setList.size())
        return qobject_cast<DeclarativeBarSet *>(setList[index]);

    return 0;
}

DeclarativeBarSet *DeclarativeHorizontalPercentBarSeries::insert(int index, QString label, QVariantList values)
{
    DeclarativeBarSet *barset = new DeclarativeBarSet(this);
    barset->setLabel(label);
    barset->setValues(values);
    if (QHorizontalPercentBarSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

QT_END_NAMESPACE

#include "moc_declarativebarseries_p.cpp"
