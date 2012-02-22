import QtQuick 1.0

Item {
    id: container
    width: 400
    height: 500
    Component.onCompleted: {
    var co = Qt.createComponent("main.qml")
    if (co.status == Component.Ready) {
            var o = co.createObject(container)
        } else {
            console.log(co.errorString())
            console.log("QtCommercial.Chart 1.1 not available")
            console.log("Please use correct QML_IMPORT_PATH export")
         }
    }
}