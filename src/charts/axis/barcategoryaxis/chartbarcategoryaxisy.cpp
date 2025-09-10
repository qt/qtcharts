// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/chartbarcategoryaxisy_p.h>
#include <private/chartpresenter_p.h>
#include <private/qbarcategoryaxis_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

ChartBarCategoryAxisY::ChartBarCategoryAxisY(QBarCategoryAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item, true),
      m_categoriesAxis(axis)
{
    QObject::connect(m_categoriesAxis,SIGNAL(categoriesChanged()),this, SLOT(handleCategoriesChanged()));
    handleCategoriesChanged();
}

ChartBarCategoryAxisY::~ChartBarCategoryAxisY()
{
}

QList<qreal> ChartBarCategoryAxisY::calculateLayout() const
{
    QList<qreal> points;
    const QRectF& gridRect = gridGeometry();
    const qreal range = max() - min();
    const qreal delta = gridRect.height() / range;

    if (delta < 2)
        return points;

    const qreal adjustedMin = min() + 0.5;
    const qreal offset = (qRound(adjustedMin) - adjustedMin) * delta;

    int count = qFloor(range);
    if (count < 1)
        return points;

    points.resize(count + 2);

    for (int i = 0; i < count + 2; ++i)
        points[i] =  gridRect.bottom() - (qreal(i) * delta) - offset;

    return points;
}

QStringList ChartBarCategoryAxisY::createCategoryLabels(const QList<qreal> &layout) const
{
    QStringList result;
    const QRectF &gridRect = gridGeometry();
    const qreal d = (max() - min()) / gridRect.height();

    for (int i = 0; i < layout.size() - 1; ++i) {
        int x = qFloor(((gridRect.height() - (layout[i + 1] + layout[i]) / 2 + gridRect.top()) * d + min() + 0.5));
        if ((x < m_categoriesAxis->categories().size()) && (x >= 0)) {
            result << m_categoriesAxis->categories().at(x);
        } else {
            // No label for x coordinate
            result << QString();
        }
    }
    result << QString();
    return result;
}

void ChartBarCategoryAxisY::updateGeometry()
{
    const QList<qreal> &layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;
    setLabels(createCategoryLabels(layout));
    VerticalAxis::updateGeometry();
}

void ChartBarCategoryAxisY::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartBarCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;
    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    const QStringList ticksList = m_categoriesAxis->categories();
    qreal width = 0;
    qreal height = 0; // Height is irrelevant for Y axes with interval labels

    switch (which) {
    case Qt::MinimumSize: {
        if (labelsVisible()) {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            width = boundingRect.width() + labelPadding() + base.width() + 1.0;
            if (base.width() > 0.0)
                width += labelPadding();
        } else {
            width = base.width() + 1.0;
        }
        sh = QSizeF(width, height);
        break;
    }
    case Qt::PreferredSize:{
        if (labelsVisible()) {
            qreal labelWidth = 0.0;
            for (const QString &s : ticksList) {
                QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                labelWidth = qMax(rect.width(), labelWidth);
            }
            width = labelWidth + labelPadding() + base.width() + 1.0;
            if (base.width() > 0.0)
                width += labelPadding();
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

QT_END_NAMESPACE

#include "moc_chartbarcategoryaxisy_p.cpp"
