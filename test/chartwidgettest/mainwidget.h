#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

class ChartWidget;

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
    void xMinChanged(int value);
    void xMaxChanged(int value);
    void yMinChanged(int value);
    void yMaxChanged(int value);

private:
    ChartWidget *m_chartWidget;
};

#endif // MAINWIDGET_H
