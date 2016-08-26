/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
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
#include <QtCore/QtMath>
#include <QtGui/QPainter>
#include <QtGui/QTextDocument>

QT_CHARTS_BEGIN_NAMESPACE

AbstractBarChartItem::AbstractBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item) :
    ChartItem(series->d_func(),item),
    m_animation(0),
    m_series(series),
    m_firstCategory(-1),
    m_lastCategory(-2),
    m_categoryCount(0),
    m_labelItemsMissing(false),
    m_orientation(Qt::Horizontal),
    m_resetAnimation(true)
{

    setFlag(ItemClipsChildrenToShape);
    setFlag(QGraphicsItem::ItemIsSelectable);
    connect(series->d_func(), SIGNAL(updatedLayout()), this, SLOT(handleLayoutChanged()));
    connect(series->d_func(), SIGNAL(updatedBars()), this, SLOT(handleUpdatedBars()));
    connect(series->d_func(), SIGNAL(labelsVisibleChanged(bool)), this, SLOT(handleLabelsVisibleChanged(bool)));
    connect(series->d_func(), SIGNAL(restructuredBars()), this, SLOT(handleDataStructureChanged()));
    connect(series->d_func(), &QAbstractBarSeriesPrivate::setValueChanged,
            this, &AbstractBarChartItem::handleBarValueChange);
    connect(series->d_func(), &QAbstractBarSeriesPrivate::setValueAdded,
            this, &AbstractBarChartItem::handleBarValueAdd);
    connect(series->d_func(), &QAbstractBarSeriesPrivate::setValueRemoved,
            this, &AbstractBarChartItem::handleBarValueRemove);
    connect(series, SIGNAL(visibleChanged()), this, SLOT(handleVisibleChanged()));
    connect(series, SIGNAL(opacityChanged()), this, SLOT(handleOpacityChanged()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(handleUpdatedBars()));
    connect(series, SIGNAL(labelsFormatChanged(QString)), this, SLOT(positionLabels()));
    connect(series, SIGNAL(labelsPositionChanged(QAbstractBarSeries::LabelsPosition)),
            this, SLOT(handleLabelsPositionChanged()));
    connect(series, SIGNAL(labelsAngleChanged(qreal)), this, SLOT(positionLabels()));
    setZValue(ChartPresenter::BarSeriesZValue);
    handleDataStructureChanged();
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

void AbstractBarChartItem::initializeFullLayout()
{
    qreal setCount = m_series->count();

    int index = 0;
    for (int set = 0; set < setCount; set++) {
        QBarSet *barSet = m_series->barSets().at(set);
        const QList<Bar *> bars = m_barMap.value(barSet);
        for (int category = 0; category < m_categoryCount; category++)
            initializeLayout(set, bars.at(category)->index(), index++, true);
    }
}

void AbstractBarChartItem::applyLayout(const QVector<QRectF> &layout)
{
    QSizeF size = geometry().size();
    if (geometry().size().isValid()) {
        if (m_animation) {
            if (m_resetAnimation || m_oldSize != size) {
                initializeFullLayout();
                m_oldSize = size;
                m_resetAnimation = false;
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
    m_resetAnimation = true;
}

void AbstractBarChartItem::setLayout(const QVector<QRectF> &layout)
{
    if (layout.size() != m_layout.size())
        return;

    m_layout = layout;

    int index = 0;
    int setCount = m_series->count();
    for (int set = 0; set < setCount; set++) {
        QBarSet *barSet = m_series->d_func()->barsetAt(set);
        const QList<Bar *> bars = m_barMap.value(barSet);
        for (int category = 0; category < m_categoryCount; category++)
            bars.at(category)->setRect(layout.at(index++));
    }

    positionLabels();
}
//handlers

void AbstractBarChartItem::handleDomainUpdated()
{
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
    updateBarItems();
    QVector<QRectF> layout = calculateLayout();
    handleUpdatedBars();
    applyLayout(layout);
}

void AbstractBarChartItem::handleLabelsVisibleChanged(bool visible)
{
    bool newVisible = visible && m_series->isVisible();
    QMapIterator<QBarSet *, QList<Bar *> > i(m_barMap);
    while (i.hasNext()) {
        i.next();
        const QList<Bar *> &bars = i.value();
        for (int j = 0; j < m_categoryCount; j++) {
            QGraphicsTextItem *label = bars.at(j)->labelItem();
            if (label)
                label->setVisible(newVisible);
        }
    }
    if (newVisible) {
        handleUpdatedBars();
        positionLabels();
    }
    update();
}

void AbstractBarChartItem::handleDataStructureChanged()
{
    handleSetStructureChange();
    handleLayoutChanged();
}

void AbstractBarChartItem::handleVisibleChanged()
{
    bool visible = m_series->isVisible();
    handleLabelsVisibleChanged(m_series->isLabelsVisible());

    QMapIterator<QBarSet *, QList<Bar *> > i(m_barMap);
    while (i.hasNext()) {
        i.next();
        const QList<Bar *> &bars = i.value();
        for (int j = 0; j < m_categoryCount; j++) {
            Bar *bar = bars.at(j);
            bar->setVisible(visible && i.key()->at(bar->index()) != 0.0);
        }
    }
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
        int setCount = m_series->count();
        const bool seriesVisualsDirty = m_series->d_func()->visualsDirty();
        const bool seriesLabelsDirty = m_series->d_func()->labelsDirty();
        m_series->d_func()->setVisualsDirty(false);

        const bool updateLabels =
                m_series->isLabelsVisible() && m_series->isVisible() && presenter();
        if (updateLabels) {
            createLabelItems();
            m_series->d_func()->setLabelsDirty(false);
        }

        for (int set = 0; set < setCount; set++) {
            QBarSet *barSet = m_series->d_func()->barsetAt(set);
            QBarSetPrivate *barSetP = barSet->d_ptr.data();
            const bool setVisualsDirty = barSetP->visualsDirty();
            const bool setLabelsDirty = barSetP->labelsDirty();
            barSetP->setVisualsDirty(false);
            if (updateLabels)
                barSetP->setLabelsDirty(false);
            const QList<Bar *> bars = m_barMap.value(barSet);
            const int actualBarCount = barSet->count();
            const int categoryCount = bars.size();
            for (int category = 0; category < categoryCount; category++) {
                Bar *bar = bars.at(category);
                if (seriesVisualsDirty || setVisualsDirty || bar->visualsDirty()) {
                    bar->setPen(barSetP->m_pen);
                    bar->setBrush(barSetP->m_brush);
                    bar->setVisualsDirty(false);
                    bar->update();
                }
                if (updateLabels && actualBarCount > category) {
                    if (seriesLabelsDirty || setLabelsDirty || bar->labelDirty()) {
                        bar->setLabelDirty(false);
                        QGraphicsTextItem *label = bars.at(category)->labelItem();
                        QString valueLabel;
                        qreal value = barSetP->value(category + m_firstCategory);
                        if (value == 0.0) {
                            label->setVisible(false);
                        } else {
                            label->setVisible(m_series->isLabelsVisible());
                            valueLabel = generateLabelText(set, category + m_firstCategory, value);
                        }
                        label->setHtml(valueLabel);
                        label->setFont(barSetP->m_labelFont);
                        label->setDefaultTextColor(barSetP->m_labelBrush.color());
                        label->update();
                    }
                }
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
    // By default position labels on horizontal bar series
    // Vertical bar series overload positionLabels() to call positionLabelsVertical()

    if (!m_series->isLabelsVisible())
        return;
    createLabelItems();

    QTransform transform;
    const qreal angle = m_series->d_func()->labelsAngle();
    if (angle != 0.0)
        transform.rotate(angle);

    int index = 0;
    int setCount = m_series->count();
    for (int set = 0; set < setCount; set++) {
        QBarSet *barSet = m_series->d_func()->barsetAt(set);
        const QList<Bar *> bars = m_barMap.value(barSet);
        for (int category = 0; category < m_categoryCount; category++) {
            QGraphicsTextItem *label = bars.at(category)->labelItem();

            QRectF labelRect = label->boundingRect();
            QPointF center = labelRect.center();

            qreal xPos = 0;
            qreal yPos = m_layout.at(index).center().y() - center.y();

            int xDiff = 0;
            if (angle != 0.0) {
                label->setTransformOriginPoint(center.x(), center.y());
                label->setRotation(m_series->d_func()->labelsAngle());
                qreal oldWidth = labelRect.width();
                labelRect = transform.mapRect(labelRect);
                xDiff = (labelRect.width() - oldWidth) / 2;
            }

            int offset = bars.at(category)->pen().width() / 2 + 2;

            switch (m_series->labelsPosition()) {
            case QAbstractBarSeries::LabelsCenter:
                xPos = m_layout.at(index).center().x() - center.x();
                break;
            case QAbstractBarSeries::LabelsInsideEnd:
                xPos = m_layout.at(index).right() - labelRect.width() - offset + xDiff;
                break;
            case QAbstractBarSeries::LabelsInsideBase:
                xPos = m_layout.at(index).left() + offset + xDiff;
                break;
            case QAbstractBarSeries::LabelsOutsideEnd:
                xPos = m_layout.at(index).right() + offset + xDiff;
                break;
            default:
                // Invalid position, never comes here
                break;
            }

            label->setPos(xPos, yPos);
            label->setZValue(zValue() + 1);

            index++;
        }
    }
}

void AbstractBarChartItem::handleBarValueChange(int index, QtCharts::QBarSet *barset)
{
    markLabelsDirty(barset, index - m_firstCategory, 1);
    handleLayoutChanged();
}

void AbstractBarChartItem::handleBarValueAdd(int index, int count, QBarSet *barset)
{
    Q_UNUSED(count)

    // Value insertions into middle of barset need to dirty the rest of the labels of the set
    int visualIndex = qMax(0, index - m_firstCategory);
    markLabelsDirty(barset, visualIndex, -1);
    handleLayoutChanged();
}

void AbstractBarChartItem::handleBarValueRemove(int index, int count, QBarSet *barset)
{
    Q_UNUSED(count)

    // Value removals from the middle of barset need to dirty the rest of the labels of the set.
    int visualIndex = qMax(0, index - m_firstCategory);
    markLabelsDirty(barset, visualIndex, -1);
    handleLayoutChanged();
}

void AbstractBarChartItem::positionLabelsVertical()
{
    if (!m_series->isLabelsVisible())
        return;
    createLabelItems();

    QTransform transform;
    const qreal angle = m_series->d_func()->labelsAngle();
    if (angle != 0.0)
        transform.rotate(angle);

    int index = 0;
    int setCount = m_series->count();
    for (int set = 0; set < setCount; set++) {
        QBarSet *barSet = m_series->d_func()->barsetAt(set);
        const QList<Bar *> bars = m_barMap.value(barSet);
        for (int category = 0; category < m_categoryCount; category++) {
            QGraphicsTextItem *label = bars.at(category)->labelItem();

            QRectF labelRect = label->boundingRect();
            QPointF center = labelRect.center();

            qreal xPos = m_layout.at(index).center().x() - center.x();
            qreal yPos = 0;

            int yDiff = 0;
            if (angle != 0.0) {
                label->setTransformOriginPoint(center.x(), center.y());
                label->setRotation(m_series->d_func()->labelsAngle());
                qreal oldHeight = labelRect.height();
                labelRect = transform.mapRect(labelRect);
                yDiff = (labelRect.height() - oldHeight) / 2;
            }

            int offset = bars.at(category)->pen().width() / 2 + 2;

            switch (m_series->labelsPosition()) {
            case QAbstractBarSeries::LabelsCenter:
                yPos = m_layout.at(index).center().y() - center.y();
                break;
            case QAbstractBarSeries::LabelsInsideEnd:
                yPos = m_layout.at(index).top() + offset + yDiff;
                break;
            case QAbstractBarSeries::LabelsInsideBase:
                yPos = m_layout.at(index).bottom() - labelRect.height() - offset + yDiff;
                break;
            case QAbstractBarSeries::LabelsOutsideEnd:
                yPos = m_layout.at(index).top() - labelRect.height() - offset + yDiff;
                break;
            default:
                // Invalid position, never comes here
                break;
            }

            label->setPos(xPos, yPos);
            label->setZValue(zValue() + 1);

            index++;
        }
    }
}

void AbstractBarChartItem::createLabelItems()
{
    if (!m_labelItemsMissing)
        return;

    m_labelItemsMissing = false;

    QMapIterator<QBarSet *, QList<Bar *> > i(m_barMap);
    while (i.hasNext()) {
        i.next();
        const QList<Bar *> &bars = i.value();
        for (int j = 0; j < bars.size(); j++) {
            QGraphicsTextItem *label = bars.at(j)->labelItem();
            if (!label) {
                QGraphicsTextItem *newLabel = new QGraphicsTextItem(this);
                newLabel->document()->setDocumentMargin(ChartPresenter::textMargin());
                bars.at(j)->setLabelItem(newLabel);
            }
        }
    }
}

// This function is called whenever barsets change
void AbstractBarChartItem::handleSetStructureChange()
{
    QList<QBarSet *> newSets = m_series->barSets();
    QList<QBarSet *> oldSets = m_barMap.keys();

    // Remove obsolete sets
    for (int i = 0; i < oldSets.size(); i++) {
        if (!newSets.contains(oldSets.at(i))) {
            qDeleteAll(m_barMap.value(oldSets.at(i)));
            m_barMap.remove(oldSets.at(i));
        }
    }

    // Create new sets
    for (int s = 0; s < newSets.size(); s++) {
        QBarSet *set = newSets.at(s);
        if (!m_barMap.contains(set)) {
            QList<Bar *> bars;
            m_barMap.insert(set, bars);
        } else {
            // Dirty the old set labels to ensure labels are updated correctly on all series types
            QBarSetPrivate *barSetP = set->d_ptr.data();
            barSetP->setLabelsDirty(true);
        }
    }

    if (themeManager())
        themeManager()->updateSeries(m_series);
}

QString AbstractBarChartItem::generateLabelText(int set, int category, qreal value)
{
    Q_UNUSED(set);
    Q_UNUSED(category);
    static const QString valueTag(QLatin1String("@value"));
    QString valueLabel;
    if (m_series->labelsFormat().isEmpty()) {
        valueLabel = presenter()->numberToString(value);
    } else {
        valueLabel = m_series->labelsFormat();
        valueLabel.replace(valueTag, presenter()->numberToString(value));
    }
    return valueLabel;
}

void AbstractBarChartItem::updateBarItems()
{
    int min(0);
    int max(0);
    if (m_orientation == Qt::Vertical) {
        min = qFloor(domain()->minX()) - 1;
        max = qCeil(domain()->maxX()) + 1;
    } else {
        min = qFloor(domain()->minY()) - 1;
        max = qCeil(domain()->maxY()) + 1;
    }

    int lastBarIndex = m_series->d_func()->categoryCount() - 1;
    int oldFirstCategory = m_firstCategory;

    if (lastBarIndex < 0) {
        // Indicate invalid categories by negatives
        // Last should be one less than the first to make loops work right in case of no categories
        m_firstCategory = -1;
        m_lastCategory = -2;
        m_categoryCount = 0;
    } else {
        m_firstCategory = qMax(qMin(min, lastBarIndex), 0);
        m_lastCategory = qMax(qMin(max, lastBarIndex), m_firstCategory);
        m_categoryCount = m_lastCategory - m_firstCategory + 1;
    }

    bool dirtyAllLabels = oldFirstCategory != m_firstCategory;

    QList<QBarSet *> newSets = m_series->barSets();
    QList<QBarSet *> oldSets = m_barMap.keys();

    Q_ASSERT(newSets.size() == oldSets.size());

    int layoutSize = m_categoryCount * newSets.size();

    QVector<QRectF> oldLayout = m_layout;
    if (layoutSize != m_layout.size())
        m_layout.resize(layoutSize);

    bool visible = m_series->isVisible();

    // Create new graphic items for bars or remove excess ones
    int layoutIndex = 0;
    for (int s = 0; s < newSets.size(); s++) {
        QBarSet *set = newSets.at(s);
        if (dirtyAllLabels) {
            QBarSetPrivate *barSetP = set->d_ptr.data();
            barSetP->setLabelsDirty(true);
        }

        QList<Bar *> bars = m_barMap.value(set);
        int addCount = m_categoryCount - bars.size();
        if (addCount > 0) {
            for (int c = 0; c < addCount; c++) {
                Bar *bar = new Bar(set, this);
                bars.append(bar);
                connect(bar, &Bar::clicked, m_series, &QAbstractBarSeries::clicked);
                connect(bar, &Bar::hovered, m_series, &QAbstractBarSeries::hovered);
                connect(bar, &Bar::pressed, m_series, &QAbstractBarSeries::pressed);
                connect(bar, &Bar::released, m_series, &QAbstractBarSeries::released);
                connect(bar, &Bar::doubleClicked, m_series, &QAbstractBarSeries::doubleClicked);

                connect(bar, &Bar::clicked, set, &QBarSet::clicked);
                connect(bar, &Bar::hovered, set, &QBarSet::hovered);
                connect(bar, &Bar::pressed, set, &QBarSet::pressed);
                connect(bar, &Bar::released, set, &QBarSet::released);
                connect(bar, &Bar::doubleClicked, set, &QBarSet::doubleClicked);

                bar->setVisible(m_series->isVisible());
                m_labelItemsMissing = true;
            }
        }
        // Update bar indexes
        QHash<int, Bar*> indexMap;
        QVector<Bar *> unassignedBars(m_categoryCount, nullptr);
        int unassignedIndex(0);
        QList<Bar *> newBars;
        newBars.reserve(m_categoryCount);
        for (int c = 0; c < bars.size(); c++) {
            Bar *bar = bars.at(c);
            if (bar->index() < m_firstCategory || bar->index() > m_lastCategory) {
                // Delete excess unassigned bars first
                if (addCount < 0) {
                    addCount++;
                    delete bar;
                    bar = nullptr;
                } else {
                    unassignedBars[unassignedIndex++] = bar;
                    bar->setLayoutIndex(layoutIndex);
                    newBars.append(bar);
                    layoutIndex++;
                }
            } else {
                indexMap.insert(bar->index(), bar);
                newBars.append(bar);
                m_layout[layoutIndex] = oldLayout.at(bar->layoutIndex());
                bar->setLayoutIndex(layoutIndex);
                layoutIndex++;
            }
        }
        unassignedIndex = 0;
        for (int c = m_firstCategory; c <= m_lastCategory; c++) {
            Bar *bar = indexMap.value(c);
            if (!bar) {
                bar = unassignedBars.at(unassignedIndex++);
                if (bar) {
                    bar->setIndex(c);
                    if (m_animation) {
                        int layoutIndex = bar->layoutIndex();
                        initializeLayout(s, c, layoutIndex, m_resetAnimation);
                        bar->setRect(m_layout.at(layoutIndex));
                    }
                }
            }
            if (bar)
                bar->setVisible(visible && set->at(c) != 0.0);
        }

        m_barMap.insert(set, newBars);
    }
}

void AbstractBarChartItem::markLabelsDirty(QBarSet *barset, int visualIndex, int count)
{
    Q_ASSERT(barset);

    QList<Bar *> bars = m_barMap.value(barset);
    int firstIndex = qMax(0, visualIndex);
    int lastIndex = count < 0 ? bars.size() - 1 : visualIndex + count - 1;
    lastIndex = qMin(bars.size() - 1, lastIndex);
    for (int i = firstIndex; i <= lastIndex; i++)
        bars.at(i)->setLabelDirty(true);
}

#include "moc_abstractbarchartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
