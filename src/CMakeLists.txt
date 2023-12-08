# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from src.pro.

add_subdirectory(charts)
if(TARGET Qt::Quick)
    add_subdirectory(chartsqml2)
endif()
