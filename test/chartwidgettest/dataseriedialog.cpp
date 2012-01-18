#include "dataseriedialog.h"
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

DataSerieDialog::DataSerieDialog(QString defaultType, QWidget *parent) :
    QDialog(parent)
{
    // Combo box for selecting the series type
    m_seriesTypeCombo = new QComboBox(this);
    m_seriesTypeCombo->addItem("Line");
    m_seriesTypeCombo->addItem("Area");
    m_seriesTypeCombo->addItem("Bar");
    m_seriesTypeCombo->addItem("Pie");
    m_seriesTypeCombo->addItem("Scatter");
    m_seriesTypeCombo->addItem("Spline");

    // Allow pre-selection of a series type
    if (defaultType != "") {
        int index = m_seriesTypeCombo->findText(defaultType);
        if (index > 0)
            m_seriesTypeCombo->setCurrentIndex(index);
    }

    // Combo box for selecting data for the new series
    m_testDataCombo = new QComboBox(this);
    m_testDataCombo->addItem("linear");
    m_testDataCombo->addItem("SIN");
    m_testDataCombo->addItem("SIN + random");
    m_testDataCombo->addItem("TODO From file...");
    m_testDataCombo->addItem("TODO From URL...");

    QDialogButtonBox *addSeriesBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *b = addSeriesBox->addButton(QDialogButtonBox::Ok);
    connect(b, SIGNAL(clicked()), this, SLOT(accept()));
    b = addSeriesBox->addButton(QDialogButtonBox::Cancel);
    connect(b, SIGNAL(clicked()), this, SLOT(reject()));

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(new QLabel("Series type:"), 0, 0);
    grid->addWidget(m_seriesTypeCombo, 0, 1);
    grid->addWidget(new QLabel("Data:"), 1, 0);
    grid->addWidget(m_testDataCombo, 1, 1);
    grid->addWidget(addSeriesBox, 2, 1);

    setLayout(grid);
}

void DataSerieDialog::accept()
{
    accepted(m_seriesTypeCombo->currentText(), m_testDataCombo->currentText());
    QDialog::accept();
}
//void DataSerieDialog::addSeries(QAbstractButton *button)
//{
//    addSeries(button->text().toAscii());
//    accept();
//}
