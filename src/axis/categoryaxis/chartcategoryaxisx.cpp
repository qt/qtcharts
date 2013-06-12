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

#include "chartcategoryaxisx_p.h"
#include "qcategoryaxis.h"
#include "qabstractaxis.h"
#include "chartpresenter_p.h"
#include "abstractchartlayout_p.h"
#include <QGraphicsLayout>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartCategoryAxisX::ChartCategoryAxisX(QCategoryAxis *axis, QGraphicsItem* item)
    : HorizontalAxis(axis, item, true),
      m_axis(axis)
{
    QObject::connect(axis, SIGNAL(categoriesChanged()), this, SLOT(handleCategoriesChanged()));
}

ChartCategoryAxisX::~ChartCategoryAxisX()
{
}

QVector<qreal> ChartCategoryAxisX::calculateLayout() const
{
    int tickCount = m_axis->categoriesLabels().count() + 1;
    QVector<qreal> points;

    if (tickCount < 2)
        return points;

    const QRectF &gridRect = gridGeometry();
    qreal range  = max() - min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = gridRect.width() / range;
        for (int i = 0; i < tickCount; ++i) {
            if (i < tickCount - 1) {
                qreal x = (m_axis->startValue(m_axis->categoriesLabels().at(i)) - min()) * scale + gridRect.left();
                points[i] = x;
            } else {
                qreal x = (m_axis->endValue(m_axis->categoriesLabels().at(i - 1)) - min())  * scale + gridRect.left();
                points[i] = x;
            }
        }
    }

    return points;
}

void ChartCategoryAxisX::updateGeometry()
{
    //TODO: this is not optimal when many categories :( , create only visible lables
    setLabels(m_axis->categoriesLabels() << "");
    HorizontalAxis::updateGeometry();
}

QSizeF ChartCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QSizeF sh;
    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_axis->categoriesLabels();
    qreal width = 0; // Width is irrelevant for X axes with interval labels
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(), "...", axis()->labelsAngle());
        height = boundingRect.height() + labelPadding() + base.height() + 1.0;
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        qreal labelHeight = 0.0;
        foreach (const QString& s, ticksList) {
            QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
            labelHeight = qMax(rect.height(), labelHeight);
        }
        height = labelHeight + labelPadding() + base.height() + 1.0;
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }

    return sh;
}

void ChartCategoryAxisX::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

#include "moc_chartcategoryaxisx_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
