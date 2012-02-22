#include "dataseriedialog.h"
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QCheckbox>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QDebug>

DataSerieDialog::DataSerieDialog(QString defaultType, QWidget *parent) :
    QDialog(parent)
{
    QDialogButtonBox *addSeriesBox = new QDialogButtonBox(Qt::Horizontal);
    QPushButton *b = addSeriesBox->addButton(QDialogButtonBox::Ok);
    connect(b, SIGNAL(clicked()), this, SLOT(accept()));
    b = addSeriesBox->addButton(QDialogButtonBox::Cancel);
    connect(b, SIGNAL(clicked()), this, SLOT(reject()));

    QGridLayout *grid = new QGridLayout();

    m_seriesTypeSelector = seriesTypeSelector();
    m_columnCountSelector = columnCountSelector();
    m_rowCountSelector = rowCountSelector();
    m_dataCharacteristicsSelector = dataCharacteristicsSelector();

    grid->addWidget(m_seriesTypeSelector, 0, 0);
    grid->addWidget(m_columnCountSelector, 0, 1);
    grid->addWidget(m_rowCountSelector, 1, 1);
    grid->addWidget(m_dataCharacteristicsSelector, 1, 0);
    m_labelsSelector = new QCheckBox("Labels defined");
    m_labelsSelector->setChecked(true);
    grid->addWidget(m_labelsSelector, 2, 0);
    grid->addWidget(addSeriesBox, 3, 1);

    setLayout(grid);
}

QGroupBox *DataSerieDialog::seriesTypeSelector()
{
    QVBoxLayout *layout = new QVBoxLayout();

    QRadioButton *line = new QRadioButton("&Line");
    QRadioButton *area = new QRadioButton("&Area");
    QRadioButton *pie = new QRadioButton("&Pie");
    QRadioButton *bar = new QRadioButton("&Bar");
    QRadioButton *scatter = new QRadioButton("&Scatter");
    QRadioButton *spline = new QRadioButton("Spl&ine");
    line->setChecked(true);

    layout->addWidget(line);
    layout->addWidget(area);
    layout->addWidget(pie);
    layout->addWidget(bar);
    layout->addWidget(scatter);
    layout->addWidget(spline);

    QGroupBox *groupBox = new QGroupBox("Series type");
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *DataSerieDialog::columnCountSelector()
{
    QVBoxLayout *layout = new QVBoxLayout();

    QRadioButton *radio = new QRadioButton("1");
    radio->setChecked(true);
    layout->addWidget(radio);
    layout->addWidget(new QRadioButton("2"));
    layout->addWidget(new QRadioButton("3"));
    layout->addWidget(new QRadioButton("5"));
    layout->addWidget(new QRadioButton("10"));
    layout->addWidget(new QRadioButton("100"));

    QGroupBox *groupBox = new QGroupBox("Column count");
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *DataSerieDialog::rowCountSelector()
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(new QRadioButton("1"));
    QRadioButton *radio = new QRadioButton("10");
    radio->setChecked(true);
    layout->addWidget(radio);
    layout->addWidget(new QRadioButton("50"));
    layout->addWidget(new QRadioButton("100"));
    layout->addWidget(new QRadioButton("10000"));
    layout->addWidget(new QRadioButton("1000000"));

    QGroupBox *groupBox = new QGroupBox("Row count");
    groupBox->setLayout(layout);

    return groupBox;
}

QGroupBox *DataSerieDialog::dataCharacteristicsSelector()
{
    QVBoxLayout *layout = new QVBoxLayout();

    QRadioButton *radio1 = new QRadioButton("Linear");
    radio1->setChecked(true);
    layout->addWidget(radio1);
    layout->addWidget(new QRadioButton("Constant"));
    layout->addWidget(new QRadioButton("Random"));
    layout->addWidget(new QRadioButton("Sin"));
    layout->addWidget(new QRadioButton("Sin + random"));

    QGroupBox *groupBox = new QGroupBox("Data Characteristics");
    groupBox->setLayout(layout);

    return groupBox;
}

void DataSerieDialog::accept()
{
    accepted(radioSelection(m_seriesTypeSelector),
             radioSelection(m_columnCountSelector).toInt(),
             radioSelection(m_rowCountSelector).toInt(),
             radioSelection(m_dataCharacteristicsSelector),
             m_labelsSelector->isChecked());
    QDialog::accept();
}

QString DataSerieDialog::radioSelection(QGroupBox *groupBox)
{
    QString selection;
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(groupBox->layout());
    Q_ASSERT(layout);

    for (int i(0); i < layout->count(); i++) {
        QLayoutItem *item = layout->itemAt(i);
        Q_ASSERT(item);
        QRadioButton *radio = qobject_cast<QRadioButton *>(item->widget());
        Q_ASSERT(radio);
        if (radio->isChecked()) {
            selection = radio->text();
            break;
        }
    }

    qDebug() << "radioSelection: " << selection;
    return selection;
}
