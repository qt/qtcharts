#ifndef QPIESLICE_H
#define QPIESLICE_H

#include <qchartglobal.h>
#include <QObject>
#include <QPen>
#include <QBrush>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSlicePrivate;

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
    void setLabelVisible(bool visible = true);
    bool isLabelVisible() const;
    void setExploded(bool exploded = true);
    bool isExploded() const;

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
    void setExplodeDistanceFactor(qreal factor);
    qreal explodeDistanceFactor() const;

Q_SIGNALS:
    void clicked();
    void hoverEnter();
    void hoverLeave();
    void changed();

private:
    QPieSlicePrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QPieSlice)
    Q_DISABLE_COPY(QPieSlice)

public:
    typedef QPieSlicePrivate * const DataPtr;
    inline DataPtr &data_ptr() { return d_ptr; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICE_H
