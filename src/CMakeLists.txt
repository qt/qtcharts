# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from src.pro.

set(QT_SBOM_DEFAULT_QT_LICENSE_ID_LIBRARIES "QT_COMMERCIAL_OR_GPL3")

add_subdirectory(charts)
if(TARGET Qt::Quick)
    add_subdirectory(chartsqml2)
endif()
