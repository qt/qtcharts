#ifndef QBARSET_P_H
#define QBARSET_P_H

#include "qbarset.h"
#include <QMap>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSetPrivate : public QObject
{
    Q_OBJECT

public:
    QBarSetPrivate(const QString name, QBarSet *parent);
    ~QBarSetPrivate();

Q_SIGNALS:
    void clicked(QString category);
    void selected();
    void restructuredBars();
    void updatedBars();
    void labelsVisibleChanged(bool visible);

public:
    QBarSet * const q_ptr;
    QString m_name;
    QList<qreal> m_values;   // TODO: replace with map (category, value)
    QMap<QString, qreal> m_mappedValues;
    QPen m_pen;
    QBrush m_brush;
    QPen m_labelPen;
    QBrush m_labelBrush;
    QFont m_labelFont;
    bool m_labelsVisible;

    friend class QBarSet;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSETPRIVATE_P_H
