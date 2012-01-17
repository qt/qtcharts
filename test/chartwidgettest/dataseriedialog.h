#ifndef DATASERIEDIALOG_H
#define DATASERIEDIALOG_H

#include <QDialog>

class QComboBox;

class DataSerieDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataSerieDialog(QWidget *parent = 0);

signals:
    void accepted(QString series, QString data);

public slots:
    void accept();

private:
    QComboBox *m_seriesTypeCombo;
    QComboBox *m_testDataCombo;
};

#endif // DATASERIEDIALOG_H
