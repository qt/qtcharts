#include "widget.h"
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QChartView>
#include <QLineSeries>
#include <QChart>
#include <QVBoxLayout>
#include <QValueAxis>
#include "xyseriesiodevice.h"

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_device(0),
      m_chart(0),
      m_series(0),
      m_audioInput(0)
{
    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(800, 600);
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 8000);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 256);
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->setTitle("Data from microphone");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);

    QAudioFormat formatAudio;
    formatAudio.setFrequency(8000);
    formatAudio.setChannels(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

    m_device = new XYSeriesIODevice(m_series, this);
    m_device->open(QIODevice::WriteOnly);

    m_audioInput->setBufferSize(10);
    m_audioInput->start(m_device);
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();
}
