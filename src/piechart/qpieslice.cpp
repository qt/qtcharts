#include "qpieslice.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define DEFAULT_PEN_COLOR         Qt::black
#define DEFAULT_BRUSH_COLOR       Qt::white
#define DEFAULT_LABEL_ARM_LENGTH_FACTOR  0.15
#define DEFAULT_EXPOLODE_DISTANCE_FACTOR 0.15

/*!
    \class QPieSlice
    \brief Defines a slice in pie series.

    Holds all the data of a single slice in a QPieSeries and provides the means
    to modify slice data and customize the visual appearance of the slice.

    It also provides the means to customize user interaction with the slice by
    providing signals for clicking and hover events.
*/

/*!
    \property QPieSlice::label

    Label of the slice.
*/

/*!
    \property QPieSlice::value

    Value of the slice.
*/

/*!
    Constructs an empty slice with a \a parent.

    Note that QPieSeries takes ownership of the slice when it is set/added.

    \sa QPieSeries::replace(), QPieSeries::add()
*/
QPieSlice::QPieSlice(QObject *parent)
    :QObject(parent),
    m_value(0),
    m_isLabelVisible(false),
    m_isExploded(false),
    m_explodeDistanceFactor(DEFAULT_EXPOLODE_DISTANCE_FACTOR),
    m_percentage(0),
    m_startAngle(0),
    m_angleSpan(0),
    m_pen(DEFAULT_PEN_COLOR),
    m_brush(DEFAULT_BRUSH_COLOR),
    m_labelPen(DEFAULT_PEN_COLOR),
    m_labelArmLengthFactor(DEFAULT_LABEL_ARM_LENGTH_FACTOR)
{

}

/*!
    Constructs an empty slice with given \a value, \a label and a \a parent.
    Note that QPieSeries takes ownership of the slice when it is set/added.
    \sa QPieSeries::replace(), QPieSeries::add()
*/
QPieSlice::QPieSlice(qreal value, QString label, QObject *parent)
    :QObject(parent),
    m_value(value),
    m_label(label),
    m_isLabelVisible(false),
    m_isExploded(false),
    m_explodeDistanceFactor(DEFAULT_EXPOLODE_DISTANCE_FACTOR),
    m_percentage(0),
    m_startAngle(0),
    m_angleSpan(0),
    m_pen(DEFAULT_PEN_COLOR),
    m_brush(DEFAULT_BRUSH_COLOR),
    m_labelPen(DEFAULT_PEN_COLOR),
    m_labelArmLengthFactor(DEFAULT_LABEL_ARM_LENGTH_FACTOR)
{

}

/*!
    Destroys the slice.
    User should not delete the slice if it has been added to the series.
*/
QPieSlice::~QPieSlice()
{

}

/*!
    Gets the value of the slice.
    Note that all values in the series
    \sa setValue()
*/
qreal QPieSlice::value() const
{
    return m_value;
}

/*!
    Gets the label of the slice.
    \sa setLabel()
*/
QString QPieSlice::label() const
{
    return m_label;
}

/*!
    Returns true if label is set as visible.
    \sa setLabelVisible()
*/
bool QPieSlice::isLabelVisible() const
{
    return m_isLabelVisible;
}

/*!
    Returns true if slice is exloded from the pie.
    \sa setExploded(), setExplodeDistanceFactor()
*/
bool QPieSlice::isExploded() const
{
    return m_isExploded;
}

/*!
    Returns the explode distance factor.

    The factor is relative to pie radius. For example:
    1.0 means the distance is the same as the radius.
    0.5 means the distance is half of the radius.

    Default value is 0.15.

    \sa setExplodeDistanceFactor()
*/
qreal QPieSlice::explodeDistanceFactor() const
{
    return m_explodeDistanceFactor;
}

/*!
    Returns the percentage of this slice compared to all slices in the same series.
    The returned value ranges from 0 to 1.0.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::percentage() const
{
    return m_percentage;
}

/*!
    Returns the starting angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::startAngle() const
{
    return m_startAngle;
}

/*!
    Returns the end angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::endAngle() const
{
    return m_startAngle + m_angleSpan;
}

/*!
    Returns the pen used to draw this slice.
    \sa setPen()
*/
QPen QPieSlice::pen() const
{
    return m_pen;
}

/*!
    Returns the brush used to draw this slice.
    \sa setBrush()
*/
QBrush QPieSlice::brush() const
{
    return m_brush;
}

/*!
    Returns the pen used to draw label in this slice.
    \sa setLabelPen()
*/
QPen QPieSlice::labelPen() const
{
    return m_labelPen;
}

/*!
    Returns the font used to draw label in this slice.
    \sa setLabelFont()
*/
QFont QPieSlice::labelFont() const
{
    return m_labelFont;
}

/*!
    Gets the label arm lenght factor.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa setLabelArmLengthFactor()
*/
qreal QPieSlice::labelArmLengthFactor() const
{
    return m_labelArmLengthFactor;
}

/*!
    \fn void QPieSlice::clicked()

    This signal is emitted when user has clicked the slice.

    \sa QPieSeries::clicked()
*/

/*!
    \fn void QPieSlice::hoverEnter()

    This signal is emitted when user has hovered over the slice.

    \sa QPieSeries::hoverEnter()
*/

/*!
    \fn void QPieSlice::hoverLeave()

    This signal is emitted when user has hovered away from the slice.

    \sa QPieSeries::hoverLeave()
*/

/*!
    \fn void QPieSlice::changed()

    This signal emitted when something has changed in the slice.

    \sa QPieSeries::changed()
*/

/*!
    Sets the \a value of this slice.
    \sa value()
*/
void QPieSlice::setValue(qreal value)
{
    if (m_value != value) {
        m_value = value;
        emit changed();
    }
}

/*!
    Sets the \a label of the slice.
    \sa label()
*/
void QPieSlice::setLabel(QString label)
{
    if (m_label != label) {
        m_label = label;
        emit changed();
    }
}

/*!
    Sets the label \a visible in this slice.
    \sa isLabelVisible(), QPieSeries::setLabelsVisible()
*/
void QPieSlice::setLabelVisible(bool visible)
{
    if (m_isLabelVisible != visible) {
        m_isLabelVisible = visible;
        emit changed();
    }
}

/*!
    Sets this slice \a exploded.
    \sa isExploded(), explodeDistanceFactor()
*/
void QPieSlice::setExploded(bool exploded)
{
    if (m_isExploded != exploded) {
        m_isExploded = exploded;
        emit changed();
    }
}

/*!
    Sets the explode distance \a factor.

    The factor is relative to pie radius. For example:
    1.0 means the distance is the same as the radius.
    0.5 means the distance is half of the radius.

    Default value is 0.15

    \sa explodeDistanceFactor()
*/
void QPieSlice::setExplodeDistanceFactor(qreal factor)
{
    if (m_explodeDistanceFactor != factor) {
        m_explodeDistanceFactor = factor;
        emit changed();
    }
}

/*!
    Sets the \a pen used to draw this slice.
    Note that applying a theme will override this.
    \sa pen()
*/
void QPieSlice::setPen(QPen pen)
{
    if (m_pen != pen) {
        m_pen = pen;
        emit changed();
    }
}

/*!
    Sets the \a brush used to draw this slice.
    Note that applying a theme will override this.
    \sa brush()
*/
void QPieSlice::setBrush(QBrush brush)
{
    if (m_brush != brush) {
        m_brush = brush;
        emit changed();
    }
}

/*!
    Sets the \a pen used to draw the label in this slice.
    Note that applying a theme will override this.
    \sa labelPen()
*/
void QPieSlice::setLabelPen(QPen pen)
{
    if (m_labelPen != pen) {
        m_labelPen = pen;
        emit changed();
    }
}

/*!
    Sets the \a font used to draw the label in this slice.
    Note that applying a theme will override this.
    \sa labelFont()
*/
void QPieSlice::setLabelFont(QFont font)
{
    if (m_labelFont != font) {
        m_labelFont = font;
        emit changed();
    }
}

/*!
    Sets the label arm lenght \a factor.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa labelArmLengthFactor()
*/
void QPieSlice::setLabelArmLengthFactor(qreal factor)
{
    if (m_labelArmLengthFactor != factor) {
        m_labelArmLengthFactor = factor;
        emit changed();
    }
}

#include "moc_qpieslice.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
