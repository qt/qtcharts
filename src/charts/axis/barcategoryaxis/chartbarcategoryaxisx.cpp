// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartbarcategoryaxisx_p.h>
#include <private/chartpresenter_p.h>
#include <private/qbarcategoryaxis_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCore/QDebug>
#include <QtCore/QtMath>

QT_BEGIN_NAMESPACE

ChartBarCategoryAxisX::ChartBarCategoryAxisX(QBarCategoryAxis *axis, QGraphicsItem* item)
    : HorizontalAxis(axis, item, true),
      m_categoriesAxis(axis)
{
    QObject::connect(m_categoriesAxis,SIGNAL(categoriesChanged()),this, SLOT(handleCategoriesChanged()));
    handleCategoriesChanged();
}

ChartBarCategoryAxisX::~ChartBarCategoryAxisX()
{
}

QList<qreal> ChartBarCategoryAxisX::calculateLayout() const
{
    QList<qreal> points;
    const QRectF& gridRect = gridGeometry();
    qreal range = max() - min();
    const qreal delta = gridRect.width() / range;

    if (delta < 2)
        return points;

    qreal adjustedMin = min() + 0.5;
    qreal offset = (qRound(adjustedMin) - adjustedMin) * delta;

    int count = qFloor(range);
    if (count < 1)
        return points;

    points.resize(count + 2);

    for (int i = 0; i < count + 2; ++i)
        points[i] = offset + (qreal(i) * delta) + gridRect.left();

    return points;
}

QStringList ChartBarCategoryAxisX::createCategoryLabels(const QList<qreal> &layout) const
{
    QStringList result ;
    const QRectF &gridRect = gridGeometry();
    const qreal d = (max() - min()) / gridRect.width();

    for (int i = 0; i < layout.size() - 1; ++i) {
        int x = qFloor((((layout[i] + layout[i + 1]) / 2 - gridRect.left()) * d + min() + 0.5));
        if (x < max() && (x >= 0) && x < m_categoriesAxis->categories().size()) {
            result << m_categoriesAxis->categories().at(x);
        } else {
            // No label for x coordinate
            result << QString();
        }
    }
    result << QString();
    return result;
}


void ChartBarCategoryAxisX::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;
    setLabels(createCategoryLabels(layout));
    HorizontalAxis::updateGeometry();
}

void ChartBarCategoryAxisX::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartBarCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;
    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_categoriesAxis->categories();

    qreal width = 0; // Width is irrelevant for X axes with interval labels
    qreal height = 0;

    switch (which) {
    case Qt::MinimumSize: {
        if (labelsVisible()) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            height = boundingRect.height() + labelPadding() + base.height() + 1.0;
        } else {
            height = base.height() + 1.0;
        }
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize:{
        if (labelsVisible()) {
            qreal labelHeight = 0.0;
            foreach (const QString& s, ticksList) {
                QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                labelHeight = qMax(rect.height(), labelHeight);
            }
            height = labelHeight + labelPadding() + base.height() + 1.0;
        } else {
            height = base.height() + 1.0;
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

#include "moc_chartbarcategoryaxisx_p.cpp"
