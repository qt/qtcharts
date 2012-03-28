#include "qpieslice.h"
#include "qpiesliceprivate_p.h"
#include "qpieseries.h"
#include "qpieseriesprivate_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

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
    d_ptr(new QPieSlicePrivate(this))
{

}

/*!
    Constructs an empty slice with given \a value, \a label and a \a parent.
    Note that QPieSeries takes ownership of the slice when it is set/added.
    \sa QPieSeries::replace(), QPieSeries::add()
*/
QPieSlice::QPieSlice(qreal value, QString label, QObject *parent)
    :QObject(parent),
    d_ptr(new QPieSlicePrivate(this))
{
    Q_D(QPieSlice);
    d->m_data.m_value = value;
    d->m_data.m_labelText = label;
}

/*!
    Destroys the slice.
    User should not delete the slice if it has been added to the series.
*/
QPieSlice::~QPieSlice()
{
    delete d_ptr;
}

/*!
    Gets the value of the slice.
    Note that all values in the series
    \sa setValue()
*/
qreal QPieSlice::value() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_value;
}

/*!
    Gets the label of the slice.
    \sa setLabel()
*/
QString QPieSlice::label() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_labelText;
}

/*!
    Returns true if label is set as visible.
    \sa setLabelVisible()
*/
bool QPieSlice::isLabelVisible() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_isLabelVisible;
}

/*!
    Returns true if slice is exloded from the pie.
    \sa setExploded(), setExplodeDistanceFactor()
*/
bool QPieSlice::isExploded() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_isExploded;
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
    Q_D(const QPieSlice);
    return d->m_data.m_explodeDistanceFactor;
}

/*!
    Returns the percentage of this slice compared to all slices in the same series.
    The returned value ranges from 0 to 1.0.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::percentage() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_percentage;
}

/*!
    Returns the starting angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::startAngle() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_startAngle;
}

/*!
    Returns the end angle of this slice in the series it belongs to.

    Full pie is 360 degrees where 0 degrees is at 12 a'clock.

    Updated internally after the slice is added to the series.
*/
qreal QPieSlice::endAngle() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_startAngle + d->m_data.m_angleSpan;
}

/*!
    Returns the pen used to draw this slice.
    \sa setSlicePen()
*/
QPen QPieSlice::pen() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_slicePen;
}

/*!
    Returns the brush used to draw this slice.
    \sa setSliceBrush()
*/
QBrush QPieSlice::brush() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_sliceBrush;
}

/*!
    Returns the pen used to draw the label in this slice.
    \sa setLabelArmPen()
*/
QPen QPieSlice::labelPen() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_labelPen;
}

/*!
    Returns the font used to draw label in this slice.
    \sa setLabelFont()
*/
QFont QPieSlice::labelFont() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_labelFont;
}

/*!
    Gets the label arm length factor.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa setLabelArmLengthFactor()
*/
qreal QPieSlice::labelArmLengthFactor() const
{
    Q_D(const QPieSlice);
    return d->m_data.m_labelArmLengthFactor;
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
    Q_D(QPieSlice);
    if (!qFuzzyIsNull(d->m_data.m_value - value)) {
        d->m_data.m_value = value;

        QPieSeries *series = qobject_cast<QPieSeries*>(parent());
        if (series)
            series->data_ptr()->updateDerivativeData(); // will emit changed()
        else
            emit changed();
    }
}

/*!
    Sets the \a label of the slice.
    \sa label()
*/
void QPieSlice::setLabel(QString label)
{
    Q_D(QPieSlice);
    if (d->m_data.m_labelText != label) {
        d->m_data.m_labelText = label;
        emit changed();
    }
}

/*!
    Sets the label \a visible in this slice.
    \sa isLabelVisible(), QPieSeries::setLabelsVisible()
*/
void QPieSlice::setLabelVisible(bool visible)
{
    Q_D(QPieSlice);
    if (d->m_data.m_isLabelVisible != visible) {
        d->m_data.m_isLabelVisible = visible;
        emit changed();
    }
}

/*!
    Sets this slice \a exploded.
    \sa isExploded(), explodeDistanceFactor()
*/
void QPieSlice::setExploded(bool exploded)
{
    Q_D(QPieSlice);
    if (d->m_data.m_isExploded != exploded) {
        d->m_data.m_isExploded = exploded;
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
    Q_D(QPieSlice);
    if (!qFuzzyIsNull(d->m_data.m_explodeDistanceFactor - factor)) {
        d->m_data.m_explodeDistanceFactor = factor;
        emit changed();
    }
}

/*!
    Sets the \a pen used to draw this slice.
    Note that applying a theme will override this.
    \sa slicePen()
*/
void QPieSlice::setPen(const QPen &pen)
{
    Q_D(QPieSlice);
    if (d->m_data.m_slicePen != pen) {
        d->m_data.m_slicePen = pen;
        d->m_data.m_slicePen.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the \a brush used to draw this slice.
    Note that applying a theme will override this.
    \sa sliceBrush()
*/
void QPieSlice::setBrush(const QBrush &brush)
{
    Q_D(QPieSlice);
    if (d->m_data.m_sliceBrush != brush) {
        d->m_data.m_sliceBrush = brush;
        d->m_data.m_sliceBrush.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the \a pen used to draw the label in this slice.
    Note that applying a theme will override this.
    \sa labelArmPen()
*/
void QPieSlice::setLabelPen(const QPen &pen)
{
    Q_D(QPieSlice);
    if (d->m_data.m_labelPen != pen) {
        d->m_data.m_labelPen = pen;
        d->m_data.m_labelPen.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the \a font used to draw the label in this slice.
    Note that applying a theme will override this.
    \sa labelFont()
*/
void QPieSlice::setLabelFont(const QFont &font)
{
    Q_D(QPieSlice);
    if (d->m_data.m_labelFont != font) {
        d->m_data.m_labelFont = font;
        d->m_data.m_labelFont.setThemed(false);
        emit changed();
    }
}

/*!
    Sets the label arm length \a factor.

    The factor is relative to pie radius. For example:
    1.0 means the length is the same as the radius.
    0.5 means the length is half of the radius.

    Default value is 0.15

    \sa labelArmLengthFactor()
*/
void QPieSlice::setLabelArmLengthFactor(qreal factor)
{
    Q_D(QPieSlice);
    if (!qFuzzyIsNull(d->m_data.m_labelArmLengthFactor - factor)) {
        d->m_data.m_labelArmLengthFactor = factor;
        emit changed();
    }
}

#include "moc_qpieslice.cpp"
#include "moc_qpiesliceprivate_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
