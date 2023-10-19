# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial

# Generated from src.pro.

add_subdirectory(charts)
if(TARGET Qt::Quick)
    add_subdirectory(chartsqml2)
endif()
