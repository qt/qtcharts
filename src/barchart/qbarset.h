#ifndef QBARSET_H
#define QBARSET_H

#include "qchartglobal.h"
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarSet // TODO? : public QObject
{
    //Q_OBJECT;
public:
    QBarSet();

    void setName(QString name);
    QString name();
    QBarSet& operator << (const qreal &value);  // appends new value to set

    int count();                                // count of values in set
    qreal valueAt(int index);                   // for modifying individual values
    void setValue(int index, qreal value);      //

    void setPen(const QPen& pen);
    const QPen& pen() const;

    void setBrush(const QBrush& brush);
    const QBrush& brush() const;

private:

    QString mName;
    QList<qreal> mValues;
    QPen mPen;
    QBrush mBrush;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
