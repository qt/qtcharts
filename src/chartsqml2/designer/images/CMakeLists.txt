# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_path_join(destination ${QT_INSTALL_DIR} "${INSTALL_QMLDIR}/QtCharts/designer/images")
qt_copy_or_install(
    FILES
        areaseries-chart-icon.png
        areaseries-chart-icon16.png
        barseries-icon.png
        barseries-icon16.png
        boxplotseries-chart-icon.png
        boxplotseries-chart-icon16.png
        horizontalbarseries-icon.png
        horizontalbarseries-icon16.png
        horizontalpercentbarseries-icon.png
        horizontalpercentbarseries-icon16.png
        horizontalstackedbarseries-icon.png
        horizontalstackedbarseries-icon16.png
        lineseries-chart-icon.png
        lineseries-chart-icon16.png
        percentbarseries-icon.png
        percentbarseries-icon16.png
        pieseries-chart-icon.png
        pieseries-chart-icon16.png
        scatterseries-chart-icon.png
        scatterseries-chart-icon16.png
        splineseries-chart-icon.png
        splineseries-chart-icon16.png
        stackedbarseries-icon.png
        stackedbarseries-icon16.png
        areaseries-polar-icon.png
        areaseries-polar-icon16.png
        lineseries-polar-icon.png
        lineseries-polar-icon16.png
        scatterseries-polar-icon.png
        scatterseries-polar-icon16.png
        splineseries-polar-icon.png
        splineseries-polar-icon16.png
    DESTINATION "${destination}"
)
