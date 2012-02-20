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
    Q_PROPERTY(QString label READ label WRITE setLabel /*NOTIFY dataYChanged*/)
    Q_PROPERTY(qreal value READ value WRITE setValue /*NOTIFY dataXChanged*/)

public:
    QPieSlice(QObject *parent = 0);
    QPieSlice(qreal value, QString label, bool labelVisible = true, QObject *parent = 0);
    virtual ~QPieSlice();

    // data
    qreal value() const;
    QString label() const;
    bool isLabelVisible() const;
    bool isExploded() const;

    // generated data
    qreal percentage() const;
    qreal angle() const;
    qreal span() const;

    // customization
    QPen pen() const;
    QBrush brush() const;
    QPen labelPen() const;
    QFont labelFont() const;
    qreal labelArmLenght() const;

Q_SIGNALS:
    void clicked();
    void hoverEnter();
    void hoverLeave();
    void changed();

public Q_SLOTS:

    // data
    void setLabel(QString label);
    void setLabelVisible(bool visible);
    void setValue(qreal value);
    void setExploded(bool exploded);

    // customization
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void setLabelFont(QFont font);
    void setLabelPen(QPen pen);
    void setLabelArmLength(qreal len);

private:

    // TODO: use private class
    friend class QPieSeries;

    // data
    qreal m_value;
    QString m_label;
    bool m_isLabelVisible;
    bool m_isExploded;

    // generated data
    qreal m_percentage;
    qreal m_angle;
    qreal m_span;

    // customization
    QPen m_pen;
    QBrush m_brush;
    QPen m_labelPen;
    QFont m_labelFont;
    qreal m_labelArmLength;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIESLICE_H
