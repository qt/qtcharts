// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartcategoryaxisy_p.h>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QAbstractAxis>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtWidgets/QGraphicsLayout>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

ChartCategoryAxisY::ChartCategoryAxisY(QCategoryAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item, true),
      m_axis(axis)
{
    QObject::connect(axis, SIGNAL(categoriesChanged()), this, SLOT(handleCategoriesChanged()));
}

ChartCategoryAxisY::~ChartCategoryAxisY()
{
}

QList<qreal> ChartCategoryAxisY::calculateLayout() const
{
    int tickCount = m_axis->categoriesLabels().size() + 1;
    QList<qreal> points;

    if (tickCount < 2)
        return points;

    const QRectF &gridRect = gridGeometry();
    qreal range = max() - min();
    if (range > 0) {
        points.resize(tickCount);
        qreal scale = gridRect.height() / range;
        for (int i = 0; i < tickCount; ++i) {
            if (i < tickCount - 1) {
                qreal y = -(m_axis->startValue(m_axis->categoriesLabels().at(i)) - min()) * scale + gridRect.bottom();
                points[i] = y;
            } else {
                qreal y = -(m_axis->endValue(m_axis->categoriesLabels().at(i - 1)) - min())  * scale + gridRect.bottom();
                points[i] = y;
            }
        }
    }

    return points;
}

void ChartCategoryAxisY::updateGeometry()
{
    setLabels(m_axis->categoriesLabels() << QString());
    VerticalAxis::updateGeometry();
}

QSizeF ChartCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;
    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_axis->categoriesLabels();
    qreal width = 0;
    qreal height = 0; // Height is irrelevant for Y axes with interval labels

    switch (which) {
    case Qt::MinimumSize: {
        if (labelsVisible()) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            width = boundingRect.width() + labelPadding() + base.width() + 1.0;
        } else {
            width = base.width() + 1.0;
        }
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize: {
        if (labelsVisible()) {
            qreal labelWidth = 0.0;
            foreach (const QString& s, ticksList) {
                QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                labelWidth = qMax(rect.width(), labelWidth);
            }
            width = labelWidth + labelPadding() + base.width() + 1.0;
        } else {
            width = base.width() + 1.0;
        }
        sh = QSizeF(width, height);
        break;
    }
    default:
        break;
    }
    return sh;
}

void ChartCategoryAxisY::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

QT_END_NAMESPACE

#include "moc_chartcategoryaxisy_p.cpp"
