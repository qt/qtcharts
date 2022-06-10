// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/qlogvalueaxis.h>
#include <QtCore/qmath.h>
#include <QtWidgets/qgraphicslayout.h>
#include <private/abstractchartlayout_p.h>
#include <private/chartlogvalueaxisy_p.h>
#include <private/chartpresenter_p.h>

QT_BEGIN_NAMESPACE

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

QList<qreal> ChartLogValueAxisY::calculateLayout() const
{
    QList<qreal> points;
    points.resize(m_axis->tickCount());

    const qreal logMax = qLn(m_axis->max()) / qLn(m_axis->base());
    const qreal logMin = qLn(m_axis->min()) / qLn(m_axis->base());
    const qreal leftEdge = qMin(logMin, logMax);
    const qreal ceilEdge = std::ceil(leftEdge);

    const QRectF &gridRect = gridGeometry();
    const qreal deltaY = gridRect.height() / qAbs(logMax - logMin);
    for (int i = 0; i < m_axis->tickCount(); ++i)
        points[i] = (ceilEdge + qreal(i)) * -deltaY - leftEdge * -deltaY + gridRect.bottom();

    return points;
}


void ChartLogValueAxisY::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
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
    Q_UNUSED(constraint);

    const QSizeF base = VerticalAxis::sizeHint(which, constraint);
    const int tickCount = m_axis->tickCount();
    QStringList ticksList;
    QSizeF sh;

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
        if (labelsVisible()) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            width = boundingRect.width() + labelPadding() + base.width() + 1.0;
            height = boundingRect.height() / 2.0;
        } else {
            width = base.width() + 1.0;
            height = 0;
        }
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        if (labelsVisible()) {
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
        } else {
            width = base.width() + 2.0;
            height = 0;
        }
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }

    return sh;
}

QT_END_NAMESPACE

#include "moc_chartlogvalueaxisy_p.cpp"
