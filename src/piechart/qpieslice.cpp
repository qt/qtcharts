#include "qpieslice.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define DEFAULT_PEN_COLOR         Qt::black
#define DEFAULT_BRUSH_COLOR       Qt::white
#define DEFAULT_LABEL_ARM_LENGTH  50
#define DEFAULT_EXPOLODE_DISTANCE 20

QPieSlice::QPieSlice(QObject *parent)
    :QObject(parent),
    m_value(0),
    m_isLabelVisible(true),
    m_isExploded(false),
    m_explodeDistance(DEFAULT_EXPOLODE_DISTANCE),
    m_percentage(0),
    m_angle(0),
    m_angleSpan(0),
    m_pen(DEFAULT_PEN_COLOR),
    m_brush(DEFAULT_BRUSH_COLOR),
    m_labelPen(DEFAULT_PEN_COLOR),
    m_labelArmLength(DEFAULT_LABEL_ARM_LENGTH)
{

}

QPieSlice::QPieSlice(qreal value, QString label, bool labelVisible, QObject *parent)
    :QObject(parent),
    m_value(value),
    m_label(label),
    m_isLabelVisible(labelVisible),
    m_isExploded(false),
    m_explodeDistance(DEFAULT_EXPOLODE_DISTANCE),
    m_percentage(0),
    m_angle(0),
    m_angleSpan(0),
    m_pen(DEFAULT_PEN_COLOR),
    m_brush(DEFAULT_BRUSH_COLOR),
    m_labelPen(DEFAULT_PEN_COLOR),
    m_labelArmLength(DEFAULT_LABEL_ARM_LENGTH)
{

}

QPieSlice::~QPieSlice()
{

}

qreal QPieSlice::value() const
{
    return m_value;
}

QString QPieSlice::label() const
{
    return m_label;
}

bool QPieSlice::isLabelVisible() const
{
    return m_isLabelVisible;
}

bool QPieSlice::isExploded() const
{
    return m_isExploded;
}

qreal QPieSlice::explodeDistance() const
{
    return m_explodeDistance;
}

qreal QPieSlice::percentage() const
{
    return m_percentage;
}

qreal QPieSlice::angle() const
{
    return m_angle;
}

qreal QPieSlice::angleSpan() const
{
    return m_angleSpan;
}

QPen QPieSlice::pen() const
{
    return m_pen;
}

QBrush QPieSlice::brush() const
{
    return m_brush;
}

QPen QPieSlice::labelPen() const
{
    return m_labelPen;
}

QFont QPieSlice::labelFont() const
{
    return m_labelFont;
}

qreal QPieSlice::labelArmLength() const
{
    return m_labelArmLength;
}

void QPieSlice::setValue(qreal value)
{
    if (m_value != value) {
        m_value = value;
        emit changed();
    }
}

void QPieSlice::setLabel(QString label)
{
    if (m_label != label) {
        m_label = label;
        emit changed();
    }
}

void QPieSlice::setLabelVisible(bool visible)
{
    if (m_isLabelVisible != visible) {
        m_isLabelVisible = visible;
        emit changed();
    }
}

void QPieSlice::setExploded(bool exploded)
{
    if (m_isExploded != exploded) {
        m_isExploded = exploded;
        emit changed();
    }
}

void QPieSlice::setExplodeDistance(qreal distance)
{
    if (m_explodeDistance != distance) {
        m_explodeDistance = distance;
        emit changed();
    }
}

void QPieSlice::setPen(QPen pen)
{
    if (m_pen != pen) {
        m_pen = pen;
        emit changed();
    }
}

void QPieSlice::setBrush(QBrush brush)
{
    if (m_brush != brush) {
        m_brush = brush;
        emit changed();
    }
}

void QPieSlice::setLabelFont(QFont font)
{
    if (m_labelFont != font) {
        m_labelFont = font;
        emit changed();
    }
}

void QPieSlice::setLabelPen(QPen pen)
{
    if (m_labelPen != pen) {
        m_labelPen = pen;
        emit changed();
    }
}

void QPieSlice::setLabelArmLength(qreal len)
{
    if (m_labelArmLength != len) {
        m_labelArmLength = len;
        emit changed();
    }
}

#include "moc_qpieslice.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
