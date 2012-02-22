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
    QString name();
    QBarSet& operator << (const qreal &value);  // appends new value to set

    int count();                                // count of values in set
    qreal valueAt(int index);                   // for modifying individual values
    void setValue(int index, qreal value);      // setter for individual value

    void setPen(const QPen& pen);
    const QPen& pen() const;

    void setBrush(const QBrush& brush);
    const QBrush& brush() const;

Q_SIGNALS:
    void clicked();                 // Clicked and hover signals exposed to user
    void hoverEnter();
    void hoverLeave();
    void toggleFloatingValues();    // Private signal, TODO: move to private impl

public Q_SLOTS:
    void enableFloatingValues(bool enabled);    // enables floating values on top of bars
    void enableHoverNames(bool enabled);        // enableHoverEvents would be better name?

    // TODO: these slots belong to private implementation.
    // These are for single bars to notify set about internal events
    void barClicked();
    void barHoverEntered();
    void barHoverLeaved();

private:

    QString mName;
    QList<qreal> mValues;
    QPen mPen;
    QBrush mBrush;

    // TODO: to pimpl
    bool mFloatingValuesEnabled;
    bool mHoverNamesEnabled;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
