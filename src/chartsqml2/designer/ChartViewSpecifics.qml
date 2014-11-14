/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

import QtQuick 2.0
import HelperWidgets 2.0
import QtQuick.Layouts 1.0

Column {
    anchors.left: parent.left
    anchors.right: parent.right

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Title")

        SectionLayout {
            rows: 1
            Label {
                text: qsTr("title")
            }

            SecondColumnLayout {
                LineEdit {
                    backendValue: backendValues.title
                    Layout.fillWidth: true
                }
                ExpandingSpacer {
                }
            }
        }
    }

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Title Color")

        ColorEditor {
            caption: qsTr("titleColor")
            backendValue: backendValues.titleColor
            supportGradient: false
        }
    }

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Background Color")

        ColorEditor {
            caption: qsTr("backgroundColor")
            backendValue: backendValues.backgroundColor
            supportGradient: false
        }
    }

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Background")

        SectionLayout {
            rows: 2
            Label {
                text: qsTr("backgroundRoundness")
                tooltip: qsTr("Diameter of the rounding circle at the corners")
                Layout.fillWidth: true
            }

            SecondColumnLayout {
                SpinBox {
                    backendValue: backendValues.backgroundRoundness
                    minimumValue: 0.1
                    maximumValue: 100.0
                    stepSize: 0.1
                    decimals: 1
                    Layout.fillWidth: true
                }
            }

            Label {
                text: qsTr("dropShadowEnabled")
                tooltip: qsTr("Enable border drop shadow")
                Layout.fillWidth: true
            }

            SecondColumnLayout {
                CheckBox {
                    backendValue: backendValues.dropShadowEnabled
                    Layout.fillWidth: true
                }
            }
        }
    }

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Fill Color")

        ColorEditor {
            caption: qsTr("fillColor")
            backendValue: backendValues.fillColor
            supportGradient: false
        }
    }

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Plot Area Color")

        ColorEditor {
            caption: qsTr("plotAreaColor")
            backendValue: backendValues.plotAreaColor
            supportGradient: false
        }
    }

    Section {
        anchors.left: parent.left
        anchors.right: parent.right
        caption: qsTr("Localization")

        SectionLayout {
            rows: 1
            Label {
                text: qsTr("localizeNumbers")
                tooltip: qsTr("Localize numbers")
                Layout.fillWidth: true
            }

            SecondColumnLayout {
                CheckBox {
                    backendValue: backendValues.localizeNumbers
                    Layout.fillWidth: true
                }
            }
        }
    }
}
