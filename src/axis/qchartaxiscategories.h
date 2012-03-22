#ifndef QCHARTAXISCATEGORIES_H_
#define QCHARTAXISCATEGORIES_H_

#include <qchartglobal.h>
#include <qbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QChartAxisCategories : public QObject
{
    Q_OBJECT
private:
    QChartAxisCategories();
public:
    ~QChartAxisCategories();

    void insert(const QBarCategories& category);
    void insert(qreal value,QString label);
    void remove(qreal value);
    QString label(qreal value) const;
    void clear();
    int count();

//internal signal
signals:
    void updated();

private:
    QMap<qreal,QString> m_map;

friend class QChartAxis;
};


QTCOMMERCIALCHART_END_NAMESPACE

#endif /* QCHARTAXISCATEGORIES_H_ */
