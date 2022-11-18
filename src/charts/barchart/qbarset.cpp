// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>
#include <private/charthelpers_p.h>
#include <private/qchart_p.h>

QT_BEGIN_NAMESPACE

/*!
    \class QBarSet
    \inmodule QtCharts
    \brief The QBarSet class represents one set of bars in a bar chart.

    A bar set contains one data value for each category. The first value of a set is assumed to
    belong to the first category, the second one to the second category, and so on. If the set has
    fewer values than there are categories, the missing values are assumed to be located at the end
    of the set. For missing values in the middle of a set, the numerical value of zero is used.
    Labels for zero value sets are not shown.

    \sa QAbstractBarSeries, QBarSeries, QStackedBarSeries, QPercentBarSeries
    \sa QHorizontalBarSeries, QHorizontalStackedBarSeries, QHorizontalPercentBarSeries
*/
/*!
    \qmltype BarSet
    \instantiates QBarSet
    \inqmlmodule QtCharts

    \brief Represents one set of bars in a bar chart.

    A bar set contains one data value for each category. The first value of a set is assumed to
    belong to the first category, the second one to the second category, and so on. If the set has
    fewer values than there are categories, the missing values are assumed to be located at the end
    of the set. For missing values in the middle of a set, the numerical value of zero is used.
    Labels for zero value sets are not shown.

    \sa AbstractBarSeries, BarSeries, StackedBarSeries, PercentBarSeries
    \sa HorizontalBarSeries, HorizontalStackedBarSeries, HorizontalPercentBarSeries

*/

/*!
    \property QBarSet::label
    \brief The label of the bar set.
*/
/*!
    \qmlproperty string BarSet::label
    The label of the bar set.
*/

/*!
    \property QBarSet::pen
    \brief The pen used to draw the lines of bars in the bar set.
*/

/*!
    \property QBarSet::brush
    \brief The brush used to fill the bars in the bar set.
*/

/*!
    \qmlproperty string BarSet::brushFilename
    The name of the file used as a brush for the set.
*/

/*!
    \property QBarSet::labelBrush
    \brief The brush used to draw the bar set's label.
*/

/*!
    \property QBarSet::labelFont
    \brief The font used to draw the bar set's label.
*/

/*!
    \qmlproperty font BarSet::labelFont
    The font used to draw the bar set's label.

    For more information, see \l [QML]{font}.
*/

/*!
    \property QBarSet::color
    \brief The fill (brush) color of the bar set.
*/
/*!
    \qmlproperty color BarSet::color
    The fill (brush) color of the bar set.
*/

/*!
    \property QBarSet::borderColor
    \brief The line (pen) color of the bar set.
*/
/*!
    \qmlproperty color BarSet::borderColor
    The line (pen) color of the bar set.
*/

/*!
    \qmlproperty real BarSet::borderWidth
    The width of the border line. By default, the width is 2.0.
*/

/*!
    \property QBarSet::labelColor
    \brief The text (label) color of the bar set.
*/
/*!
    \qmlproperty color BarSet::labelColor
    The text (label) color of the bar set.
*/

/*!
    \fn void QBarSet::clicked(int index)

    This signal is emitted when the user clicks the bar specified by \a index in a bar set.
*/

/*!
    \qmlmethod BarSet::clicked(int index)

    This signal is emitted when the user clicks the bar specified by \a index
    in a bar set.

    The corresponding signal handler is \c onClicked.
*/

/*!
    \fn void QBarSet::pressed(int index)

    This signal is emitted when the user clicks the bar specified by \a index in a bar set
    and holds down the mouse button.
*/

/*!
    \qmlmethod BarSet::pressed(int index)

    This signal is emitted when the user clicks the bar specified by \a index in
    a bar set and holds down the mouse button.

    The corresponding signal handler is \c onPressed.
*/

/*!
    \fn void QBarSet::released(int index)

    This signal is emitted when the user releases the mouse press on the bar specified by
    \a index in a bar set.
*/

/*!
    \qmlmethod BarSet::released(int index)

    This signal is emitted when the user releases the mouse press on the bar
    specified by \a index in a bar set.

    The corresponding signal handler is \c onReleased.
*/

/*!
    \fn void QBarSet::doubleClicked(int index)

    This signal is emitted when the user double-clicks the bar specified by \a index in a bar set.
*/

/*!
    \qmlmethod BarSet::doubleClicked(int index)

    This signal is emitted when the user double-clicks the bar specified by
    \a index in a bar set.

    The corresponding signal handler is \c onDoubleClicked.
*/

/*!
    \fn void QBarSet::hovered(bool status, int index)

    This signal is emitted when a mouse is hovered over the bar specified by \a index in a bar set.
    When the mouse moves over the bar, \a status turns \c true, and when the mouse moves away again,
    it turns \c false.
*/


/*!
    \fn void QBarSet::labelChanged()
    This signal is emitted when the label of the bar set changes.
    \sa label
*/

/*!
    \fn void QBarSet::penChanged()
    This signal is emitted when the pen used to draw the bar set changes.
    \sa pen
*/

/*!
    \fn void QBarSet::brushChanged()
    This signal is emitted when the brush used to draw the bar set changes.
    \sa brush
*/

/*!
    \fn void QBarSet::labelBrushChanged()
    This signal is emitted when the brush used to draw the bar set's label changes.
    \sa labelBrush
*/

/*!
    \fn void QBarSet::labelFontChanged()
    This signal is emitted when the font of the bar set's label changes.
    \sa labelBrush
*/

/*!
    \fn void QBarSet::colorChanged(QColor)
    This signal is emitted when the fill (brush) color of the bar set changes to \a color.
*/

/*!
    \fn void QBarSet::borderColorChanged(QColor)
    This signal is emitted when the line (pen) color of the bar set changes to \a color.
*/

/*!
    \fn void QBarSet::labelColorChanged(QColor)
    This signal is emitted when the text (label) color of the bar set changes to \a color.
*/

/*!
    \fn void QBarSet::valuesAdded(int index, int count)
    This signal is emitted when new values are added to the bar set.
    \a index indicates the position of the first inserted value, and \a count is the number
    of inserted values.
    \sa append(), insert()
*/
/*!
    \qmlsignal BarSet::valuesAdded(int index, int count)
    This signal is emitted when new values are added to the bar set.
    \a index indicates the position of the first inserted value, and \a count is the number
    of inserted values.

    The corresponding signal handler is \c onValuesAdded.
*/

/*!
    \fn void QBarSet::valuesRemoved(int index, int count)
    This signal is emitted when values are removed from the bar set.
    \a index indicates the position of the first removed value, and \a count is the number
    of removed values.
    \sa remove()
*/
/*!
    \qmlsignal BarSet::valuesRemoved(int index, int count)
    This signal is emitted when values are removed from the bar set.
    \a index indicates the position of the first removed value, and \a count is the number
    of removed values.

    The corresponding signal handler is \c onValuesRemoved.
*/

/*!
    \fn void QBarSet::valueChanged(int index)
    This signal is emitted when the value at the position specified by \a index is modified.
    \sa at()
*/
/*!
    \qmlsignal BarSet::valueChanged(int index)
    This signal is emitted when the value at the position specified by \a index is modified.

    The corresponding signal handler is \c onValueChanged.
*/

/*!
    \qmlproperty int BarSet::count
    The number of values in the bar set.
*/

/*!
    \qmlproperty QVariantList BarSet::values
    The values of the bar set. You can set a list of either \l [QML]{real} or \l [QML]{point}
    types as values.

    If you set a list of real types as values, they directly define the bar set values.

    If you set a list of point types as values, the x-coordinate of the point specifies its
    zero-based index in the bar set. The size of the bar set is the highest x-coordinate value + 1.
    If a point is missing for any x-coordinate between zero and the highest value,
    it gets the value zero.

    For example, the following bar sets have equal values:
    \code
        myBarSet1.values = [5, 0, 1, 5];
        myBarSet2.values = [Qt.point(0, 5), Qt.point(2, 1), Qt.point(3, 5)];
    \endcode
*/

/*!
    Constructs a bar set with the label \a label and the parent \a parent.
*/
QBarSet::QBarSet(const QString label, QObject *parent)
    : QObject(parent),
      d_ptr(new QBarSetPrivate(label, this))
{
}

/*!
    Removes the bar set.
*/
QBarSet::~QBarSet()
{
    // NOTE: d_ptr destroyed by QObject
}

/*!
    Sets \a label as the new label for the bar set.
*/
void QBarSet::setLabel(const QString label)
{
    d_ptr->m_label = label;
    d_ptr->setLabelsDirty(true);
    emit labelChanged();
}

/*!
    Returns the label of the bar set.
*/
QString QBarSet::label() const
{
    return d_ptr->m_label;
}

/*!
    \qmlmethod BarSet::append(real value)
    Appends the new value specified by \a value to the end of the bar set.
*/

/*!
    Appends the new value specified by \a value to the end of the bar set.
*/
void QBarSet::append(const qreal value)
{
    // Convert to QPointF
    int index = d_ptr->m_values.size();
    d_ptr->append(QPointF(d_ptr->m_values.size(), value));
    emit valuesAdded(index, 1);
}

/*!
    Appends the list of real values specified by \a values to the end of the bar set.

    \sa append()
*/
void QBarSet::append(const QList<qreal> &values)
{
    int index = d_ptr->m_values.size();
    d_ptr->append(values);
    emit valuesAdded(index, values.size());
}

/*!
    A convenience operator for appending the real value specified by \a value to the end of the
    bar set.

    \sa append()
*/
QBarSet &QBarSet::operator << (const qreal &value)
{
    append(value);
    return *this;
}

/*!
    Inserts \a value in the position specified by \a index.
    The values following the inserted value are moved up one position.

    \sa remove()
*/
void QBarSet::insert(const int index, const qreal value)
{
    d_ptr->insert(index, value);

    bool callSignal = false;
    if (!d_ptr->m_selectedBars.isEmpty()) {
        // if value was inserted we need to move already selected bars by 1
        QSet<int> selectedAfterInsert;
        for (const auto &value : std::as_const(d_ptr->m_selectedBars)) {
            if (value >= index) {
                selectedAfterInsert << value + 1;
                callSignal = true;
            } else {
                selectedAfterInsert << value;
            }
        }
        d_ptr->m_selectedBars = selectedAfterInsert;
    }

    emit valuesAdded(index, 1);
    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
    \qmlmethod BarSet::remove(int index, int count)
    Removes the number of values specified by \a count from the bar set starting
    with the value specified by \a index.

    If you leave out \a count, only the value specified by \a index is removed.
*/

/*!
    Removes the number of values specified by \a count from the bar set starting with
    the value specified by \a index.
    \sa insert()
*/
void QBarSet::remove(const int index, const int count)
{
    int removedCount = d_ptr->remove(index, count);
    if (removedCount > 0)
        emit valuesRemoved(index, removedCount);
    return;
}

/*!
    \qmlmethod BarSet::replace(int index, real value)
    Adds the value specified by \a value to the bar set at the position
    specified by \a index.
*/

/*!
    Adds the value specified by \a value to the bar set at the position specified by \a index.
*/
void QBarSet::replace(const int index, const qreal value)
{
    if (index >= 0 && index < d_ptr->m_values.size()) {
        d_ptr->replace(index, value);
        emit valueChanged(index);
    }
}

/*!
    \qmlmethod BarSet::at(int index)
    Returns the value specified by \a index from the bar set.
    If the index is out of bounds, 0.0 is returned.
*/

/*!
    Returns the value specified by \a index from the bar set.
    If the index is out of bounds, 0.0 is returned.
*/
qreal QBarSet::at(const int index) const
{
    if (index < 0 || index >= d_ptr->m_values.size())
        return 0;
    return d_ptr->m_values.at(index).y();
}

/*!
    Returns the value of the bar set specified by \a index.
    If the index is out of bounds, 0.0 is returned.
*/
qreal QBarSet::operator [](const int index) const
{
    return at(index);
}

/*!
    Returns the number of values in a bar set.
*/
int QBarSet::count() const
{
    return d_ptr->m_values.size();
}

/*!
    Returns the sum of all values in the bar set.
*/
qreal QBarSet::sum() const
{
    qreal total(0);
    for (int i = 0; i < d_ptr->m_values.size(); i++)
        total += d_ptr->m_values.at(i).y();
    return total;
}

/*!
    Sets the pen used to draw the lines in the bar set to \a pen.
*/
void QBarSet::setPen(const QPen &pen)
{
    if (d_ptr->m_pen != pen) {
        d_ptr->m_pen = pen;
        d_ptr->setVisualsDirty(true);
        emit d_ptr->updatedBars();
        emit penChanged();
    }
}

/*!
    Returns the pen used to draw the lines in the bar set.
*/
QPen QBarSet::pen() const
{
    if (d_ptr->m_pen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d_ptr->m_pen;
}

/*!
    Sets the brush used to fill the bars in the bar set to \a brush.
*/
void QBarSet::setBrush(const QBrush &brush)
{
    if (d_ptr->m_brush != brush) {
        d_ptr->m_brush = brush;
        d_ptr->setVisualsDirty(true);
        emit d_ptr->updatedBars();
        emit brushChanged();
    }
}

/*!
    Returns the brush used to fill the bars in the bar set.
*/
QBrush QBarSet::brush() const
{
    if (d_ptr->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d_ptr->m_brush;
}

/*!
    Sets the brush used to draw values on top of this bar set to \a brush.
*/
void QBarSet::setLabelBrush(const QBrush &brush)
{
    if (d_ptr->m_labelBrush != brush) {
        d_ptr->m_labelBrush = brush;
        d_ptr->setLabelsDirty(true);
        emit d_ptr->updatedBars();
        emit labelBrushChanged();
    }
}

/*!
    Returns the brush used to draw values on top of this bar set.
*/
QBrush QBarSet::labelBrush() const
{
    if (d_ptr->m_labelBrush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d_ptr->m_labelBrush;
}

/*!
    Sets the font used to draw values on top of this bar set to \a font.
*/
void QBarSet::setLabelFont(const QFont &font)
{
    if (d_ptr->m_labelFont != font) {
        d_ptr->m_labelFont = font;
        d_ptr->setLabelsDirty(true);
        emit d_ptr->updatedBars();
        emit labelFontChanged();
    }
}

/*!
    Returns the pen used to draw values on top of this bar set.
*/
QFont QBarSet::labelFont() const
{
    return d_ptr->m_labelFont;
}

/*!
    Returns the fill color for the bar set.
*/
QColor QBarSet::color()
{
    return brush().color();
}

/*!
    Sets the fill color for the bar set to \a color.
*/
void QBarSet::setColor(QColor color)
{
    QBrush b = brush();
    if ((b.color() != color) || (b.style() == Qt::NoBrush)) {
        b.setColor(color);
        if (b.style() == Qt::NoBrush) {
            // Set tyle to Qt::SolidPattern. (Default is Qt::NoBrush)
            // This prevents theme to override color defined in QML side:
            // BarSet { label: "Bob"; color:"red"; values: [1,2,3] }
            // The color must be obeyed, since user wanted it.
            b.setStyle(Qt::SolidPattern);
        }
        setBrush(b);
        emit colorChanged(color);
    }
}

/*!
    Returns the line color for the bar set.
*/
QColor QBarSet::borderColor()
{
    return pen().color();
}

/*!
    Sets the line color for the bar set to \a color.
*/
void QBarSet::setBorderColor(QColor color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
        emit borderColorChanged(color);
    }
}

/*!
    Returns the text color for the bar set.
*/
QColor QBarSet::labelColor()
{
    return labelBrush().color();
}

/*!
    Sets the text color for the bar set to \a color.
*/
void QBarSet::setLabelColor(QColor color)
{
    QBrush b = labelBrush();
    if (b == QBrush())
        b.setStyle(Qt::SolidPattern);

    if (d_ptr->m_labelBrush.color() != color) {
        b.setColor(color);
        setLabelBrush(b);
        emit labelColorChanged(color);
    }
}

/*!
    Returns the color of the selected bars.

    This is the fill (brush) color of bars marked as selected. If not specified,
    value of QBarSet::color is used as default.
    \sa color
    \since 6.2
*/
QColor QBarSet::selectedColor() const
{
    return d_ptr->m_selectedColor;
}

/*!
    Sets the \a color of the selected bars.
    \sa selectedColor
    \since 6.2
*/
void QBarSet::setSelectedColor(const QColor &color)
{
    if (d_ptr->m_selectedColor != color) {
        d_ptr->m_selectedColor = color;
        d_ptr->setLabelsDirty(true);
        emit d_ptr->updatedBars();
        emit selectedColorChanged(color);
    }
}

/*!
   Returns \c true if the bar at the given \a index is among selected bars and \c false otherwise.
   \note Selected bars are drawn using the selected color if it was specified using QBarSet::setSelectedColor.
   \sa selectedBars(), setBarSelected(), setSelectedColor()
   \since 6.2
 */
bool QBarSet::isBarSelected(int index) const
{
    return d_ptr->isBarSelected(index);
}

/*!
  Marks the bar at \a index as selected.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::selectBar(int index)
{
    setBarSelected(index, true);
}

/*!
  Deselects the bar at \a index.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::deselectBar(int index)
{
    setBarSelected(index, false);
}

/*!
  Marks the bar at \a index as either selected or deselected as specified by \a selected.
  \note Selected bars are drawn using the selected color if it was specified. Emits QBarSet::selectedBarsChanged.
  \sa setSelectedColor()
  \since 6.2
 */
void QBarSet::setBarSelected(int index, bool selected)
{
    bool callSignal = false;
    d_ptr->setBarSelected(index, selected, callSignal);

    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
  Marks all bars in the series as selected.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::selectAllBars()
{
    bool callSignal = false;
    for (int i = 0; i < d_ptr->m_values.size(); ++i)
        d_ptr->setBarSelected(i, true, callSignal);

    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
  Deselects all bars in the series.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::deselectAllBars()
{
    bool callSignal = false;
    for (int i = 0; i < d_ptr->m_values.size(); ++i)
        d_ptr->setBarSelected(i, false, callSignal);

    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
  Marks multiple bars passed in an \a indexes list as selected.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::selectBars(const QList<int> &indexes)
{
    bool callSignal = false;
    for (const int &index : indexes)
        d_ptr->setBarSelected(index, true, callSignal);

    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
  Marks multiple bars passed in an \a indexes list as deselected.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::deselectBars(const QList<int> &indexes)
{
    bool callSignal = false;
    for (const int &index : indexes)
        d_ptr->setBarSelected(index, false, callSignal);

    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
  Changes the selection state of bars at the given \a indexes to the opposite one.
  \note Emits QBarSet::selectedBarsChanged.
  \sa setBarSelected()
  \since 6.2
 */
void QBarSet::toggleSelection(const QList<int> &indexes)
{
    bool callSignal = false;
    for (const int &index : indexes)
        d_ptr->setBarSelected(index, !isBarSelected(index), callSignal);

    if (callSignal)
        emit selectedBarsChanged(selectedBars());
}

/*!
  Returns a list of bars marked as selected.
  \sa setBarSelected()
  \since 6.2
 */
QList<int> QBarSet::selectedBars() const
{
    return QList<int>(d_ptr->m_selectedBars.begin(), d_ptr->m_selectedBars.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSetPrivate::QBarSetPrivate(const QString label, QBarSet *parent) : QObject(parent),
    q_ptr(parent),
    m_label(label),
    m_pen(QChartPrivate::defaultPen()),
    m_brush(QChartPrivate::defaultBrush()),
    m_labelBrush(QChartPrivate::defaultBrush()),
    m_visualsDirty(true)
{
}

QBarSetPrivate::~QBarSetPrivate()
{
}

void QBarSetPrivate::append(QPointF value)
{
    if (isValidValue(value)) {
        m_values.append(value);
        emit valueAdded(m_values.size() - 1, 1);
    }
}

void QBarSetPrivate::append(const QList<QPointF> &values)
{
    int originalIndex = m_values.size();
    for (const auto &value : values) {
        if (isValidValue(value))
            m_values.append(value);
    }
    emit valueAdded(originalIndex, values.size());
}

void QBarSetPrivate::append(const QList<qreal> &values)
{
    int originalIndex = m_values.size();
    int index = originalIndex;
    for (const auto value : values) {
        if (isValidValue(value)) {
            m_values.append(QPointF(index, value));
            index++;
        }
    }
    emit valueAdded(originalIndex, values.size());
}

void QBarSetPrivate::insert(const int index, const qreal value)
{
    m_values.insert(index, QPointF(index, value));
    emit valueAdded(index, 1);
}

void QBarSetPrivate::insert(const int index, const QPointF value)
{
    m_values.insert(index, value);
    emit valueAdded(index, 1);
}

int QBarSetPrivate::remove(const int index, const int count)
{
    int removeCount = count;

    if ((index < 0) || (m_values.size() == 0))
        return 0; // Invalid index or not values in list, remove nothing.
    else if ((index + count) > m_values.size())
        removeCount = m_values.size() - index; // Trying to remove more items than list has. Limit amount to be removed.

    int c = 0;
    while (c < removeCount) {
        m_values.removeAt(index);
        c++;
    }

    bool callSignal = false;
    if (!m_selectedBars.empty()) {
        QSet<int> selectedAfterRemoving;

        for (const int &selectedBarIndex : std::as_const(m_selectedBars)) {
            if (selectedBarIndex < index) {
                selectedAfterRemoving << selectedBarIndex;
            } else if (selectedBarIndex >= index + removeCount) {
                selectedAfterRemoving << selectedBarIndex - removeCount;
                callSignal = true;
            } else {
                callSignal = true;
            }
        }

        m_selectedBars = selectedAfterRemoving;
    }

    emit valueRemoved(index, removeCount);
    if (callSignal)
        emit q_ptr->selectedBarsChanged(q_ptr->selectedBars());

    return removeCount;
}

void QBarSetPrivate::replace(const int index, const qreal value)
{
    m_values.replace(index, QPointF(index, value));
    emit valueChanged(index);
}

qreal QBarSetPrivate::pos(const int index)
{
    if (index < 0 || index >= m_values.size())
        return 0;
    return m_values.at(index).x();
}

qreal QBarSetPrivate::value(const int index)
{
    if (index < 0 || index >= m_values.size())
        return 0;
    return m_values.at(index).y();
}

void QBarSetPrivate::setBarSelected(int index, bool selected, bool &callSignal)
{
    if (index < 0 || index > m_values.size() - 1)
        return;

    if (selected) {
        if (!isBarSelected(index)) {
            m_selectedBars << index;
            callSignal = true;
        }
    } else {
        if (isBarSelected(index)) {
            m_selectedBars.remove(index);
            callSignal = true;
        }
    }

    if (callSignal)
        setVisualsDirty(true);
}

bool QBarSetPrivate::isBarSelected(int index) const
{
    return m_selectedBars.contains(index);
}

QT_END_NAMESPACE

#include "moc_qbarset.cpp"
#include "moc_qbarset_p.cpp"
