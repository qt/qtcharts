#ifndef DATASERIEDIALOG_H
#define DATASERIEDIALOG_H

#include <QDialog>

class QGroupBox;
class QCheckBox;

class DataSerieDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataSerieDialog(QWidget *parent = 0);

signals:
    void accepted(QString series, int columnCount, int rowCount, QString dataCharacteristics, bool labelsDefined);

public slots:
    void accept();

private:
    QGroupBox *seriesTypeSelector();
    QGroupBox *columnCountSelector();
    QGroupBox *rowCountSelector();
    QGroupBox *dataCharacteristicsSelector();
    void selectRadio(QGroupBox *groupBox, int defaultSelection);
    QString radioSelection(QGroupBox *groupBox);
    QGroupBox *m_seriesTypeSelector;
    QGroupBox *m_columnCountSelector;
    QGroupBox *m_rowCountSelector;
    QCheckBox *m_labelsSelector;
    QGroupBox *m_dataCharacteristicsSelector;
};

#endif // DATASERIEDIALOG_H
