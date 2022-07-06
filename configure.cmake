# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0



#### Inputs



#### Libraries



#### Tests



#### Features


qt_extra_definition("QT_VERSION_STR" "\"${PROJECT_VERSION}\"" PUBLIC)
qt_extra_definition("QT_VERSION_MAJOR" ${PROJECT_VERSION_MAJOR} PUBLIC)
qt_extra_definition("QT_VERSION_MINOR" ${PROJECT_VERSION_MINOR} PUBLIC)
qt_extra_definition("QT_VERSION_PATCH" ${PROJECT_VERSION_PATCH} PUBLIC)
