# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_path_join(destination ${QT_INSTALL_DIR} "${INSTALL_QMLDIR}/QtCharts/designer")
qt_copy_or_install(
    FILES
        ChartViewSpecifics.qml
        qtcharts.metainfo
    DESTINATION ${destination}
)

add_subdirectory(default)
add_subdirectory(images)
