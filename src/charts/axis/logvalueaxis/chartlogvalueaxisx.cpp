/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/chartlogvalueaxisx_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/QLogValueAxis>
#include <private/abstractchartlayout_p.h>
#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

ChartLogValueAxisX::ChartLogValueAxisX(QLogValueAxis *axis, QGraphicsItem *item)
    : HorizontalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(baseChanged(qreal)), this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(m_axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
}

ChartLogValueAxisX::~ChartLogValueAxisX()
{
}

QVector<qreal> ChartLogValueAxisX::calculateLayout() const
{
    QVector<qreal> points;

    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    qreal leftEdge = logMin < logMax ? logMin : logMax;
    qreal ceilEdge = ceil(leftEdge);
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));

    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaX = gridRect.width() / qAbs(logMax - logMin);
    for (int i = 0; i < tickCount; ++i)
        points[i] = (ceilEdge + qreal(i)) * deltaX - leftEdge * deltaX + gridRect.left();

    return points;
}

void ChartLogValueAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxisElement::layout();
    setLabels(createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), layout.size(), m_axis->labelFormat()));
    HorizontalAxis::updateGeometry();
}

void ChartLogValueAxisX::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

void ChartLogValueAxisX::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartLogValueAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QSizeF sh;

    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList;
    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));
    if (m_axis->max() > m_axis->min() && tickCount > 0)
        ticksList = createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), tickCount, m_axis->labelFormat());
    else
        ticksList.append(QStringLiteral(" "));
    // Width of horizontal axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base width is irrelevant.
    qreal width = 0;
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize:{
        QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                               QStringLiteral("..."),
                                                               axis()->labelsAngle());
        width = boundingRect.width() / 2.0;
        height = boundingRect.height() + labelPadding() + base.height() + 1.0;
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        qreal labelHeight = 0.0;
        qreal firstWidth = -1.0;
        foreach (const QString& s, ticksList) {
            QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
            labelHeight = qMax(rect.height(), labelHeight);
            width = rect.width();
            if (firstWidth < 0.0)
                firstWidth = width;
        }
        height = labelHeight + labelPadding() + base.height() + 1.0;
        width = qMax(width, firstWidth) / 2.0;
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }

    return sh;
}

#include "moc_chartlogvalueaxisx_p.cpp"

QT_CHARTS_END_NAMESPACE
