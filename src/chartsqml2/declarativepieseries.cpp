// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "declarativepieseries_p.h"
#include <QtCharts/QPieSlice>
#include <QtCharts/QVPieModelMapper>
#include <QtCharts/QHPieModelMapper>

QT_BEGIN_NAMESPACE

DeclarativePieSlice::DeclarativePieSlice(QObject *parent)
    : QPieSlice(parent)
{
    connect(this, SIGNAL(brushChanged()), this, SLOT(handleBrushChanged()));
}

QString DeclarativePieSlice::brushFilename() const
{
    return m_brushFilename;
}

void DeclarativePieSlice::setBrushFilename(const QString &brushFilename)
{
    QImage brushImage(brushFilename);
    if (QPieSlice::brush().textureImage() != brushImage) {
        QBrush brush = QPieSlice::brush();
        brush.setTextureImage(brushImage);
        QPieSlice::setBrush(brush);
        m_brushFilename = brushFilename;
        m_brushImage = brushImage;
        emit brushFilenameChanged(brushFilename);
    }
}

void DeclarativePieSlice::handleBrushChanged()
{
    // If the texture image of the brush has changed along the brush
    // the brush file name needs to be cleared.
    if (!m_brushFilename.isEmpty() && QPieSlice::brush().textureImage() != m_brushImage) {
        m_brushFilename.clear();
        emit brushFilenameChanged(QString());
    }
}

// Declarative pie series =========================================================================
DeclarativePieSeries::DeclarativePieSeries(QQuickItem *parent) :
    QPieSeries(parent)
{
    connect(this, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleAdded(QList<QPieSlice*>)));
    connect(this, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleRemoved(QList<QPieSlice*>)));
}

void DeclarativePieSeries::classBegin()
{
}

void DeclarativePieSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<QPieSlice *>(child)) {
            QPieSeries::append(qobject_cast<QPieSlice *>(child));
        } else if (qobject_cast<QVPieModelMapper *>(child)) {
            QVPieModelMapper *mapper = qobject_cast<QVPieModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHPieModelMapper *>(child)) {
            QHPieModelMapper *mapper = qobject_cast<QHPieModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QQmlListProperty<QObject> DeclarativePieSeries::seriesChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativePieSeries::appendSeriesChildren ,0,0,0);
}

void DeclarativePieSeries::appendSeriesChildren(QQmlListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

QPieSlice *DeclarativePieSeries::at(int index)
{
    QList<QPieSlice *> sliceList = slices();
    if (index >= 0 && index < sliceList.size())
        return sliceList[index];

    return 0;
}

QPieSlice *DeclarativePieSeries::find(QString label)
{
    foreach (QPieSlice *slice, slices()) {
        if (slice->label() == label)
            return slice;
    }
    return 0;
}

DeclarativePieSlice *DeclarativePieSeries::append(QString label, qreal value)
{
    DeclarativePieSlice *slice = new DeclarativePieSlice(this);
    slice->setLabel(label);
    slice->setValue(value);
    if (QPieSeries::append(slice))
        return slice;
    delete slice;
    return 0;
}

bool DeclarativePieSeries::remove(QPieSlice *slice)
{
    return QPieSeries::remove(slice);
}

void DeclarativePieSeries::clear()
{
    QPieSeries::clear();
}

void DeclarativePieSeries::handleAdded(const QList<QPieSlice *> &slices)
{
    for (auto *slice : slices)
        emit sliceAdded(slice);
}

void DeclarativePieSeries::handleRemoved(const QList<QPieSlice *> &slices)
{
    for (auto *slice : slices)
        emit sliceRemoved(slice);
}

QT_END_NAMESPACE

#include "moc_declarativepieseries_p.cpp"
