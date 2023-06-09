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

#include <private/chartaxiselement_p.h>
#include <private/qabstractaxis_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCharts/QCategoryAxis>
#include <QtCore/QtMath>
#include <QtCore/QDateTime>
#include <QtCore/QRegularExpression>
#include <QtGui/QTextDocument>
#include <cmath>

QT_CHARTS_BEGIN_NAMESPACE

static const char *labelFormatMatchString = "%[\\-\\+#\\s\\d\\.\\'lhjztL]*([dicuoxfegXFEG])";
static const char *labelFormatMatchLocalizedString = "^([^%]*)%\\.(\\d+)([defgiEG])(.*)$";
static QRegularExpression *labelFormatMatcher = 0;
static QRegularExpression *labelFormatMatcherLocalized = 0;
class StaticLabelFormatMatcherDeleter
{
public:
    StaticLabelFormatMatcherDeleter() {}
    ~StaticLabelFormatMatcherDeleter() {
        delete labelFormatMatcher;
        delete labelFormatMatcherLocalized;
    }
};
static StaticLabelFormatMatcherDeleter staticLabelFormatMatcherDeleter;

ChartAxisElement::ChartAxisElement(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis)
    : ChartElement(item),
      m_axis(axis),
      m_animation(0),
      m_grid(new QGraphicsItemGroup(item)),
      m_arrow(new QGraphicsItemGroup(item)),
      m_minorGrid(new QGraphicsItemGroup(item)),
      m_minorArrow(new QGraphicsItemGroup(item)),
      m_shades(new QGraphicsItemGroup(item)),
      m_labels(new QGraphicsItemGroup(item)),
      m_title(new QGraphicsTextItem(item)),
      m_intervalAxis(intervalAxis)

{
    //initial initialization
    m_arrow->setHandlesChildEvents(false);
    m_arrow->setZValue(ChartPresenter::AxisZValue);
    m_minorArrow->setHandlesChildEvents(false);
    m_minorArrow->setZValue(ChartPresenter::AxisZValue);
    m_labels->setZValue(ChartPresenter::AxisZValue);
    m_shades->setZValue(ChartPresenter::ShadesZValue);
    m_grid->setZValue(ChartPresenter::GridZValue);
    m_minorGrid->setZValue(ChartPresenter::GridZValue);
    m_title->setZValue(ChartPresenter::GridZValue);
    m_title->document()->setDocumentMargin(ChartPresenter::textMargin());
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
    QObject::connect(axis(), SIGNAL(labelsBrushChanged(const QBrush&)), this, SLOT(handleLabelsBrushChanged(const QBrush&)));
    QObject::connect(axis(), SIGNAL(labelsFontChanged(const QFont&)), this, SLOT(handleLabelsFontChanged(const QFont&)));
    QObject::connect(axis(), SIGNAL(gridLinePenChanged(const QPen&)), this, SLOT(handleGridPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(shadesPenChanged(const QPen&)), this, SLOT(handleShadesPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(shadesBrushChanged(const QBrush&)), this, SLOT(handleShadesBrushChanged(const QBrush&)));
    QObject::connect(axis(), SIGNAL(titleTextChanged(const QString&)), this, SLOT(handleTitleTextChanged(const QString&)));
    QObject::connect(axis(), SIGNAL(titleFontChanged(const QFont&)), this, SLOT(handleTitleFontChanged(const QFont&)));
    QObject::connect(axis(), SIGNAL(titleBrushChanged(const QBrush&)), this, SLOT(handleTitleBrushChanged(const QBrush&)));
    QObject::connect(axis(), SIGNAL(titleVisibleChanged(bool)), this, SLOT(handleTitleVisibleChanged(bool)));
    QObject::connect(axis()->d_ptr.data(), SIGNAL(rangeChanged(qreal, qreal)), this, SLOT(handleRangeChanged(qreal, qreal)));
    QObject::connect(axis(), SIGNAL(reverseChanged(bool)), this, SLOT(handleReverseChanged(bool)));
    QObject::connect(axis(), SIGNAL(lineVisibleChanged(bool)),
                     this, SLOT(handleMinorArrowVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(linePenChanged(const QPen&)), this,
                     SLOT(handleMinorArrowPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(minorGridVisibleChanged(bool)),
                     this, SLOT(handleMinorGridVisibleChanged(bool)));
    QObject::connect(axis(), SIGNAL(minorGridLinePenChanged(const QPen&)),
                     this, SLOT(handleMinorGridPenChanged(const QPen&)));
    QObject::connect(axis(), SIGNAL(gridLineColorChanged(const QColor&)),
                     this, SLOT(handleGridLineColorChanged(const QColor&)));
    QObject::connect(axis(), SIGNAL(minorGridLineColorChanged(const QColor&)),
                     this, SLOT(handleMinorGridLineColorChanged(const QColor&)));

    if (axis()->type() == QAbstractAxis::AxisTypeCategory) {
        QCategoryAxis *categoryAxis = static_cast<QCategoryAxis *>(axis());
        QObject::connect(categoryAxis,
                         SIGNAL(labelsPositionChanged(QCategoryAxis::AxisLabelsPosition)),
                         this, SLOT(handleLabelsPositionChanged()));
    }
}

void ChartAxisElement::handleArrowVisibleChanged(bool visible)
{
    m_arrow->setVisible(visible);
}

void ChartAxisElement::handleMinorArrowVisibleChanged(bool visible)
{
    m_minorArrow->setVisible(visible);
}

void ChartAxisElement::handleGridVisibleChanged(bool visible)
{
    m_grid->setVisible(visible);
}

void ChartAxisElement::handleMinorGridVisibleChanged(bool visible)
{
    m_minorGrid->setVisible(visible);
}

void ChartAxisElement::handleLabelsPositionChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

void ChartAxisElement::valueLabelEdited(qreal oldValue, qreal newValue)
{
    qreal range = max() - min();
    qreal center = ((max() - min()) / 2.0) + min();
    qreal newRange = 0.0;
    auto label = static_cast<ValueAxisLabel *>(this->sender());
    if ((oldValue >= center && newValue >= min())
     || (oldValue <  center && newValue >= max() && oldValue != min())) {
        newRange = range * ((newValue - min()) / (oldValue - min()));
        if (newRange > 0) {
            m_axis->setRange(min(), min() + newRange);
            return;
        }
    } else if ((oldValue >= center && newValue <= min() && max() != oldValue)
            || (oldValue <  center && newValue <  max())) {
        newRange = range * ((max() - newValue) / (max() - oldValue));
        if (newRange > 0) {
            m_axis->setRange(max() - newRange, max());
            return;
        }
    }
    label->reloadBeforeEditContent();
}

void ChartAxisElement::dateTimeLabelEdited(const QDateTime &oldTime, const QDateTime &newTime)
{
    qreal range = max() - min();
    qreal center = ((max() - min()) / 2.0) + min();
    qreal newRange = 0.0;
    qint64 oldValue = oldTime.toMSecsSinceEpoch();
    qint64 newValue = newTime.toMSecsSinceEpoch();
    if ((oldValue >= center && newValue >= min())
     || (oldValue <  center && newValue >= max() && oldValue != min())) {
        newRange = range * ((newValue - min()) / (oldValue - min()));
        if (newRange > 0) {
            m_axis->setRange(
                        QDateTime::fromMSecsSinceEpoch(min()),
                        QDateTime::fromMSecsSinceEpoch(min() + newRange));
            return;
        }
    } else if ((oldValue >= center && newValue <= min() && max() != oldValue)
            || (oldValue <  center && newValue <  max())) {
        newRange = range * ((max() - newValue) / (max() - oldValue));
        if (newRange > 0) {
            m_axis->setRange(max() - newRange, max());
            m_axis->setRange(
                        QDateTime::fromMSecsSinceEpoch(max() - newRange),
                        QDateTime::fromMSecsSinceEpoch(max()));
            return;
        }
    }
    static_cast<DateTimeAxisLabel *>(this->sender())->reloadBeforeEditContent();
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
    if (title.isEmpty() || !m_title->isVisible())
        m_title->setHtml(title);
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
        m_minorGrid->setVisible(visible);
        m_minorArrow->setVisible(visible);
        m_shades->setVisible(visible);
        m_labels->setVisible(visible);
        m_title->setVisible(visible);
    } else {
        m_grid->setVisible(axis()->isGridLineVisible());
        m_arrow->setVisible(axis()->isLineVisible());
        m_minorGrid->setVisible(axis()->isMinorGridLineVisible());
        m_minorArrow->setVisible(axis()->isLineVisible());
        m_shades->setVisible(axis()->shadesVisible());
        m_labels->setVisible(axis()->labelsVisible());
        m_title->setVisible(axis()->isTitleVisible());
    }
    if (presenter()) {
        if (visible) {
            QSizeF before = effectiveSizeHint(Qt::PreferredSize);
            QSizeF after = sizeHint(Qt::PreferredSize);
            if (before != after)
                QGraphicsLayoutItem::updateGeometry();
        }
        presenter()->layout()->invalidate();
    }
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

void ChartAxisElement::handleReverseChanged(bool reverse)
{
    Q_UNUSED(reverse);

    QGraphicsLayoutItem::updateGeometry();
    presenter()->layout()->invalidate();
}

bool ChartAxisElement::isEmpty()
{
    return axisGeometry().isEmpty()
           || gridGeometry().isEmpty()
           || qFuzzyIsNull(max() - min());
}

qreal ChartAxisElement::min() const
{
    return m_axis->d_ptr->min();
}

qreal ChartAxisElement::max() const
{
    return m_axis->d_ptr->max();
}

qreal ChartAxisElement::tickInterval() const
{
    QValueAxis *valueAxis = qobject_cast<QValueAxis *>(m_axis);
    if (valueAxis)
        return valueAxis->tickInterval();
    else
        return 0.0;
}

qreal ChartAxisElement::tickAnchor() const
{
    QValueAxis *valueAxis = qobject_cast<QValueAxis *>(m_axis);
    if (valueAxis)
        return valueAxis->tickAnchor();
    else
        return 0.0;
}

QString ChartAxisElement::formatLabel(const QString &formatSpec, const QByteArray &array,
                                      qreal value, int precision, const QString &preStr,
                                      const QString &postStr) const
{
    QString retVal;
    if (!formatSpec.isEmpty()) {
        if (formatSpec.at(0) == QLatin1Char('d')
            || formatSpec.at(0) == QLatin1Char('i')
            || formatSpec.at(0) == QLatin1Char('c')) {
            if (presenter()->localizeNumbers())
                retVal = preStr + presenter()->locale().toString(qint64(value)) + postStr;
            else
                retVal = QString::asprintf(array.constData(), qint64(value));
        } else if (formatSpec.at(0) == QLatin1Char('u')
                 || formatSpec.at(0) == QLatin1Char('o')
                 || formatSpec.at(0) == QLatin1Char('x')
                 || formatSpec.at(0) == QLatin1Char('X')) {
            // These formats are not supported by localized numbers
            retVal = QString::asprintf(array.constData(), quint64(value));
        } else if (formatSpec.at(0) == QLatin1Char('f')
                   || formatSpec.at(0) == QLatin1Char('F')
                   || formatSpec.at(0) == QLatin1Char('e')
                   || formatSpec.at(0) == QLatin1Char('E')
                   || formatSpec.at(0) == QLatin1Char('g')
                   || formatSpec.at(0) == QLatin1Char('G')) {
            if (presenter()->localizeNumbers()) {
                retVal = preStr
                        + presenter()->locale().toString(value, formatSpec.at(0).toLatin1(),
                                                         precision)
                        + postStr;
            } else {
                retVal = QString::asprintf(array.constData(), value);
            }
        }
    }
    return retVal;
}

QStringList ChartAxisElement::createValueLabels(qreal min, qreal max, int ticks,
                                                qreal tickInterval, qreal tickAnchor,
                                                QValueAxis::TickType tickType,
                                                const QString &format) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
        return labels;

    if (format.isEmpty()) {
        // Calculate how many decimal digits are needed to show difference between ticks,
        // for example tick marks 1.002 and 1.003 have a difference of 0.001 and need 3 decimals.
        // For differences >= 1 (positive log10) use always 1 decimal.
        double l10 = std::log10((max - min) / (ticks - 1));
        int n = qMax(int(-qFloor(l10)), 0) + 1;
        if (tickType == QValueAxis::TicksFixed) {
            for (int i = 0; i < ticks; i++) {
                qreal value = min + (i * (max - min) / (ticks - 1));
                labels << presenter()->numberToString(value, 'f', n);
            }
        } else {
            const qreal ticksFromAnchor = (tickAnchor - min) / tickInterval;
            const qreal firstMajorTick = tickAnchor - std::floor(ticksFromAnchor) * tickInterval;

            qreal value = firstMajorTick;
            while (value <= max) {
                labels << presenter()->numberToString(value, 'f', n);
                value += tickInterval;
            }
        }
    } else {
        QByteArray array = format.toLatin1();
        QString formatSpec;
        QString preStr;
        QString postStr;
        int precision = 6; // Six is the default precision in Qt API
        if (presenter()->localizeNumbers()) {
            if (!labelFormatMatcherLocalized)
                labelFormatMatcherLocalized
                        = new QRegularExpression(QString::fromLatin1(labelFormatMatchLocalizedString));
            QRegularExpressionMatch rmatch;
            if (format.indexOf(*labelFormatMatcherLocalized, 0, &rmatch) != -1) {
                preStr = rmatch.captured(1);
                if (!rmatch.captured(2).isEmpty())
                    precision = rmatch.captured(2).toInt();
                formatSpec = rmatch.captured(3);
                postStr = rmatch.captured(4);
            }
        } else {
            if (!labelFormatMatcher)
                labelFormatMatcher = new QRegularExpression(QString::fromLatin1(labelFormatMatchString));
            QRegularExpressionMatch rmatch;
            if (format.indexOf(*labelFormatMatcher, 0, &rmatch) != -1)
                formatSpec = rmatch.captured(1);
        }
        if (tickType == QValueAxis::TicksFixed) {
            for (int i = 0; i < ticks; i++) {
                qreal value = min + (i * (max - min) / (ticks - 1));
                labels << formatLabel(formatSpec, array, value, precision, preStr, postStr);
            }
        } else {
            const qreal ticksFromAnchor = (tickAnchor - min) / tickInterval;
            const qreal firstMajorTick = tickAnchor - std::floor(ticksFromAnchor) * tickInterval;

            qreal value = firstMajorTick;
            while (value <= max) {
                labels << formatLabel(formatSpec, array, value, precision, preStr, postStr);
                value += tickInterval;
            }
        }
    }

    return labels;
}

QStringList ChartAxisElement::createLogValueLabels(qreal min, qreal max, qreal base, int ticks,
                                                   const QString &format) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
        return labels;

    int firstTick;
    if (base > 1)
        firstTick = qCeil(std::log10(min) / std::log10(base));
    else
        firstTick = qCeil(std::log10(max) / std::log10(base));

    if (format.isEmpty()) {
        int n = 0;
        if (ticks > 1)
            n = qMax(int(-qFloor(std::log10((max - min) / (ticks - 1)))), 0);
        n++;
        for (int i = firstTick; i < ticks + firstTick; i++) {
            qreal value = qPow(base, i);
            labels << presenter()->numberToString(value, 'f', n);
        }
    } else {
        QByteArray array = format.toLatin1();
        QString formatSpec;
        QString preStr;
        QString postStr;
        int precision = 6; // Six is the default precision in Qt API
        if (presenter()->localizeNumbers()) {
            if (!labelFormatMatcherLocalized)
                labelFormatMatcherLocalized =
                        new QRegularExpression(QString::fromLatin1(labelFormatMatchLocalizedString));
            QRegularExpressionMatch rmatch;
            if (format.indexOf(*labelFormatMatcherLocalized, 0, &rmatch) != -1) {
                preStr = rmatch.captured(1);
                if (!rmatch.captured(2).isEmpty())
                    precision = rmatch.captured(2).toInt();
                formatSpec = rmatch.captured(3);
                postStr = rmatch.captured(4);
            }
        } else {
            if (!labelFormatMatcher)
                labelFormatMatcher = new QRegularExpression(QString::fromLatin1(labelFormatMatchString));
            QRegularExpressionMatch rmatch;
            if (format.indexOf(*labelFormatMatcher, 0, &rmatch) != -1)
                formatSpec = rmatch.captured(1);
        }
        for (int i = firstTick; i < ticks + firstTick; i++) {
            qreal value = qPow(base, i);
            labels << formatLabel(formatSpec, array, value, precision, preStr, postStr);
        }
    }

    return labels;
}

QStringList ChartAxisElement::createDateTimeLabels(qreal min, qreal max,int ticks,
                                                   const QString &format) const
{
    QStringList labels;

    if (max <= min || ticks < 1)
        return labels;

    for (int i = 0; i < ticks; i++) {
        qreal value = min + (i * (max - min) / (ticks - 1));
        labels << presenter()->locale().toString(QDateTime::fromMSecsSinceEpoch(value), format);
    }
    return labels;
}


bool ChartAxisElement::labelsEditable() const
{
    return m_labelsEditable;
}

void ChartAxisElement::setLabelsEditable(bool labelsEditable)
{
    if (axis()->type() == QAbstractAxis::AxisTypeValue
            || axis()->type() == QAbstractAxis::AxisTypeDateTime) {
        labelGroup()->setHandlesChildEvents(!labelsEditable);
        const QList<QGraphicsItem *> childItems = labelGroup()->childItems();
        for (auto item : childItems) {
            switch (axis()->type()) {
            case QtCharts::QAbstractAxis::AxisTypeValue:
                static_cast<ValueAxisLabel *>(item)->setEditable(labelsEditable);
                break;
            case QtCharts::QAbstractAxis::AxisTypeDateTime:
                static_cast<DateTimeAxisLabel *>(item)->setEditable(labelsEditable);
                break;
            default:
                break;
            }
        }
        m_labelsEditable = labelsEditable;
    }
}

void ChartAxisElement::axisSelected()
{
    emit clicked();
}

QT_CHARTS_END_NAMESPACE

#include "moc_chartaxiselement_p.cpp"
