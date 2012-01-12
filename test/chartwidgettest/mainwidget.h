#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class QChartWidget;
class QSpinBox;
class QCheckBox;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

private slots:
    void chartTypeChanged(int itemIndex);
    void dataChanged(QString itemText);
    void backgroundChanged(int itemIndex);
    void autoScaleChanged(int value);
    void xMinChanged(int value);
    void xMaxChanged(int value);
    void yMinChanged(int value);
    void yMaxChanged(int value);

private:
    QChartWidget *m_chartWidget;
    QCheckBox *m_autoScaleCheck;
    QSpinBox *m_xMinSpin;
    QSpinBox *m_xMaxSpin;
    QSpinBox *m_yMinSpin;
    QSpinBox *m_yMaxSpin;
};

#endif // MAINWIDGET_H
