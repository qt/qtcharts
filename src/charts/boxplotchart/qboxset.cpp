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

#include <QtCharts/QBoxSet>
#include <private/qboxset_p.h>
#include <private/charthelpers_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QBoxSet
    \inmodule Qt Charts
    \brief Building block for box-and-whiskers chart.

    QBoxSet represents one box-and-whiskers item. It takes five values to create a graphical representation
    of range and three medians. There are two ways to give the values. The first one is with constructor
    or stream operator (<<). The values have to be given in the following order: lower extreme,
    lower quartile, median, upper quartile and upper extreme. The Second method is to create an empty QBoxSet instance and
    give the values using setValue method.

    \sa QBoxPlotSeries
*/
/*!
    \enum QBoxSet::ValuePositions

    \value LowerExtreme
    \value LowerQuartile
    \value Median
    \value UpperQuartile
    \value UpperExtreme
*/
/*!
    \property QBoxSet::pen
    \brief Defines the pen used by the box-and-whiskers set.
*/
/*!
    \property QBoxSet::brush
    \brief Defines the brush used by the box-and-whiskers set.
*/

/*!
    \qmlproperty QString BoxSet::brushFilename
    The name of the file used as a brush for the box-and-whiskers set.
*/

/*!
    \fn void QBoxSet::clicked()
    The signal is emitted if the user clicks with a mouse on top of box-and-whisker item.
*/

/*!
    \fn void QBoxSet::pressed()
    The signal is emitted if the user presses with a mouse on top of box-and-whisker item.
*/

/*!
    \fn void QBoxSet::released()
    The signal is emitted if the user releases with a mouse on top of box-and-whisker item.
*/

/*!
    \fn void QBoxSet::doubleClicked()
    The signal is emitted if the user doubleclicks with a mouse on top of box-and-whisker item.
*/

/*!
    \fn void QBoxSet::hovered(bool status)

    The signal is emitted if mouse is hovered on top of box-and-whisker item.
    Parameter \a status is true, if mouse entered on top of item, false if mouse left from top of item.
*/
/*!
    \fn void QBoxSet::penChanged()
    This signal is emitted when the pen of the box-and-whisker item has changed.
    \sa pen
*/
/*!
    \fn void QBoxSet::brushChanged()
    This signal is emitted when the brush of the box-and-whisker item has changed.
    \sa brush
*/
/*!
    \fn void QBoxSet::valuesChanged()
    This signal is emitted when multiple values have been changed on the box-and-whisker item.
    \sa append()
*/
/*!
    \fn void QBoxSet::valueChanged(int index)
    This signal is emitted values the value in the box-and-whisker item has been modified.
    Parameter \a index indicates the position of the modified value.
    \sa at()
*/
/*!
    \fn void QBoxSet::cleared()
    This signal is emitted when all the values on the set are cleared to 0.
*/

/*!
    Constructs QBoxSet with optional \a label and parent of \a parent
*/
QBoxSet::QBoxSet(const QString label, QObject *parent)
    : QObject(parent),
      d_ptr(new QBoxSetPrivate(label, this))
{
}

/*!
    Constructs QBoxSet with given ordered values. \a le for lower extreme, \a lq for lower quartile, \a m for median,
    \a uq for upper quartile and \a ue for upper quartile. \a label and \a parent are optional.
 */
QBoxSet::QBoxSet(const qreal le, const qreal lq, const qreal m, const qreal uq, const qreal ue, const QString label, QObject *parent)
    : QObject(parent),
      d_ptr(new QBoxSetPrivate(label, this))
{
    d_ptr->append(le);
    d_ptr->append(lq);
    d_ptr->append(m);
    d_ptr->append(uq);
    d_ptr->append(ue);
}

/*!
    Destroys the boxset
*/
QBoxSet::~QBoxSet()
{
}

/*!
    Appends new value \a value to the end of set.
*/
void QBoxSet::append(const qreal value)
{
    if (d_ptr->append(value))
        emit valueChanged(d_ptr->m_appendCount - 1);
}

/*!
    Appends a list of reals to set. Works like append with single real value. The \a values in list
    are appended to end of boxset.
    \sa append()
*/
void QBoxSet::append(const QList<qreal> &values)
{
    if (d_ptr->append(values))
        emit valuesChanged();
}

/*!
    Sets new \a label for the category of the set.
*/
void QBoxSet::setLabel(const QString label)
{
    d_ptr->m_label = label;
}

/*!
    Returns the label of the the category of the set.
*/
QString QBoxSet::label() const
{
    return d_ptr->m_label;
}

/*!
    Convenience operator. Same as append, with real \a value.
    \sa append()
*/
QBoxSet &QBoxSet::operator << (const qreal &value)
{
    append(value);
    return *this;
}

/*!
    Sets a new \a value on the \a index position. For \a index ValuePositions can be used.
*/
void QBoxSet::setValue(const int index, const qreal value)
{
    d_ptr->setValue(index, value);
    emit valueChanged(index);
}

/*!
    Sets all values on the set to 0.
 */
void QBoxSet::clear()
{
    d_ptr->clear();
    emit cleared();
}

/*!
    Returns value of set indexed by \a index. For \a index ValuePositions can be used.
    If the index is out of bounds 0.0 is returned.
*/
qreal QBoxSet::at(const int index) const
{
    if (index < 0 || index >= 5)
        return 0;
    return d_ptr->m_values[index];
}

/*!
    Returns value of set indexed by \a index. For \a index ValuePositions can be used.
    If the index is out of bounds 0.0 is returned.
*/
qreal QBoxSet::operator [](const int index) const
{
    return at(index);
}

/*!
    Returns count of values appended to the set.
*/
int QBoxSet::count() const
{
    return d_ptr->m_appendCount;
}

/*!
    Sets pen for set. Boxes of this set are drawn using \a pen
*/
void QBoxSet::setPen(const QPen &pen)
{
    if (d_ptr->m_pen != pen) {
        d_ptr->m_pen = pen;
        emit d_ptr->updatedBox();
        emit penChanged();
    }
}

/*!
    Returns pen of the set.
*/
QPen QBoxSet::pen() const
{
    return d_ptr->m_pen;
}

/*!
    Sets brush for the set. Boxes of this set are drawn using \a brush
*/
void QBoxSet::setBrush(const QBrush &brush)
{
    if (d_ptr->m_brush != brush) {
        d_ptr->m_brush = brush;
        emit d_ptr->updatedBox();
        emit brushChanged();
    }
}

/*!
    Returns brush of the set.
*/
QBrush QBoxSet::brush() const
{
    return d_ptr->m_brush;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxSetPrivate::QBoxSetPrivate(const QString label, QBoxSet *parent) : QObject(parent),
    q_ptr(parent),
    m_label(label),
    m_valuesCount(5),
    m_appendCount(0),
    m_pen(QPen(Qt::NoPen)),
    m_brush(QBrush(Qt::NoBrush)),
    m_series(0)
{
    m_values = new qreal[m_valuesCount];
}

QBoxSetPrivate::~QBoxSetPrivate()
{
    delete[] m_values;
}

bool QBoxSetPrivate::append(qreal value)
{
    if (isValidValue(value) && m_appendCount < m_valuesCount) {
        m_values[m_appendCount++] = value;
        emit restructuredBox();

        return true;
    }
    return false;
}

bool QBoxSetPrivate::append(QList<qreal> values)
{
    bool success = false;

    for (int i = 0; i < values.count(); i++) {
        if (isValidValue(values.at(i)) && m_appendCount < m_valuesCount) {
            success = true;
            m_values[m_appendCount++] = values.at(i);
        }
    }

    if (success)
        emit restructuredBox();

    return success;
}

void QBoxSetPrivate::clear()
{
    m_appendCount = 0;
    for (int i = 0; i < m_valuesCount; i++)
         m_values[i] = 0.0;
    emit restructuredBox();
}

void QBoxSetPrivate::setValue(const int index, const qreal value)
{
    if (index < m_valuesCount) {
        m_values[index] = value;
        emit updatedLayout();
    }
}

qreal QBoxSetPrivate::value(const int index)
{
    if (index < 0 || index >= m_valuesCount)
        return 0;
    return m_values[index];
}

#include "moc_qboxset.cpp"
#include "moc_qboxset_p.cpp"

QT_CHARTS_END_NAMESPACE
