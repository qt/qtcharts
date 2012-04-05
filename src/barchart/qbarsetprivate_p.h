#ifndef QBARSETPRIVATE_P_H
#define QBARSETPRIVATE_P_H

#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSetPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(QBarSet)

public:
    QBarSetPrivate(QString name, QBarSet *parent);
    ~QBarSetPrivate();

    void setName(QString name);
    QString name() const;
    QBarSetPrivate& operator << (const qreal &value);  // appends new value to set
    void insertValue(int i, qreal value);
    void removeValue(int i);
    int count() const;
    qreal valueAt(int index) const;
    void setValue(int index, qreal value);
    qreal sum() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setLabelPen(const QPen &pen);
    QPen labelPen() const;

    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelFont(const QFont &font);
    QFont labelFont() const;

    void setLabelsVisible(bool visible = true);
    bool labelsVisible() const;

    static QBarSetPrivate &pimpl(QBarSet *barset)
    {
        Q_ASSERT(barset);
        return *barset->d_ptr;
    }

Q_SIGNALS:
    void clicked(QString category, Qt::MouseButtons button);
    void structureChanged();
    void valueChanged();
    void hoverEnter(QPoint pos);
    void hoverLeave();
    void showToolTip(QPoint pos, QString tip);
    void labelsVisibleChanged(bool visible);

public Q_SLOTS:
    void barHoverEnterEvent(QPoint pos);
    void barHoverLeaveEvent();

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
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSETPRIVATE_P_H
