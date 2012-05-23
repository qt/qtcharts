/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 1.1
import QtCommercial.Chart 1.0

Rectangle {
    width: 360
    height: 360

    //![1]
    ChartView {
        id: chartView
        title: "Weather forecast"
    //![1]
        anchors.top: parent.top
        anchors.bottom: weatherImageRow.top
        anchors.left: parent.left
        anchors.right: parent.right
        legend: ChartView.LegendTop

    //![2]
//        BarSeries {
        GroupedBarSeries {
            barCategories: [ "2008", "2009", "2010", "2011", "2012" ]
            BarSet {
                id: rainfallSet
                name: "Rainfall"
            }
        }

        ScatterSeries {
            id: maxTempSeries
            name: "Max. temperature"
        }

        ScatterSeries {
            id: minTempSeries
            name: "Min. temperature"
        }
    //![2]
    }

    // A timer to refresh the forecast every 5 minutes
    Timer {
        interval: 300000;
        repeat: true
        triggeredOnStart: true
        running: true
        onTriggered: {
            if (weatherAppKey != "") {                
                //![3]
                // Make HTTP GET request and parse the result
                var xhr = new XMLHttpRequest;
                xhr.open("GET",
                         "http://free.worldweatheronline.com/feed/weather.ashx?q=Jyv%c3%a4skyl%c3%a4,Finland&format=json&num_of_days=5&key="
                         + weatherAppKey);
                xhr.onreadystatechange = function() {
                    if (xhr.readyState == XMLHttpRequest.DONE) {
                        var a = JSON.parse(xhr.responseText);
                        parseWeatherData(a);
                    }
                }
                xhr.send();
                //![3]
            } else {
                // No app key for worldweatheronline.com given by the user -> use static data
                var responseText = "{ \"data\": { \"current_condition\": [ {\"cloudcover\": \"10\", \"humidity\": \"61\", \"observation_time\": \"06:26 AM\", \"precipMM\": \"0.0\", \"pressure\": \"1022\", \"temp_C\": \"6\", \"temp_F\": \"43\", \"visibility\": \"10\", \"weatherCode\": \"113\",  \"weatherDesc\": [ {\"value\": \"Sunny\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0001_sunny.png\" } ], \"winddir16Point\": \"SE\", \"winddirDegree\": \"140\", \"windspeedKmph\": \"7\", \"windspeedMiles\": \"4\" } ],  \"request\": [ {\"query\": \"Jyvaskyla, Finland\", \"type\": \"City\" } ],  \"weather\": [ {\"date\": \"2012-05-09\", \"precipMM\": \"0.4\", \"tempMaxC\": \"14\", \"tempMaxF\": \"57\", \"tempMinC\": \"7\", \"tempMinF\": \"45\", \"weatherCode\": \"116\",  \"weatherDesc\": [ {\"value\": \"Partly Cloudy\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0002_sunny_intervals.png\" } ], \"winddir16Point\": \"S\", \"winddirDegree\": \"179\", \"winddirection\": \"S\", \"windspeedKmph\": \"20\", \"windspeedMiles\": \"12\" }, {\"date\": \"2012-05-10\", \"precipMM\": \"2.4\", \"tempMaxC\": \"13\", \"tempMaxF\": \"55\", \"tempMinC\": \"8\", \"tempMinF\": \"46\", \"weatherCode\": \"266\",  \"weatherDesc\": [ {\"value\": \"Light drizzle\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0017_cloudy_with_light_rain.png\" } ], \"winddir16Point\": \"SW\", \"winddirDegree\": \"219\", \"winddirection\": \"SW\", \"windspeedKmph\": \"21\", \"windspeedMiles\": \"13\" }, {\"date\": \"2012-05-11\", \"precipMM\": \"11.1\", \"tempMaxC\": \"15\", \"tempMaxF\": \"59\", \"tempMinC\": \"7\", \"tempMinF\": \"44\", \"weatherCode\": \"266\",  \"weatherDesc\": [ {\"value\": \"Light drizzle\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0017_cloudy_with_light_rain.png\" } ], \"winddir16Point\": \"SSW\", \"winddirDegree\": \"200\", \"winddirection\": \"SSW\", \"windspeedKmph\": \"20\", \"windspeedMiles\": \"12\" }, {\"date\": \"2012-05-12\", \"precipMM\": \"2.8\", \"tempMaxC\": \"7\", \"tempMaxF\": \"44\", \"tempMinC\": \"2\", \"tempMinF\": \"35\", \"weatherCode\": \"317\",  \"weatherDesc\": [ {\"value\": \"Light sleet\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0021_cloudy_with_sleet.png\" } ], \"winddir16Point\": \"NW\", \"winddirDegree\": \"311\", \"winddirection\": \"NW\", \"windspeedKmph\": \"24\", \"windspeedMiles\": \"15\" }, {\"date\": \"2012-05-13\", \"precipMM\": \"0.4\", \"tempMaxC\": \"6\", \"tempMaxF\": \"42\", \"tempMinC\": \"2\", \"tempMinF\": \"35\", \"weatherCode\": \"116\",  \"weatherDesc\": [ {\"value\": \"Partly Cloudy\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0002_sunny_intervals.png\" } ], \"winddir16Point\": \"WNW\", \"winddirDegree\": \"281\", \"winddirection\": \"WNW\", \"windspeedKmph\": \"21\", \"windspeedMiles\": \"13\" } ] }}";
                var a = JSON.parse(responseText);
                parseWeatherData(a);
            }
        }
    }

    Row {
        id: weatherImageRow
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.right: parent.right
        anchors.rightMargin: 25

        ListModel {
            id: weatherImageModel
        }

        Repeater {
            id: repeater
            model: weatherImageModel
            delegate: Image {
                source: imageSource
                width: weatherImageRow.width / weatherImageModel.count
                height: width
                fillMode: Image.PreserveAspectCrop
            }
        }
    }

    function parseWeatherData(weatherData) {
        // Clear previous values
        chartView.axisX.min = 0;
        chartView.axisX.max = 5;
        chartView.axisY.min = 0;
        chartView.axisY.max = 5;
        maxTempSeries.clear();
        minTempSeries.clear();
        weatherImageModel.clear();

        //![4]
        // Loop through the parsed JSON
        for (var i in weatherData.data.weather) {
            var weatherObj = weatherData.data.weather[i];
            //![4]

            //![5]
            // Store temperature values, rainfall and weather icon
            maxTempSeries.append(i, weatherObj.tempMaxC);
            minTempSeries.append(i, weatherObj.tempMinC);
            rainfallSet.append(i, weatherObj.precipMM);

            weatherImageModel.append({"imageSource":weatherObj.weatherIconUrl[0].value});
            //![5]

            // Update scale of the chart
            chartView.axisX.min = 0;
            chartView.axisX.max = i;
            while (chartView.axisY.min >= Number(weatherObj.tempMinC))
                chartView.axisY.min = chartView.axisY.min - 10;
            while (chartView.axisY.max <= Number(weatherObj.tempMaxC))
                chartView.axisY.max = chartView.axisY.max + 10;

            // Set the x-axis labels to the dates of the forecast
            // TODO: the API could probably be more intuitive..
            // Now it takes an array of strings: chartView.axisXLabels = ["value1", "label1", "value2", "label2", ...]
            var xLabels = chartView.axisXLabels;
            xLabels[Number(i) * 2] = i;
            xLabels[(Number(i) * 2) + 1] = weatherObj.date.substring(5, 10);
            chartView.axisXLabels = xLabels;
        }
    }
}
