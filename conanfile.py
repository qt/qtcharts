# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

from conans import ConanFile
import re
from pathlib import Path
from typing import Dict, Any

_qtcharts_features = [
    "charts-area-chart",
    "charts-bar-chart",
    "charts-boxplot-chart",
    "charts-candlestick-chart",
    "charts-datetime-axis",
    "charts-line-chart",
    "charts-pie-chart",
    "charts-scatter-chart",
    "charts-spline-chart",
]


def _parse_qt_version_by_key(key: str) -> str:
    with open(Path(__file__).parent.resolve() / ".cmake.conf") as f:
        m = re.search(fr'{key} .*"(.*)"', f.read())
    return m.group(1) if m else ""


def _get_qt_minor_version() -> str:
    return ".".join(_parse_qt_version_by_key("QT_REPO_MODULE_VERSION").split(".")[:2])


class QtCharts(ConanFile):
    name = "qtcharts"
    license = "GPL-3.0+, Commercial Qt License Agreement"
    author = "The Qt Company <https://www.qt.io/contact-us>"
    url = "https://code.qt.io/cgit/qt/qtcharts.git"
    description = (
        "Qt Charts module provides a set of easy to use chart components. "
        "It uses the Qt Graphics View Framework, therefore charts can be easily integrated "
        "to modern user interfaces. Qt Charts can be used as QWidgets, QGraphicsWidget, or QML types. "
        "Users can easily create impressive graphs by selecting one of the charts themes."
    )
    topics = "qt", "qt6", "qtcharts", "charts", "graphs"
    settings = "os", "compiler", "arch", "build_type"
    # for referencing the version number and prerelease tag and dependencies info
    exports = ".cmake.conf", "dependencies.yaml"
    exports_sources = "*", "!conan*.*"
    python_requires = f"qt-conan-common/{_get_qt_minor_version()}@qt/everywhere"
    python_requires_extend = "qt-conan-common.QtLeafModule"

    def get_qt_leaf_module_options(self) -> Dict[str, Any]:
        """Implements abstractmethod from qt-conan-common.QtLeafModule"""
        return self._shared.convert_qt_features_to_conan_options(_qtcharts_features)

    def get_qt_leaf_module_default_options(self) -> Dict[str, Any]:
        """Implements abstractmethod from qt-conan-common.QtLeafModule"""
        return self._shared.convert_qt_features_to_default_conan_options(_qtcharts_features)
