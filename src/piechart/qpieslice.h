#ifndef QPIESLICE_H
#define QPIESLICE_H

#include <qchartglobal.h>
#include <QObject>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QPieSlice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY changed)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY changed)

public:
    QPieSlice(QObject *parent = 0);
    QPieSlice(qreal value, QString label, QObject *parent = 0);
    virtual ~QPieSlice();

    // data
    void setValue(qreal value);
    qreal value() const;
    void setLabel(QString label);
    QString label() const;
    void setLabelVisible(bool visible);
    bool isLabelVisible() const;
    void setExploded(bool exploded);
    bool isExploded() const;
    void setExplodeDistanceFactor(qreal factor);
    qreal explodeDistanceFactor() const;

    // generated data
    qreal percentage() const;
    qreal startAngle() const;
    qreal endAngle() const;

    // customization
    void setSlicePen(const QPen &pen);
    QPen slicePen() const;
    void setSliceBrush(const QBrush &brush);
    QBrush sliceBrush() const;
    void setLabelArmPen(const QPen &pen);
    QPen labelArmPen() const;
    void setLabelFont(const QFont &font);
    QFont labelFont() const;
    void setLabelArmLengthFactor(qreal factor);
    qreal labelArmLengthFactor() const;

    // TODO: label position in general
    // setLabelFlags(inside|outside|labelArmOn|labelArmOff|???)
    // setLabelOrientation(horizontal|vertical|same as slice center angle|???)

Q_SIGNALS:
    void clicked();
    void hoverEnter();
    void hoverLeave();
    void changed();

private:

    // TODO: use private class
    friend class QPieSeries;
    friend class PiePresenter;
    friend class PieSlice;

    // data
    qreal m_value;
    QString m_label;
    bool m_isLabelVisible;
    bool m_isExploded;
    qreal m_explodeDistanceFactor;

    // generated data
    qreal m_percentage;
    qreal m_startAngle;
    qreal m_angleSpan;

    // customization
    QPen m_slicePen;
    QBrush m_sliceBrush;
    QFont m_labelFont;
    QPen m_labelArmPen;
    qreal m_labelArmLengthFactor;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICE_H
