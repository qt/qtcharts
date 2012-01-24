#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <qchartglobal.h>
#include <qchartwidget.h>
#include <QWidget>

class QSpinBox;
class QCheckBox;
class QGridLayout;

QTCOMMERCIALCHART_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

private slots:
    void addSeries();
    void addSeries(QString series, QString data);
    void testDataChanged(int itemIndex);
    void backgroundChanged(int itemIndex);
    void autoScaleChanged(int value);
    void xMinChanged(int value);
    void xMaxChanged(int value);
    void yMinChanged(int value);
    void yMaxChanged(int value);
    void setCurrentSeries(QChartSeries *series);
    void setPieSizeFactor(double margin);

private:
    QChartWidget *m_chartWidget;
    QCheckBox *m_autoScaleCheck;
    QSpinBox *m_xMinSpin;
    QSpinBox *m_xMaxSpin;
    QSpinBox *m_yMinSpin;
    QSpinBox *m_yMaxSpin;
    QString m_defaultSeriesName;
    QChartSeries *m_currentSeries;
    QGridLayout *m_scatterLayout;
    QGridLayout *m_pieLayout;
};

#endif // MAINWIDGET_H
