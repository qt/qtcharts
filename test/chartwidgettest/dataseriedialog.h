#ifndef DATASERIEDIALOG_H
#define DATASERIEDIALOG_H

#include <QDialog>

class QAbstractButton;

class DataSerieDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataSerieDialog(QWidget *parent = 0);

signals:
    void addSeries(QString series);

public slots:
    void addSeries(QAbstractButton *button);
};

#endif // DATASERIEDIALOG_H
