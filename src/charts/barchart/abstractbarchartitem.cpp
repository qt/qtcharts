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

#include <private/abstractbarchartitem_p.h>
#include <private/bar_p.h>
#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>
#include <QtCharts/QAbstractBarSeries>
#include <private/qabstractbarseries_p.h>
#include <QtCharts/QChart>
#include <private/chartpresenter_p.h>
#include <private/charttheme_p.h>
#include <private/baranimation_p.h>

#include <private/chartdataset_p.h>
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>

QT_CHARTS_BEGIN_NAMESPACE

AbstractBarChartItem::AbstractBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    ChartItem(series->d_func(),item),
    m_animation(0),
    m_series(series)
{

    setFlag(ItemClipsChildrenToShape);
    setFlag(QGraphicsItem::ItemIsSelectable);
    connect(series->d_func(), SIGNAL(updatedLayout()), this, SLOT(handleLayoutChanged()));
    connect(series->d_func(), SIGNAL(updatedBars()), this, SLOT(handleUpdatedBars()));
    connect(series->d_func(), SIGNAL(labelsVisibleChanged(bool)), this, SLOT(handleLabelsVisibleChanged(bool)));
    connect(series->d_func(), SIGNAL(restructuredBars()), this, SLOT(handleDataStructureChanged()));
    connect(series, SIGNAL(visibleChanged()), this, SLOT(handleVisibleChanged()));
    connect(series, SIGNAL(opacityChanged()), this, SLOT(handleOpacityChanged()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(handleUpdatedBars()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(positionLabels()));
    connect(series, SIGNAL(labelsPositionChanged(QAbstractBarSeries::LabelsPosition)),
            this, SLOT(handleLabelsPositionChanged()));
    setZValue(ChartPresenter::BarSeriesZValue);
    handleDataStructureChanged();
    handleVisibleChanged();
    handleUpdatedBars();
}

AbstractBarChartItem::~AbstractBarChartItem()
{
}

void AbstractBarChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF AbstractBarChartItem::boundingRect() const
{
    return m_rect;
}

void AbstractBarChartItem::applyLayout(const QVector<QRectF> &layout)
{
    QSizeF size = geometry().size();
    if (geometry().size().isValid()) {
        if (m_animation) {
            if (m_layout.count() == 0 || m_oldSize != size) {
                initializeLayout();
                m_oldSize = size;
            }
            m_animation->setup(m_layout, layout);
            presenter()->startAnimation(m_animation);
        } else {
            setLayout(layout);
            update();
        }
    }
}

void AbstractBarChartItem::setAnimation(BarAnimation *animation)
{
    m_animation = animation;
}

void AbstractBarChartItem::setLayout(const QVector<QRectF> &layout)
{
    if (layout.count() != m_bars.count())
        return;

    m_layout = layout;

    for (int i = 0; i < m_bars.count(); i++)
        m_bars.at(i)->setRect(layout.at(i));

    positionLabels();
}
//handlers

void AbstractBarChartItem::handleDomainUpdated()
{
    m_domainMinX = domain()->minX();
    m_domainMaxX = domain()->maxX();
    m_domainMinY = domain()->minY();
    m_domainMaxY = domain()->maxY();

    QRectF rect(QPointF(0,0),domain()->size());

    if(m_rect != rect){
        prepareGeometryChange();
        m_rect = rect;
    }

    handleLayoutChanged();
}

void AbstractBarChartItem::handleLayoutChanged()
{
    if ((m_rect.width() <= 0) || (m_rect.height() <= 0))
        return; // rect size zero.
    QVector<QRectF> layout = calculateLayout();
    applyLayout(layout);
    handleUpdatedBars();
}

void AbstractBarChartItem::handleLabelsVisibleChanged(bool visible)
{
    foreach (QGraphicsTextItem *label, m_labels)
        label->setVisible(visible);
    update();
}

void AbstractBarChartItem::handleDataStructureChanged()
{
    foreach (QGraphicsItem *item, childItems())
        delete item;

    m_bars.clear();
    m_labels.clear();
    m_layout.clear();

    // Create new graphic items for bars
    for (int c = 0; c < m_series->d_func()->categoryCount(); c++) {
        for (int s = 0; s < m_series->count(); s++) {
            QBarSet *set = m_series->d_func()->barsetAt(s);

            // Bars
            Bar *bar = new Bar(set, c, this);
            m_bars.append(bar);
            connect(bar, SIGNAL(clicked(int,QBarSet*)), m_series, SIGNAL(clicked(int,QBarSet*)));
            connect(bar, SIGNAL(hovered(bool, int, QBarSet*)), m_series, SIGNAL(hovered(bool, int, QBarSet*)));
            connect(bar, SIGNAL(pressed(int, QBarSet*)), m_series, SIGNAL(pressed(int, QBarSet*)));
            connect(bar, SIGNAL(released(int, QBarSet*)),
                    m_series, SIGNAL(released(int, QBarSet*)));
            connect(bar, SIGNAL(doubleClicked(int, QBarSet*)),
                    m_series, SIGNAL(doubleClicked(int, QBarSet*)));
            connect(bar, SIGNAL(clicked(int,QBarSet*)), set, SIGNAL(clicked(int)));
            connect(bar, SIGNAL(hovered(bool, int, QBarSet*)), set, SIGNAL(hovered(bool, int)));
            connect(bar, SIGNAL(pressed(int, QBarSet*)), set, SIGNAL(pressed(int)));
            connect(bar, SIGNAL(released(int, QBarSet*)), set, SIGNAL(released(int)));
            connect(bar, SIGNAL(doubleClicked(int, QBarSet*)), set, SIGNAL(doubleClicked(int)));
            //            m_layout.append(QRectF(0, 0, 1, 1));

            // Labels
            QGraphicsTextItem *newLabel = new QGraphicsTextItem(this);
            newLabel->document()->setDocumentMargin(ChartPresenter::textMargin());
            m_labels.append(newLabel);
        }
    }

    if(themeManager()) themeManager()->updateSeries(m_series);
    handleLayoutChanged();
    handleVisibleChanged();
}

void AbstractBarChartItem::handleVisibleChanged()
{
    bool visible = m_series->isVisible();
    if (visible)
        handleLabelsVisibleChanged(m_series->isLabelsVisible());
    else
        handleLabelsVisibleChanged(visible);

    foreach (QGraphicsItem *bar, m_bars)
        bar->setVisible(visible);
}

void AbstractBarChartItem::handleOpacityChanged()
{
    foreach (QGraphicsItem *item, childItems())
        item->setOpacity(m_series->opacity());
}

void AbstractBarChartItem::handleUpdatedBars()
{
    if (!m_series->d_func()->blockBarUpdate()) {
        // Handle changes in pen, brush, labels etc.
        int categoryCount = m_series->d_func()->categoryCount();
        int setCount = m_series->count();
        int itemIndex(0);
        static const QString valueTag(QLatin1String("@value"));

        for (int category = 0; category < categoryCount; category++) {
            for (int set = 0; set < setCount; set++) {
                QBarSetPrivate *barSet = m_series->d_func()->barsetAt(set)->d_ptr.data();
                Bar *bar = m_bars.at(itemIndex);
                bar->setPen(barSet->m_pen);
                bar->setBrush(barSet->m_brush);
                bar->update();

                QGraphicsTextItem *label = m_labels.at(itemIndex);
                QString valueLabel;
                if (presenter()) { // At startup presenter is not yet set, yet somehow update comes
                    if (m_series->labelsFormat().isEmpty()) {
                        valueLabel = presenter()->numberToString(barSet->value(category));
                    } else {
                        valueLabel = m_series->labelsFormat();
                        valueLabel.replace(valueTag,
                                           presenter()->numberToString(barSet->value(category)));
                    }
                }
                label->setHtml(valueLabel);
                label->setFont(barSet->m_labelFont);
                label->setDefaultTextColor(barSet->m_labelBrush.color());
                label->update();
                itemIndex++;
            }
        }
    }
}

void AbstractBarChartItem::handleLabelsPositionChanged()
{
    positionLabels();
}

void AbstractBarChartItem::positionLabels()
{
    for (int i = 0; i < m_layout.count(); i++) {
        QGraphicsTextItem *label = m_labels.at(i);
        qreal xPos = 0;
        qreal yPos = m_layout.at(i).center().y() - label->boundingRect().center().y();

        int offset = m_bars.at(i)->pen().width() / 2 + 2;
        if (m_series->labelsPosition() == QAbstractBarSeries::LabelsCenter)
            xPos = m_layout.at(i).center().x() - label->boundingRect().center().x();
        else if (m_series->labelsPosition() == QAbstractBarSeries::LabelsInsideEnd)
            xPos = m_layout.at(i).right() - label->boundingRect().width() - offset;
        else if (m_series->labelsPosition() == QAbstractBarSeries::LabelsInsideBase)
            xPos = m_layout.at(i).left() + offset;
        else if (m_series->labelsPosition() == QAbstractBarSeries::LabelsOutsideEnd)
            xPos = m_layout.at(i).right() + offset;

        label->setPos(xPos, yPos);
        label->setZValue(zValue() + 1);
    }
}

#include "moc_abstractbarchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
