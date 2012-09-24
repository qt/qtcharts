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
#include "chartpresenter_p.h"
#include "qchart.h"
#include "qchart_p.h"
#include "qabstractaxis.h"
#include "qabstractaxis_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimation_p.h"
#include "qabstractseries_p.h"
#include "qareaseries.h"
#include "chartaxis_p.h"
#include "chartbackground_p.h"
#include "chartlayout_p.h"
#include "charttitle_p.h"
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart, ChartDataSet* dataset)
    : QObject(chart),
      m_chart(chart),
      m_dataset(dataset),
      m_chartTheme(0),
      m_options(QChart::NoAnimation),
      m_state(ShowState),
      m_layout(new ChartLayout(this)),
      m_background(0),
      m_title(0)
{

}

ChartPresenter::~ChartPresenter()
{
    delete m_chartTheme;
}

void ChartPresenter::setChartsGeometry(const QRectF& rect)
{
    Q_ASSERT(rect.isValid());

    if (m_chartsRect != rect) {
        m_chartsRect = rect;
        foreach (ChartElement *chart, m_chartItems)
            chart->handleGeometryChanged(rect);
    }
}

QRectF ChartPresenter::chartsGeometry() const
{
    return m_chartsRect;
}

void ChartPresenter::handleAxisAdded(QAbstractAxis* axis, Domain* domain)
{
    ChartAxis* item = axis->d_ptr->createGraphics(this);
    item->setDomain(domain);

    if (m_options.testFlag(QChart::GridAxisAnimations))
        item->setAnimation(new AxisAnimation(item));

    QObject::connect(this, SIGNAL(geometryChanged(QRectF)), item, SLOT(handleGeometryChanged(QRectF)));
    QObject::connect(domain, SIGNAL(updated()), item, SLOT(handleDomainUpdated()));
    QObject::connect(axis, SIGNAL(visibleChanged(bool)), this, SLOT(handleAxisVisibleChanged(bool)));

    //initialize
    domain->emitUpdated();
    m_chartTheme->decorate(axis);
    axis->d_ptr->setDirty(false);
    axis->d_ptr->emitUpdated();
    if (m_chartsRect.isValid())
        item->handleGeometryChanged(m_chartsRect);

    m_axisItems.insert(axis, item);
    selectVisibleAxis();
}

void ChartPresenter::handleAxisRemoved(QAbstractAxis* axis)
{
    ChartAxis* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    selectVisibleAxis();
    item->hide();
    item->disconnect();
    QObject::disconnect(this, 0, item, 0);
    item->deleteLater();
}


void ChartPresenter::handleSeriesAdded(QAbstractSeries* series, Domain* domain)
{
    ChartElement *item = series->d_ptr->createGraphics(this);
    Q_ASSERT(item);
    item->setDomain(domain);

    QObject::connect(this, SIGNAL(geometryChanged(QRectF)), item, SLOT(handleGeometryChanged(QRectF)));
    QObject::connect(domain, SIGNAL(updated()), item, SLOT(handleDomainUpdated()));
    //initialize
    item->handleDomainUpdated();

    if (m_chartsRect.isValid())
        item->handleGeometryChanged(m_chartsRect);
    m_chartItems.insert(series, item);
}

void ChartPresenter::handleSeriesRemoved(QAbstractSeries* series)
{
    ChartElement* item = m_chartItems.take(series);
    Q_ASSERT(item);
    item->deleteLater();
}

void ChartPresenter::selectVisibleAxis()
{
    QMapIterator<QAbstractAxis*, ChartAxis*> i(m_axisItems);

    while (i.hasNext()) {
        i.next();
//        i.key()->hide();
        i.key()->show();
    }

//    i.toFront();

//    bool axisX=false;
//    bool axisY=false;

//    while (i.hasNext()) {
//        i.next();
//        if(i.key()->orientation()==Qt::Vertical && !axisY) {
//            axisY=true;
//            i.key()->show();
//        }
//        if(i.key()->orientation()==Qt::Horizontal && !axisX) {
//            axisX=true;
//            i.key()->show();
//        }

//    }
}


void ChartPresenter::handleAxisVisibleChanged(bool visible)
{
    QAbstractAxis* axis = static_cast<QAbstractAxis*>(sender());
    Q_ASSERT(axis);
    if (visible) {

        QMapIterator<QAbstractAxis*, ChartAxis*> i(m_axisItems);

        while (i.hasNext()) {
            i.next();
            if (i.key() == axis)
                continue;
            if (i.key()->orientation() == axis->orientation())
                i.key()->setVisible(false);
        }
    }
}

void ChartPresenter::setTheme(QChart::ChartTheme theme, bool force)
{
    if (m_chartTheme && m_chartTheme->id() == theme)
        return;
    delete m_chartTheme;
    m_chartTheme = ChartTheme::createTheme(theme);
    m_chartTheme->setForced(force);
    m_chartTheme->decorate(m_chart);
    m_chartTheme->decorate(m_chart->legend());
    resetAllElements();

    // We do not want "force" to stay on.
    // Bar/pie are calling decorate when adding/removing slices/bars which means
    // that to preserve users colors "force" must not be on.
    m_chartTheme->setForced(false);
}

QChart::ChartTheme ChartPresenter::theme()
{
    return m_chartTheme->id();
}

void ChartPresenter::setAnimationOptions(QChart::AnimationOptions options)
{
    if (m_options != options) {
        m_options = options;
        resetAllElements();
    }

}

void ChartPresenter::resetAllElements()
{
    QMapIterator<QAbstractAxis*, ChartAxis*> i(m_axisItems);
    while (i.hasNext()) {
        i.next();
        Domain* domain = i.value()->domain();
        QAbstractAxis* axis = i.key();
        handleAxisRemoved(axis);
        handleAxisAdded(axis, domain);
    }

    QMapIterator<QAbstractSeries*, ChartElement*> j(m_chartItems);
    while (j.hasNext()) {
        j.next();
        Domain* domain = j.value()->domain();
        QAbstractSeries* series = j.key();
        handleSeriesRemoved(series);
        handleSeriesAdded(series, domain);
    }

    layout()->invalidate();
}

void ChartPresenter::zoomIn(qreal factor)
{
    QRectF rect = chartsGeometry();
    rect.setWidth(rect.width() / factor);
    rect.setHeight(rect.height() / factor);
    rect.moveCenter(chartsGeometry().center());
    zoomIn(rect);
}

void ChartPresenter::zoomIn(const QRectF& rect)
{
    QRectF r = rect.normalized();
    r.translate(-chartsGeometry().topLeft());
    if (!r.isValid())
        return;

    m_state = ZoomInState;
    m_statePoint = QPointF(r.center().x() / chartsGeometry().width(), r.center().y() / chartsGeometry().height());
    m_dataset->zoomInDomain(r, chartsGeometry().size());
    m_state = ShowState;
}

void ChartPresenter::zoomOut(qreal factor)
{
    m_state = ZoomOutState;

    QRectF chartRect;
    chartRect.setSize(chartsGeometry().size());

    QRectF rect;
    rect.setSize(chartRect.size() / factor);
    rect.moveCenter(chartRect.center());
    if (!rect.isValid())
        return;
    m_statePoint = QPointF(rect.center().x() / chartsGeometry().width(), rect.center().y() / chartsGeometry().height());
    m_dataset->zoomOutDomain(rect, chartRect.size());
    m_state = ShowState;
}

void ChartPresenter::scroll(qreal dx, qreal dy)
{
    if (dx < 0) m_state = ScrollLeftState;
    if (dx > 0) m_state = ScrollRightState;
    if (dy < 0) m_state = ScrollUpState;
    if (dy > 0) m_state = ScrollDownState;

    m_dataset->scrollDomain(dx, dy, chartsGeometry().size());
    m_state = ShowState;
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}

void ChartPresenter::createBackgroundItem()
{
    if (!m_background) {
        m_background = new ChartBackground(rootItem());
        m_background->setPen(Qt::NoPen);
        m_background->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void ChartPresenter::createTitleItem()
{
    if (!m_title) {
        m_title = new ChartTitle(rootItem());
        m_title->setZValue(ChartPresenter::BackgroundZValue);
    }
}


void ChartPresenter::handleAnimationFinished()
{
    m_animations.removeAll(qobject_cast<ChartAnimation*>(sender()));
    if (m_animations.empty())
        emit animationsFinished();
}

void ChartPresenter::startAnimation(ChartAnimation* animation)
{
    if (animation->state() != QAbstractAnimation::Stopped)
        animation->stop();
    QObject::connect(animation, SIGNAL(finished()), this, SLOT(handleAnimationFinished()), Qt::UniqueConnection);
    if (!m_animations.isEmpty())
        m_animations.append(animation);
    QTimer::singleShot(0, animation, SLOT(start()));
}

void ChartPresenter::setBackgroundBrush(const QBrush& brush)
{
    createBackgroundItem();
    m_background->setBrush(brush);
    m_layout->invalidate();
}

QBrush ChartPresenter::backgroundBrush() const
{
    if (!m_background)
        return QBrush();
    return m_background->brush();
}

void ChartPresenter::setBackgroundPen(const QPen& pen)
{
    createBackgroundItem();
    m_background->setPen(pen);
    m_layout->invalidate();
}

QPen ChartPresenter::backgroundPen() const
{
    if (!m_background)
        return QPen();
    return m_background->pen();
}

void ChartPresenter::setTitle(const QString& title)
{
    createTitleItem();
    m_title->setText(title);
    m_layout->invalidate();
}

QString ChartPresenter::title() const
{
    if (!m_title)
        return QString();
    return m_title->text();
}

void ChartPresenter::setTitleFont(const QFont& font)
{
    createTitleItem();
    m_title->setFont(font);
    m_layout->invalidate();
}

QFont ChartPresenter::titleFont() const
{
    if (!m_title)
        return QFont();
    return m_title->font();
}

void ChartPresenter::setTitleBrush(const QBrush &brush)
{
    createTitleItem();
    m_title->setBrush(brush);
    m_layout->invalidate();
}

QBrush ChartPresenter::titleBrush() const
{
    if (!m_title)
        return QBrush();
    return m_title->brush();
}

void ChartPresenter::setBackgroundVisible(bool visible)
{
    createBackgroundItem();
    m_background->setVisible(visible);
}


bool ChartPresenter::isBackgroundVisible() const
{
    if (!m_background)
        return false;
    return m_background->isVisible();
}

void ChartPresenter::setBackgroundDropShadowEnabled(bool enabled)
{
    createBackgroundItem();
    m_background->setDropShadowEnabled(enabled);
}

bool ChartPresenter::isBackgroundDropShadowEnabled() const
{
    if (!m_background)
        return false;
    return m_background->isDropShadowEnabled();
}


QGraphicsLayout* ChartPresenter::layout()
{
    return m_layout;
}

void ChartPresenter::setMargins(const QMargins& margins)
{
    m_layout->setMargins(margins);
}

QMargins ChartPresenter::margins() const
{
    return m_layout->margins();
}

QLegend* ChartPresenter::legend()
{
    return m_chart->legend();
}

void ChartPresenter::setVisible(bool visible)
{
    m_chart->setVisible(visible);
}

ChartBackground* ChartPresenter::backgroundElement()
{
    return m_background;
}

QList<ChartAxis*>  ChartPresenter::axisItems() const
{
    return m_axisItems.values();
}

ChartTitle* ChartPresenter::titleElement()
{
    return m_title;
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
