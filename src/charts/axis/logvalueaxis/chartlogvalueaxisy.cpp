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

#include <private/chartlogvalueaxisy_p.h>
#include <private/chartpresenter_p.h>
#include <QtCharts/QLogValueAxis>
#include <private/abstractchartlayout_p.h>
#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

ChartLogValueAxisY::ChartLogValueAxisY(QLogValueAxis *axis, QGraphicsItem *item)
    : VerticalAxis(axis, item),
      m_axis(axis)
{
    QObject::connect(m_axis, SIGNAL(baseChanged(qreal)), this, SLOT(handleBaseChanged(qreal)));
    QObject::connect(m_axis, SIGNAL(labelFormatChanged(QString)), this, SLOT(handleLabelFormatChanged(QString)));
}

ChartLogValueAxisY::~ChartLogValueAxisY()
{
}

QVector<qreal> ChartLogValueAxisY::calculateLayout() const
{
    QVector<qreal> points;
    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    qreal leftEdge = logMin < logMax ? logMin : logMax;
    qreal ceilEdge = ceil(leftEdge);
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));

    points.resize(tickCount);
    const QRectF &gridRect = gridGeometry();
    const qreal deltaY = gridRect.height() / qAbs(logMax - logMin);
    for (int i = 0; i < tickCount; ++i)
        points[i] = (ceilEdge + qreal(i)) * -deltaY - leftEdge * -deltaY + gridRect.bottom();

    return points;
}


void ChartLogValueAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxisElement::layout();
    setLabels(createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), layout.size(), m_axis->labelFormat()));
    VerticalAxis::updateGeometry();
}

void ChartLogValueAxisY::handleBaseChanged(qreal base)
{
    Q_UNUSED(base);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

void ChartLogValueAxisY::handleLabelFormatChanged(const QString &format)
{
    Q_UNUSED(format);
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartLogValueAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QSizeF sh;

    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList;
    qreal logMax = log10(m_axis->max()) / log10(m_axis->base());
    qreal logMin = log10(m_axis->min()) / log10(m_axis->base());
    int tickCount = qAbs(ceil(logMax) - ceil(logMin));
    if (m_axis->max() > m_axis->min() && tickCount > 0)
        ticksList = createLogValueLabels(m_axis->min(), m_axis->max(), m_axis->base(), tickCount, m_axis->labelFormat());
    else
        ticksList.append(QStringLiteral(" "));
    qreal width = 0;
    // Height of vertical axis sizeHint indicates the maximum distance labels can extend past
    // first and last ticks. Base height is irrelevant.
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                               QStringLiteral("..."),
                                                               axis()->labelsAngle());
        width = boundingRect.width() + labelPadding() + base.width() + 1.0;
        height = boundingRect.height() / 2.0;
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        qreal labelWidth = 0.0;
        qreal firstHeight = -1.0;
        foreach (const QString& s, ticksList) {
            QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
            labelWidth = qMax(rect.width(), labelWidth);
            height = rect.height();
            if (firstHeight < 0.0)
                firstHeight = height;
        }
        width = labelWidth + labelPadding() + base.width() + 2.0; //two pixels of tolerance
        height = qMax(height, firstHeight) / 2.0;
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }

    return sh;
}

#include "moc_chartlogvalueaxisy_p.cpp"

QT_CHARTS_END_NAMESPACE
