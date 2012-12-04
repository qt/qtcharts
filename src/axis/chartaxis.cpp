/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartaxis_p.h"
#include "qabstractaxis.h"
#include "qabstractaxis_p.h"
#include "chartpresenter_p.h"
#include "chartlayout_p.h"
#include "abstractdomain_p.h"
#include <qmath.h>
#include <QDateTime>
#include <QValueAxis>
#include <QLogValueAxis>
#include <QGraphicsLayout>
#include <QFontMetrics>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAxis::ChartAxis(QAbstractAxis *axis, QGraphicsItem* item , bool intervalAxis)
    : ChartElement(item),
      m_axis(axis),
      m_labelsAngle(0),
      m_grid(new QGraphicsItemGroup(item)),
      m_arrow(new QGraphicsItemGroup(item)),
      m_shades(new QGraphicsItemGroup(item)),
      m_labels(new QGraphicsItemGroup(item)),
      m_title(new QGraphicsSimpleTextItem(item)),
      m_animation(0),
      m_labelPadding(5),
      m_intervalAxis(intervalAxis)
{
    Q_ASSERT(item);
    //initial initialization    
    m_arrow->setHandlesChildEvents(false);
    m_arrow->setZValue(ChartPresenter::AxisZValue);
    m_labels->setZValue(ChartPresenter::AxisZValue);
    m_shades->setZValue(ChartPresenter::ShadesZValue);
    m_grid->setZValue(ChartPresenter::GridZValue);
    m_title->setZValue(ChartPresenter::GridZValue);
    handleVisibleChanged(m_axis->isVisible());
    connectSlots();

    setFlag(QGraphicsItem::ItemHasNoContents,true);
}

void ChartAxis::connectSlots()
{
    QObject::connect(m_axis,SIGNAL(visibleChanged(bool)),this,SLOT(handleVisibleChanged(bool)));
    QObject::connect(m_axis,SIGNAL(lineVisibleChanged(bool)),this,SLOT(handleArrowVisibleChanged(bool)));
    QObject::connect(m_axis,SIGNAL(gridVisibleChanged(bool)),this,SLOT(handleGridVisibleChanged(bool)));
    QObject::connect(m_axis,SIGNAL(labelsVisibleChanged(bool)),this,SLOT(handleLabelsVisibleChanged(bool)));
    QObject::connect(m_axis,SIGNAL(shadesVisibleChanged(bool)),this,SLOT(handleShadesVisibleChanged(bool)));
    QObject::connect(m_axis,SIGNAL(labelsAngleChanged(int)),this,SLOT(handleLabelsAngleChanged(int)));
    QObject::connect(m_axis,SIGNAL(linePenChanged(const QPen&)),this,SLOT(handleArrowPenChanged(const QPen&)));
    QObject::connect(m_axis,SIGNAL(labelsPenChanged(const QPen&)),this,SLOT(handleLabelsPenChanged(const QPen&)));
    QObject::connect(m_axis,SIGNAL(labelsBrushChanged(const QBrush&)),this,SLOT(handleLabelsBrushChanged(const QBrush&)));
    QObject::connect(m_axis,SIGNAL(labelsFontChanged(const QFont&)),this,SLOT(handleLabelsFontChanged(const QFont&)));
    QObject::connect(m_axis,SIGNAL(gridLinePenChanged(const QPen&)),this,SLOT(handleGridPenChanged(const QPen&)));
    QObject::connect(m_axis,SIGNAL(shadesPenChanged(const QPen&)),this,SLOT(handleShadesPenChanged(const QPen&)));
    QObject::connect(m_axis,SIGNAL(shadesBrushChanged(const QBrush&)),this,SLOT(handleShadesBrushChanged(const QBrush&)));
    QObject::connect(m_axis,SIGNAL(titleTextChanged(const QString&)),this,SLOT(handleTitleTextChanged(const QString&)));
    QObject::connect(m_axis,SIGNAL(titleFontChanged(const QFont&)),this,SLOT(handleTitleFontChanged(const QFont&)));
    QObject::connect(m_axis,SIGNAL(titlePenChanged(const QPen&)),this,SLOT(handleTitlePenChanged(const QPen&)));
    QObject::connect(m_axis,SIGNAL(titleBrushChanged(const QBrush&)),this,SLOT(handleTitleBrushChanged(const QBrush&)));
    QObject::connect(m_axis,SIGNAL(titleVisibleChanged(bool)),this,SLOT(handleTitleVisibleChanged(bool)));
    QObject::connect(m_axis->d_ptr.data(),SIGNAL(rangeChanged(qreal,qreal)),this,SLOT(handleRangeChanged(qreal,qreal)));
}

ChartAxis::~ChartAxis()
{
}

void ChartAxis::setAnimation(AxisAnimation *animation)
{
    m_animation = animation;
}

void ChartAxis::setLayout(QVector<qreal> &layout)
{
    m_layoutVector = layout;
}

void ChartAxis::createItems(int count)
{
    if (m_arrow->childItems().size() == 0){
        QGraphicsLineItem* arrow = new ArrowItem(this, this);
        arrow->setPen(m_axis->linePen());
        m_arrow->addToGroup(arrow);
    }

    if (m_intervalAxis && m_grid->childItems().size() == 0) {
        for (int i = 0 ; i < 2 ; i  ++){
            QGraphicsLineItem* item = new QGraphicsLineItem(this);
            item->setPen(m_axis->gridLinePen());
            m_grid->addToGroup(item);
        }
    }

    for (int i = 0; i < count; ++i) {
        QGraphicsLineItem* arrow = new QGraphicsLineItem(this);
        arrow->setPen(m_axis->linePen());
        QGraphicsLineItem* grid = new QGraphicsLineItem(this);
        grid->setPen(m_axis->gridLinePen());
        QGraphicsSimpleTextItem* label = new QGraphicsSimpleTextItem(this);
        label->setFont(m_axis->labelsFont());
        label->setPen(m_axis->labelsPen());
        label->setBrush(m_axis->labelsBrush());
        m_arrow->addToGroup(arrow);
        m_grid->addToGroup(grid);
        m_labels->addToGroup(label);

        if ((m_grid->childItems().size()) % 2 && m_grid->childItems().size() > 2){
            QGraphicsRectItem* shades = new QGraphicsRectItem(this);
            shades->setPen(m_axis->shadesPen());
            shades->setBrush(m_axis->shadesBrush());
            m_shades->addToGroup(shades);
        }
    }

}

void ChartAxis::deleteItems(int count)
{
    QList<QGraphicsItem *> lines = m_grid->childItems();
    QList<QGraphicsItem *> labels = m_labels->childItems();
    QList<QGraphicsItem *> shades = m_shades->childItems();
    QList<QGraphicsItem *> axis = m_arrow->childItems();

    for (int i = 0; i < count; ++i) {
        if (lines.size() % 2 && lines.size() > 1)
            delete(shades.takeLast());
        delete(lines.takeLast());
        delete(labels.takeLast());
        delete(axis.takeLast());
    }
}

void ChartAxis::updateLayout(QVector<qreal> &layout)
{
    int diff = m_layoutVector.size() - layout.size();

    if (diff > 0)
        deleteItems(diff);
    else if (diff < 0)
        createItems(-diff);

    if (m_animation) {
        switch (presenter()->state()) {
        case ChartPresenter::ZoomInState:
            m_animation->setAnimationType(AxisAnimation::ZoomInAnimation);
            m_animation->setAnimationPoint(presenter()->statePoint());
            break;
        case ChartPresenter::ZoomOutState:
            m_animation->setAnimationType(AxisAnimation::ZoomOutAnimation);
            m_animation->setAnimationPoint(presenter()->statePoint());
            break;
        case ChartPresenter::ScrollUpState:
        case ChartPresenter::ScrollLeftState:
            m_animation->setAnimationType(AxisAnimation::MoveBackwordAnimation);
            break;
        case ChartPresenter::ScrollDownState:
        case ChartPresenter::ScrollRightState:
            m_animation->setAnimationType(AxisAnimation::MoveForwardAnimation);
            break;
        case ChartPresenter::ShowState:
            m_animation->setAnimationType(AxisAnimation::DefaultAnimation);
            break;
        }
        m_animation->setValues(m_layoutVector, layout);
        presenter()->startAnimation(m_animation);
    } else {
        setLayout(layout);
        updateGeometry();
    }
}

void ChartAxis::setLabelPadding(int padding)
{
    m_labelPadding = padding;
}

bool ChartAxis::isEmpty()
{
    return m_axisRect.isEmpty() || m_gridRect.isEmpty() ||  qFuzzyCompare(min(),max());
}

void ChartAxis::setGeometry(const QRectF &axis, const QRectF &grid)
{
    m_gridRect = grid;
    m_axisRect = axis;

    if (isEmpty())
        return;

    QVector<qreal> layout = calculateLayout();
    updateLayout(layout);
}

qreal ChartAxis::min() const
{
    return m_axis->d_ptr->min();
}

qreal ChartAxis::max() const
{
    return m_axis->d_ptr->max();
}

QFont ChartAxis::font() const
{
    return m_axis->labelsFont();
}

QFont ChartAxis::titleFont() const
{
    return m_axis->titleFont();
}

QString ChartAxis::titleText() const
{
    return m_axis->titleText();
}

void ChartAxis::axisSelected()
{
    emit clicked();
}

Qt::Orientation ChartAxis::orientation() const
{
    return m_axis->orientation();
}

Qt::Alignment ChartAxis::alignment() const
{
    return m_axis->alignment();
}

void ChartAxis::setLabels(const QStringList &labels)
{
    m_labelsList = labels;
}

QSizeF ChartAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return QSizeF();
}

//handlers

void ChartAxis::handleArrowVisibleChanged(bool visible)
{
    m_arrow->setVisible(visible);
}

void ChartAxis::handleGridVisibleChanged(bool visible)
{
    m_grid->setVisible(visible);
}

void ChartAxis::handleLabelsVisibleChanged(bool visible)
{
    m_labels->setVisible(visible);
}

void ChartAxis::handleShadesVisibleChanged(bool visible)
{
    m_shades->setVisible(visible);
}

void ChartAxis::handleTitleVisibleChanged(bool visible)
{
    m_title->setVisible(visible);
    presenter()->layout()->invalidate();
}

void ChartAxis::handleLabelsAngleChanged(int angle)
{
    foreach (QGraphicsItem *item, m_labels->childItems())
        item->setRotation(angle);

    m_labelsAngle = angle;
}

void ChartAxis::handleLabelsPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_labels->childItems())
        static_cast<QGraphicsSimpleTextItem *>(item)->setPen(pen);
}

void ChartAxis::handleLabelsBrushChanged(const QBrush &brush)
{
    foreach (QGraphicsItem *item , m_labels->childItems())
        static_cast<QGraphicsSimpleTextItem *>(item)->setBrush(brush);
}

void ChartAxis::handleLabelsFontChanged(const QFont &font)
{
    foreach (QGraphicsItem *item , m_labels->childItems())
    static_cast<QGraphicsSimpleTextItem *>(item)->setFont(font);
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartAxis::handleShadesBrushChanged(const QBrush &brush)
{
    foreach (QGraphicsItem *item , m_shades->childItems())
        static_cast<QGraphicsRectItem *>(item)->setBrush(brush);
}

void ChartAxis::handleShadesPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_shades->childItems())
        static_cast<QGraphicsRectItem *>(item)->setPen(pen);
}

void ChartAxis::handleArrowPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_arrow->childItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void ChartAxis::handleGridPenChanged(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_grid->childItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void ChartAxis::handleTitleTextChanged(const QString &title)
{
    Q_UNUSED(title)
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}


void ChartAxis::handleTitlePenChanged(const QPen &pen)
{
    m_title->setPen(pen);
}

void ChartAxis::handleTitleBrushChanged(const QBrush &brush)
{
    m_title->setBrush(brush);
}

void ChartAxis::handleTitleFontChanged(const QFont &font)
{
    if(m_title->font() != font){
        m_title->setFont(font);
        QGraphicsLayoutItem::updateGeometry();
        presenter()->layout()->invalidate();
    }
}

void ChartAxis::handleVisibleChanged(bool visible)
{
    setVisible(visible);
    if(!visible) {
        m_grid->setVisible(visible);
        m_arrow->setVisible(visible);
        m_shades->setVisible(visible);
        m_labels->setVisible(visible);
        m_title->setVisible(visible);
    }else {
        m_grid->setVisible(m_axis->isGridLineVisible());
        m_arrow->setVisible(m_axis->isLineVisible());
        m_shades->setVisible(m_axis->shadesVisible());
        m_labels->setVisible(m_axis->labelsVisible());
        m_title->setVisible(m_axis->isTitleVisible());
    }

    if(presenter()) presenter()->layout()->invalidate();
}

void ChartAxis::handleRangeChanged(qreal min, qreal max)
{
    Q_UNUSED(min);
    Q_UNUSED(max);

    if (!isEmpty()) {

        QVector<qreal> layout = calculateLayout();
        updateLayout(layout);
        QSizeF before = effectiveSizeHint(Qt::PreferredSize);
        QSizeF after = sizeHint(Qt::PreferredSize);

        if (before != after) {
            QGraphicsLayoutItem::updateGeometry();
            //we don't want to call invalidate on layout, since it will change minimum size of component,
            //which we would like to avoid since it causes nasty flips when scrolling or zooming,
            //instead recalculate layout and use plotArea for extra space.
            presenter()->layout()->setGeometry(presenter()->layout()->geometry());
        }
    }

}

//helpers

QStringList ChartAxis::createValueLabels(qreal min, qreal max, int ticks,const QString& format)
{
    //TODO: Q_ASSERT(m_max > m_min);
    //TODO: Q_ASSERT(ticks > 1);

    QStringList labels;

    if(max <= min || ticks < 1){
        return labels;
    }

    int n = qMax(int(-qFloor(log10((max - min) / (ticks - 1)))), 0);
    n++;

    if (format.isNull()) {
        for (int i = 0; i < ticks; i++) {
            qreal value = min + (i * (max - min) / (ticks - 1));
            labels << QString::number(value, 'f', n);
        }
    } else {
        QByteArray array = format.toLatin1();
        for (int i = 0; i < ticks; i++) {
            qreal value = min + (i * (max - min) / (ticks - 1));
            if (format.contains("d")
                    || format.contains("i")
                    || format.contains("c"))
                labels << QString().sprintf(array, (qint64)value);
            else if (format.contains("u")
                     || format.contains("o")
                     || format.contains("x", Qt::CaseInsensitive))
                labels << QString().sprintf(array, (quint64)value);
            else if (format.contains("f", Qt::CaseInsensitive)
                      || format.contains("e", Qt::CaseInsensitive)
                      || format.contains("g", Qt::CaseInsensitive))
                labels << QString().sprintf(array, value);
            else
                labels << QString();
        }
    }

    return labels;
}

QStringList ChartAxis::createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString& format)
{
//    Q_ASSERT(m_max > m_min);
    //    Q_ASSERT(ticks > 1);

    QStringList labels;

    int n = 0;
    if (ticks > 1)
        n = qMax(int(-qFloor(log10((max - min) / (ticks - 1)))), 0);
    n++;

    int firstTick;
    if (base > 1)
        firstTick = ceil(log10(min) / log10(base));
    else
        firstTick = ceil(log10(max) / log10(base));

    if (format.isNull()) {
        for (int i = firstTick; i < ticks + firstTick; i++) {
            qreal value = qPow(base, i);
            labels << QString::number(value, 'f', n);
        }
    } else {
        QByteArray array = format.toLatin1();
        for (int i = firstTick; i < ticks + firstTick; i++) {
            qreal value = qPow(base, i);
            if (format.contains("d")
                    || format.contains("i")
                    || format.contains("c"))
                labels << QString().sprintf(array, (qint64)value);
            else if (format.contains("u")
                     || format.contains("o")
                     || format.contains("x", Qt::CaseInsensitive))
                labels << QString().sprintf(array, (quint64)value);
            else if (format.contains("f", Qt::CaseInsensitive)
                      || format.contains("e", Qt::CaseInsensitive)
                      || format.contains("g", Qt::CaseInsensitive))
                labels << QString().sprintf(array, value);
            else
                labels << QString();
        }
    }

    return labels;
}

QStringList ChartAxis::createDateTimeLabels(qreal min, qreal max,int ticks,const QString& format)
{
    //TODO: Q_ASSERT(m_max > m_min);
    //TODO: Q_ASSERT(ticks > 1);
    QStringList labels;

    if(max <= min || ticks < 1) {
        return labels;
    }

    int n = qMax(int(-floor(log10((max - min) / (ticks - 1)))), 0);
    n++;
    for (int i = 0; i < ticks; i++) {
        qreal value = min + (i * (max - min) / (ticks - 1));
        labels << QDateTime::fromMSecsSinceEpoch(value).toString(format);
    }
    return labels;
}

#include "moc_chartaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
