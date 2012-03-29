#ifndef QBARSET_H
#define QBARSET_H

#include <qchartglobal.h>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarSet : public QObject
{
    Q_OBJECT
public:
    QBarSet(QString name, QObject *parent = 0);

    void setName(QString name);
    QString name() const;
    QBarSet& operator << (const qreal &value);  // appends new value to set
    void insertValue(int i, qreal value);
    void removeValue(int i);

    // TODO: remove indices eventually. Use as internal?
    int count() const;                          // count of values in set
    qreal valueAt(int index) const;                   // for modifying individual values
    void setValue(int index, qreal value);      // setter for individual value
    qreal total() const;                              // total values in the set

    // TODO:
    //qreal value(QString category);
    //void setValue(QString category, qreal value);

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setFloatingValuePen(const QPen &pen);
    QPen floatingValuePen() const;

Q_SIGNALS:
    void clicked(QString category);                         // Clicked and hover signals exposed to user
    void rightClicked(QString category);
    void toggleFloatingValues();

    // TODO: Expose this to user or not?
    // TODO: TO PIMPL --->
    void structureChanged();
    void valueChanged();
    void hoverEnter(QPoint pos);
    void hoverLeave();
    void showToolTip(QPoint pos, QString tip);  // Private signal
    // <--- TO PIMPL

public Q_SLOTS:
    // These are for internal communication
    // TODO: TO PIMPL --->
    void barHoverEnterEvent(QPoint pos);
    void barHoverLeaveEvent();
    // <--- TO PIMPL

private:

    QString m_name;
    QList<qreal> m_values;   // TODO: replace with map (category, value)
    QMap<QString, qreal> m_mappedValues;
    QPen m_pen;
    QBrush m_brush;
    QPen m_floatingValuePen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
