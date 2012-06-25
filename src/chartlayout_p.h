#ifndef CHARTLAYOUT_H_
#define CHARTLAYOUT_H_
#include <QGraphicsLayout>
#include "qchartglobal.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;

class ChartLayout : public QGraphicsLayout
{
public:

    ChartLayout(ChartPresenter* presenter);
    virtual ~ChartLayout();

    void setMarginsMinimum(const QRectF& margins);
    QRectF margins() const;

    void setGeometry(const QRectF& rect);

protected:
    QSizeF sizeHint ( Qt::SizeHint which, const QSizeF & constraint = QSizeF() ) const;
    int count() const { return 0; }
    QGraphicsLayoutItem* itemAt(int) const { return 0; };
    void removeAt(int){};

private:
    ChartPresenter* m_presenter;
    int m_marginBig;
    int m_marginSmall;
    int m_marginTiny;

    QRectF m_chartMargins;
    QRectF m_legendMargins;



};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
