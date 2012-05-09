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

    ChartView {
        id: chartView
        anchors.top: parent.top
        anchors.bottom: weatherImageRow.top
        anchors.left: parent.left
        anchors.right: parent.right
        axisX.min: 0
        axisX.max: 6
        axisY.min: 0
        axisY.max: 50

        // TODO: implement categories
//        AxisCategory { axis: AxisCategory.AxisX; value: 0.0; label: "" }
//        AxisCategory { axis: AxisCategory.AxisX; value: 1.0; label: "Today" }
//        AxisCategory { axis: AxisCategory.AxisX; value: 2.0; label: "Tomorrow" }
//        AxisCategory { axis: AxisCategory.AxisX; value: 3.0; label: "Day after tomorrow" }

        LineSeries {
            model: maxModel
        }

        LineSeries {
            model: minModel
        }

        // TODO: use a single base model with mappings instead of two separate xy models
//        LineSeries {
//            model: chartModel
//            modelMapping: XyModelMapping {
//                xColumn: 0
//                yColumn: 1
//            }
//        }
//        LineSeries {
//            model: chartModel
//            modelMapping: XyModelMapping {
//                xColumn: 0
//                yColumn: 2
//            }
//        }
    }

//    ChartModel {
//        id: chartModel
//    }

    XYModel {
        id: maxModel
    }

    XYModel {
        id: minModel
    }

    Component.onCompleted: {
        // TODO: use live data instead of hard coded example data
        // in case an application key was defined for this demo app
//            var xhr = new XMLHttpRequest;
//            var appKey = "";
//            xhr.open("GET", "http://free.worldweatheronline.com/feed/weather.ashx?q=Jyv%c3%a4skyl%c3%a4,Finland&format=json&num_of_days=5&key=" + appKey");
//            xhr.onreadystatechange = function() {
//                        if (xhr.readyState == XMLHttpRequest.DONE) {
//                            var a = JSON.parse(xhr.responseText);
//                            console.log("a: " + a);
//                            console.log("response: " + xhr.responseText);
//                            for (var b in a) {
//                                var o = a[b];
//                                console.log("o: " + o);
////                                model.append({id: o.id, name: o.name, duration: o.duration});
//                            }
//                        }
//                    }
//            xhr.send();

        var responseText = "{ \"data\": { \"current_condition\": [ {\"cloudcover\": \"10\", \"humidity\": \"61\", \"observation_time\": \"06:26 AM\", \"precipMM\": \"0.0\", \"pressure\": \"1022\", \"temp_C\": \"6\", \"temp_F\": \"43\", \"visibility\": \"10\", \"weatherCode\": \"113\",  \"weatherDesc\": [ {\"value\": \"Sunny\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0001_sunny.png\" } ], \"winddir16Point\": \"SE\", \"winddirDegree\": \"140\", \"windspeedKmph\": \"7\", \"windspeedMiles\": \"4\" } ],  \"request\": [ {\"query\": \"Jyvaskyla, Finland\", \"type\": \"City\" } ],  \"weather\": [ {\"date\": \"2012-05-09\", \"precipMM\": \"0.4\", \"tempMaxC\": \"14\", \"tempMaxF\": \"57\", \"tempMinC\": \"7\", \"tempMinF\": \"45\", \"weatherCode\": \"116\",  \"weatherDesc\": [ {\"value\": \"Partly Cloudy\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0002_sunny_intervals.png\" } ], \"winddir16Point\": \"S\", \"winddirDegree\": \"179\", \"winddirection\": \"S\", \"windspeedKmph\": \"20\", \"windspeedMiles\": \"12\" }, {\"date\": \"2012-05-10\", \"precipMM\": \"2.4\", \"tempMaxC\": \"13\", \"tempMaxF\": \"55\", \"tempMinC\": \"8\", \"tempMinF\": \"46\", \"weatherCode\": \"266\",  \"weatherDesc\": [ {\"value\": \"Light drizzle\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0017_cloudy_with_light_rain.png\" } ], \"winddir16Point\": \"SW\", \"winddirDegree\": \"219\", \"winddirection\": \"SW\", \"windspeedKmph\": \"21\", \"windspeedMiles\": \"13\" }, {\"date\": \"2012-05-11\", \"precipMM\": \"11.1\", \"tempMaxC\": \"15\", \"tempMaxF\": \"59\", \"tempMinC\": \"7\", \"tempMinF\": \"44\", \"weatherCode\": \"266\",  \"weatherDesc\": [ {\"value\": \"Light drizzle\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0017_cloudy_with_light_rain.png\" } ], \"winddir16Point\": \"SSW\", \"winddirDegree\": \"200\", \"winddirection\": \"SSW\", \"windspeedKmph\": \"20\", \"windspeedMiles\": \"12\" }, {\"date\": \"2012-05-12\", \"precipMM\": \"2.8\", \"tempMaxC\": \"7\", \"tempMaxF\": \"44\", \"tempMinC\": \"2\", \"tempMinF\": \"35\", \"weatherCode\": \"317\",  \"weatherDesc\": [ {\"value\": \"Light sleet\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0021_cloudy_with_sleet.png\" } ], \"winddir16Point\": \"NW\", \"winddirDegree\": \"311\", \"winddirection\": \"NW\", \"windspeedKmph\": \"24\", \"windspeedMiles\": \"15\" }, {\"date\": \"2012-05-13\", \"precipMM\": \"0.4\", \"tempMaxC\": \"6\", \"tempMaxF\": \"42\", \"tempMinC\": \"2\", \"tempMinF\": \"35\", \"weatherCode\": \"116\",  \"weatherDesc\": [ {\"value\": \"Partly Cloudy\" } ],  \"weatherIconUrl\": [ {\"value\": \"http:\/\/www.worldweatheronline.com\/images\/wsymbols01_png_64\/wsymbol_0002_sunny_intervals.png\" } ], \"winddir16Point\": \"WNW\", \"winddirDegree\": \"281\", \"winddirection\": \"WNW\", \"windspeedKmph\": \"21\", \"windspeedMiles\": \"13\" } ] }}";
        var a = JSON.parse(responseText);

        for (var i in a.data.weather) {
            var weatherObj = a.data.weather[i];
            maxModel.append([Number(i) + 1, weatherObj.tempMaxC]);
            minModel.append([Number(i) + 1, weatherObj.tempMinC]);
            weatherImageModel.append({"imageSource":weatherObj.weatherIconUrl[0].value});
        }
    }

    ListModel {
        id: weatherImageModel
    }

    Row {
        id: weatherImageRow
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 25
        anchors.right: parent.right
        anchors.rightMargin: 25
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
}
