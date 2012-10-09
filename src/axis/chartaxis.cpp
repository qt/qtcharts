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
#include "domain_p.h"
#include <qmath.h>
#include <QDateTime>
#include <QValueAxis>
#include <QGraphicsLayout>
#include <QFontMetrics>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartAxis::ChartAxis(QAbstractAxis *axis, ChartPresenter *presenter, bool intervalAxis)
    : ChartElement(presenter),
      m_chartAxis(axis),
      m_labelsAngle(0),
      m_grid(new QGraphicsItemGroup(presenter->rootItem())),
      m_shades(new QGraphicsItemGroup(presenter->rootItem())),
      m_labels(new QGraphicsItemGroup(presenter->rootItem())),
      m_arrow(new QGraphicsItemGroup(presenter->rootItem())),
      m_title(new QGraphicsSimpleTextItem(presenter->rootItem())),
      m_min(0),
      m_max(0),
      m_animation(0),
      m_labelPadding(5),
      m_intervalAxis(intervalAxis)
{
    //initial initialization
    m_arrow->setZValue(ChartPresenter::AxisZValue);
    m_arrow->setHandlesChildEvents(false);
    m_labels->setZValue(ChartPresenter::AxisZValue);
    m_shades->setZValue(ChartPresenter::ShadesZValue);
    m_grid->setZValue(ChartPresenter::GridZValue);

    QObject::connect(m_chartAxis->d_ptr.data(), SIGNAL(updated()), this, SLOT(handleAxisUpdated()));

    QGraphicsSimpleTextItem item;
    m_font = item.font();

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
    if (m_arrow->children().size() == 0)
        m_arrow->addToGroup(new AxisItem(this, presenter()->rootItem()));

    if (m_intervalAxis && m_grid->children().size() == 0) {
        for (int i = 0 ; i < 2 ; i  ++)
            m_grid->addToGroup(new QGraphicsLineItem(presenter()->rootItem()));
    }

    for (int i = 0; i < count; ++i) {
        m_grid->addToGroup(new QGraphicsLineItem(presenter()->rootItem()));
        m_labels->addToGroup(new QGraphicsSimpleTextItem(presenter()->rootItem()));
        m_arrow->addToGroup(new QGraphicsLineItem(presenter()->rootItem()));
        if ((m_grid->childItems().size()) % 2 && m_grid->childItems().size() > 2)
            m_shades->addToGroup(new QGraphicsRectItem(presenter()->rootItem()));
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

    if (diff < 0) handleAxisUpdated();

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

void ChartAxis::setArrowOpacity(qreal opacity)
{
    m_arrow->setOpacity(opacity);
}

qreal ChartAxis::arrowOpacity() const
{
    return m_arrow->opacity();
}

void ChartAxis::setArrowVisibility(bool visible)
{
    m_arrow->setOpacity(visible);
}

void ChartAxis::setGridOpacity(qreal opacity)
{
    m_grid->setOpacity(opacity);
}

qreal ChartAxis::gridOpacity() const
{
    return m_grid->opacity();
}

void ChartAxis::setGridVisibility(bool visible)
{
    m_grid->setOpacity(visible);
}

void ChartAxis::setLabelsOpacity(qreal opacity)
{
    m_labels->setOpacity(opacity);
}

qreal ChartAxis::labelsOpacity() const
{
    return m_labels->opacity();
}

void ChartAxis::setLabelsVisibility(bool visible)
{
    m_labels->setOpacity(visible);
}

void ChartAxis::setShadesOpacity(qreal opacity)
{
    m_shades->setOpacity(opacity);
}

qreal ChartAxis::shadesOpacity() const
{
    return m_shades->opacity();
}

void ChartAxis::setShadesVisibility(bool visible)
{
    m_shades->setVisible(visible);
}

void ChartAxis::setLabelsAngle(int angle)
{
    foreach (QGraphicsItem *item, m_labels->childItems())
        item->setRotation(angle);

    m_labelsAngle = angle;
}

void ChartAxis::setLabelsPen(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_labels->childItems())
        static_cast<QGraphicsSimpleTextItem *>(item)->setPen(pen);
}

void ChartAxis::setLabelsBrush(const QBrush &brush)
{
    foreach (QGraphicsItem *item , m_labels->childItems())
        static_cast<QGraphicsSimpleTextItem *>(item)->setBrush(brush);
}

void ChartAxis::setLabelsFont(const QFont &font)
{
    foreach (QGraphicsItem *item , m_labels->childItems())
        static_cast<QGraphicsSimpleTextItem *>(item)->setFont(font);

    if (m_font != font) {
        m_font = font;
        foreach (QGraphicsItem *item , m_labels->childItems())
            static_cast<QGraphicsSimpleTextItem *>(item)->setFont(font);
        QGraphicsLayoutItem::updateGeometry();
        presenter()->layout()->invalidate();
    }
}

void ChartAxis::setShadesBrush(const QBrush &brush)
{
    foreach (QGraphicsItem *item , m_shades->childItems())
        static_cast<QGraphicsRectItem *>(item)->setBrush(brush);
}

void ChartAxis::setShadesPen(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_shades->childItems())
        static_cast<QGraphicsRectItem *>(item)->setPen(pen);
}

void ChartAxis::setArrowPen(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_arrow->childItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void ChartAxis::setGridPen(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_grid->childItems())
        static_cast<QGraphicsLineItem *>(item)->setPen(pen);
}

void ChartAxis::setLabelPadding(int padding)
{
    m_labelPadding = padding;
}

bool ChartAxis::isEmpty()
{
    return !m_axisRect.isValid() || m_gridRect.isEmpty() || qFuzzyIsNull(m_min - m_max);
}

void ChartAxis::handleDomainUpdated()
{
    Domain *domain = qobject_cast<Domain *>(sender());
    qreal min(0);
    qreal max(0);

    if (m_chartAxis->orientation() == Qt::Horizontal) {
        min = domain->minX();
        max = domain->maxX();
    } else if (m_chartAxis->orientation() == Qt::Vertical) {
        min = domain->minY();
        max = domain->maxY();
    }

    if (!qFuzzyIsNull(m_min - min) || !qFuzzyIsNull(m_max - max)) {
        m_min = min;
        m_max = max;

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
}

void ChartAxis::handleAxisUpdated()
{
    if (isEmpty())
        return;

    bool visible = m_chartAxis->isVisible();

    setArrowVisibility(visible && m_chartAxis->isLineVisible());
    setGridVisibility(visible && m_chartAxis->isGridLineVisible());
    setLabelsVisibility(visible && m_chartAxis->labelsVisible());
    setShadesVisibility(visible && m_chartAxis->shadesVisible());
    setLabelsAngle(m_chartAxis->labelsAngle());
    setArrowPen(m_chartAxis->linePen());
    setLabelsPen(m_chartAxis->labelsPen());
    setLabelsBrush(m_chartAxis->labelsBrush());
    setLabelsFont(m_chartAxis->labelsFont());
    setGridPen(m_chartAxis->gridLinePen());
    setShadesPen(m_chartAxis->shadesPen());
    setShadesBrush(m_chartAxis->shadesBrush());
    setTitleText(m_chartAxis->title());
}

void ChartAxis::setTitleText(const QString &title)
{
    if (m_titleText != title) {
        m_titleText = title;
        m_axisRect = QRect();
        QGraphicsLayoutItem::updateGeometry();
        presenter()->layout()->invalidate();
    }
}

void ChartAxis::hide()
{
    setArrowVisibility(false);
    setGridVisibility(false);
    setLabelsVisibility(false);
    setShadesVisibility(false);
}

void ChartAxis::setGeometry(const QRectF &axis, const QRectF &grid)
{
    m_gridRect = grid;
    m_axisRect = axis;

    if (isEmpty())
        return;

    if (!m_titleText.isNull()) {
        QFontMetrics fn(m_title->font());

        int size(0);

        if (orientation() == Qt::Horizontal)
            size = grid.width();
        else if (orientation() == Qt::Vertical)
            size = grid.height();

        if (fn.boundingRect(m_titleText).width() > size) {
            QString string = m_titleText + "...";
            while (fn.boundingRect(string).width() > size && string.length() > 3)
                string.remove(string.length() - 4, 1);
            m_title->setText(string);
        } else {
            m_title->setText(m_titleText);
        }

        QPointF center = grid.center() - m_title->boundingRect().center();
        if (orientation() == Qt::Horizontal) {
            m_title->setPos(center.x(), m_axisRect.bottom() - m_title->boundingRect().height());
        } else if (orientation() == Qt::Vertical) {
            m_title->setTransformOriginPoint(m_title->boundingRect().center());
            m_title->setRotation(270);
            m_title->setPos(m_axisRect.left() - m_title->boundingRect().width() / 2 + m_title->boundingRect().height() / 2, center.y());
        }
    }

    QVector<qreal> layout = calculateLayout();
    updateLayout(layout);

}

void ChartAxis::axisSelected()
{
    //TODO: axis clicked;
}

Qt::Orientation ChartAxis::orientation() const
{
    return m_chartAxis->orientation();
}

Qt::Alignment ChartAxis::alignment() const
{
    return m_chartAxis->alignment();
}

bool ChartAxis::isVisible()
{
    return m_chartAxis->isVisible();
}

void ChartAxis::setLabels(const QStringList &labels)
{
    m_labelsList = labels;
}

QStringList ChartAxis::createValueLabels(int ticks) const
{
    Q_ASSERT(m_max > m_min);
    Q_ASSERT(ticks > 1);

    QStringList labels;

    int n = qMax(int(-qFloor(log10((m_max - m_min) / (ticks - 1)))), 0);
    n++;

    QValueAxis *axis = qobject_cast<QValueAxis *>(m_chartAxis);

    QString format = axis->labelFormat();

    if (format.isNull()) {
        for (int i = 0; i < ticks; i++) {
            qreal value = m_min + (i * (m_max - m_min) / (ticks - 1));
            labels << QString::number(value, 'f', n);
        }
    } else {
        QByteArray array = format.toAscii();
        for (int i = 0; i < ticks; i++) {
            qreal value = m_min + (i * (m_max - m_min) / (ticks - 1));
            labels << QString().sprintf(array, value);
        }
    }

    return labels;
}

QStringList ChartAxis::createDateTimeLabels(const QString &format, int ticks) const
{
    Q_ASSERT(m_max > m_min);
    Q_ASSERT(ticks > 1);
    QStringList labels;
    int n = qMax(int(-floor(log10((m_max - m_min) / (ticks - 1)))), 0);
    n++;
    for (int i = 0; i < ticks; i++) {
        qreal value = m_min + (i * (m_max - m_min) / (ticks - 1));
        labels << QDateTime::fromMSecsSinceEpoch(value).toString(format);
    }
    return labels;
}

QSizeF ChartAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return QSizeF();
}

#include "moc_chartaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
