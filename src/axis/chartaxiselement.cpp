/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "chartaxiselement_p.h"
#include "qabstractaxis_p.h"
#include "chartpresenter_p.h"
#include "abstractchartlayout_p.h"
#include <qmath.h>
#include <QDateTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

static const char *labelFormatMatchString = "%[\\-\\+#\\s\\d\\.lhjztL]*([dicuoxfegXFEG])";
static QRegExp *labelFormatMatcher = 0;
class StaticLabelFormatMatcherDeleter
{
public:
    StaticLabelFormatMatcherDeleter() {}
    ~StaticLabelFormatMatcherDeleter() { delete labelFormatMatcher; }
};
static StaticLabelFormatMatcherDeleter staticLabelFormatMatcherDeleter;

ChartAxisElement::ChartAxisElement(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : ChartElement(item),
      m_axis(axis),
      m_animation(0),
      m_grid(new QGraphicsItemGroup(item)),
      m_arrow(new QGraphicsItemGroup(item)),
      m_shades(new QGraphicsItemGroup(item)),
      m_labels(new QGraphicsItemGroup(item)),
      m_title(new QGraphicsTextItem(item)),
      m_intervalAxis(intervalAxis)

{
    //initial initialization
    m_arrow->setHandlesChildEvents(false);
    m_arrow->setZValue(ChartPresenter::AxisZValue);
    m_labels->setZValue(ChartPresenter::AxisZValue);
    m_shades->setZValue(ChartPresenter::ShadesZValue);
    m_grid->setZValue(ChartPresenter::GridZValue);
    m_title->setZValue(ChartPresenter::GridZValue);
    handleVisibleChanged(axis->isVisible());
    connectSlots();

    setFlag(QGraphicsItem::ItemHasNoContents, true);
}

ChartAxisElement::~ChartAxisElement()
{
}

void ChartAxisElement::connectSlots()
{
    QObject::connect(axis(), SIGNAL(visibleChanged(bool)), this, SLOT(handleVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(lineVisibleChanged(bool)), this, SLOT(handleArrowVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(gridVisibleChanged(bool)), this, SLOT(handleGridVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(labelsVisibleChanged(bool)), this, SLOT(handleLabelsVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(shadesVisibleChanged(bool)), this, SLOT(handleShadesVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(labelsAngleChanged(int)), this, SLOT(handleLabelsAngleChanged(int)));
    QObject::connect(axis(), SIGNAL(linePenChanged(const QPen&)), this, SLOT(handleArrowPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(labelsPenChanged(const QPen&)), this, SLOT(handleLabelsPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(labelsBrushChanged(const QBrush&)), this, SLOT(handleLabelsBrushChanged(const QBrush&)));
    QObject::connect(axis(), SIGNAL(labelsFontChanged(const QFont&)), this, SLOT(handleLabelsFontChanged(const QFont&)));
    QObject::connect(axis(), SIGNAL(gridLinePenChanged(const QPen&)), this, SLOT(handleGridPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(shadesPenChanged(const QPen&)), this, SLOT(handleShadesPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(shadesBrushChanged(const QBrush&)), this, SLOT(handleShadesBrushChanged(const QBrush&)));
    QObject::connect(axis(), SIGNAL(titleTextChanged(const QString&)), this, SLOT(handleTitleTextChanged(const QString&)));
    QObject::connect(axis(), SIGNAL(titleFontChanged(const QFont&)), this, SLOT(handleTitleFontChanged(const QFont&)));
    QObject::connect(axis(), SIGNAL(titlePenChanged(const QPen&)), this, SLOT(handleTitlePenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(titleBrushChanged(const QBrush&)), this, SLOT(handleTitleBrushChanged(const QBrush&)));
    QObject::connect(axis(), SIGNAL(titleVisibleChanged(bool)), this, SLOT(handleTitleVisibleChanged(bool)));
    QObject::connect(axis()->d_ptr.data(), SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(handleRangeChanged(qreal, qreal)));
}

void ChartAxisElement::handleArrowVisibleChanged(bool visible)
{
    m_arrow->setVisible(visible);
}

void ChartAxisElement::handleGridVisibleChanged(bool visible)
{
    m_grid->setVisible(visible);
}

void ChartAxisElement::handleLabelsVisibleChanged(bool visible)
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
    m_labels->setVisible(visible);
}

void ChartAxisElement::handleShadesVisibleChanged(bool visible)
{
    m_shades->setVisible(visible);
}

void ChartAxisElement::handleTitleVisibleChanged(bool visible)
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
    m_title->setVisible(visible);
}

void ChartAxisElement::handleLabelsAngleChanged(int angle)
{
    foreach (QGraphicsItem *item, m_labels->childItems())
        item->setRotation(angle);

    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartAxisElement::handleLabelsPenChanged(const QPen &pen)
{
    Q_UNUSED(pen)
}

void ChartAxisElement::handleLabelsBrushChanged(const QBrush &brush)
{
    foreach (QGraphicsItem *item, m_labels->childItems())
        static_cast<QGraphicsTextItem *>(item)->setDefaultTextColor(brush.color());
}

void ChartAxisElement::handleLabelsFontChanged(const QFont &font)
{
    foreach (QGraphicsItem *item, m_labels->childItems())
        static_cast<QGraphicsTextItem *>(item)->setFont(font);
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartAxisElement::handleTitleTextChanged(const QString &title)
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
    m_title->setHtml(title);
}

void ChartAxisElement::handleTitlePenChanged(const QPen &pen)
{
    Q_UNUSED(pen)
}

void ChartAxisElement::handleTitleBrushChanged(const QBrush &brush)
{
    m_title->setDefaultTextColor(brush.color());
}

void ChartAxisElement::handleTitleFontChanged(const QFont &font)
{
    if (m_title->font() != font) {
        m_title->setFont(font);
        QGraphicsLayoutItem::updateGeometry();
        presenter()->layout()->invalidate();
    }
}

void ChartAxisElement::handleVisibleChanged(bool visible)
{
    setVisible(visible);
    if (!visible) {
        m_grid->setVisible(visible);
        m_arrow->setVisible(visible);
        m_shades->setVisible(visible);
        m_labels->setVisible(visible);
        m_title->setVisible(visible);
    } else {
        m_grid->setVisible(axis()->isGridLineVisible());
        m_arrow->setVisible(axis()->isLineVisible());
        m_shades->setVisible(axis()->shadesVisible());
        m_labels->setVisible(axis()->labelsVisible());
        m_title->setVisible(axis()->isTitleVisible());
    }

    if (presenter()) presenter()->layout()->invalidate();
}

void ChartAxisElement::handleRangeChanged(qreal min, qreal max)
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
            // We don't want to call invalidate on layout, since it will change minimum size of
            // component, which we would like to avoid since it causes nasty flips when scrolling
            // or zooming, instead recalculate layout and use plotArea for extra space.
            presenter()->layout()->setGeometry(presenter()->layout()->geometry());
        }
    }
}

bool ChartAxisElement::isEmpty()
{
    return axisGeometry().isEmpty()
           || gridGeometry().isEmpty()
           || qFuzzyCompare(min(), max());
}

qreal ChartAxisElement::min() const
{
    return m_axis->d_ptr->min();
}

qreal ChartAxisElement::max() const
{
    return m_axis->d_ptr->max();
}

static void appendFormattedLabel(const QString &capStr, const QByteArray &array,
                                 QStringList &labels, qreal value)
{
    if (capStr.isEmpty()) {
        labels << QString();
    } else if (capStr.at(0) == QLatin1Char('d')
        || capStr.at(0) == QLatin1Char('i')
        || capStr.at(0) == QLatin1Char('c')) {
        labels << QString().sprintf(array, (qint64)value);
    } else if (capStr.at(0) == QLatin1Char('u')
             || capStr.at(0) == QLatin1Char('o')
             || capStr.at(0) == QLatin1Char('x')
             || capStr.at(0) == QLatin1Char('X')) {
        labels << QString().sprintf(array, (quint64)value);
    } else if (capStr.at(0) == QLatin1Char('f')
               || capStr.at(0) == QLatin1Char('F')
               || capStr.at(0) == QLatin1Char('e')
               || capStr.at(0) == QLatin1Char('E')
               || capStr.at(0) == QLatin1Char('g')
               || capStr.at(0) == QLatin1Char('G')) {
        labels << QString().sprintf(array, value);
    } else {
        labels << QString();
    }
}

QStringList ChartAxisElement::createValueLabels(qreal min, qreal max, int ticks, const QString &format)
{
    QStringList labels;

    if (max <= min || ticks < 1)
        return labels;

    int n = qMax(int(-qFloor(log10((max - min) / (ticks - 1)))), 0);
    n++;

    if (format.isNull()) {
        for (int i = 0; i < ticks; i++) {
            qreal value = min + (i * (max - min) / (ticks - 1));
            labels << QString::number(value, 'f', n);
        }
    } else {
        QByteArray array = format.toLatin1();
        QString capStr;
        if (!labelFormatMatcher)
            labelFormatMatcher = new QRegExp(labelFormatMatchString);
        if (labelFormatMatcher->indexIn(format, 0) != -1)
            capStr = labelFormatMatcher->cap(1);
        for (int i = 0; i < ticks; i++) {
            qreal value = min + (i * (max - min) / (ticks - 1));
            appendFormattedLabel(capStr, array, labels, value);
        }
    }

    return labels;
}

QStringList ChartAxisElement::createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString &format)
{
    QStringList labels;

    if (max <= min || ticks < 1)
        return labels;

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
        QString capStr;
        if (!labelFormatMatcher)
            labelFormatMatcher = new QRegExp(labelFormatMatchString);
        if (labelFormatMatcher->indexIn(format, 0) != -1)
            capStr = labelFormatMatcher->cap(1);
        for (int i = firstTick; i < ticks + firstTick; i++) {
            qreal value = qPow(base, i);
            appendFormattedLabel(capStr, array, labels, value);
        }
    }

    return labels;
}

QStringList ChartAxisElement::createDateTimeLabels(qreal min, qreal max,int ticks,const QString &format)
{
    QStringList labels;

    if (max <= min || ticks < 1)
        return labels;

    int n = qMax(int(-floor(log10((max - min) / (ticks - 1)))), 0);
    n++;
    for (int i = 0; i < ticks; i++) {
        qreal value = min + (i * (max - min) / (ticks - 1));
        labels << QDateTime::fromMSecsSinceEpoch(value).toString(format);
    }
    return labels;
}

void ChartAxisElement::axisSelected()
{
    emit clicked();
}

#include "moc_chartaxiselement_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
