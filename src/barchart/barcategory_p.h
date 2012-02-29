#ifndef BARCATEGORY_P_H
#define BARCATEGORY_P_H

#include <QObject>
#include <qchartglobal.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
// Event handler for bar category
class BarCategory : public QObject
{
    Q_OBJECT
public:
    explicit BarCategory(QString name, QObject *parent = 0);
    
signals:
    void rightClicked(QString name); // "We want something to happen that involves this category"
    
public slots:
    void barRightClickEvent();

private:
    QString mName;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif // BARCATEGORY_P_H
