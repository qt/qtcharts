/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQml.Models

//![1]
ListModel {
    // Hard-coded test data
    ListElement { speedTrap:0; driver: "Fittipaldi"; speed:104.12 }
        ListElement { speedTrap:0; driver:"Stewart"; speed:106.12 }
        ListElement { speedTrap:0; driver:"Hunt"; speed:106.12 }
//![1]
        ListElement { speedTrap:1; driver:"Fittipaldi"; speed:115.12 }
        ListElement { speedTrap:1; driver:"Stewart"; speed:114.12 }
        ListElement { speedTrap:1; driver:"Hunt"; speed:115.12 }
        ListElement { speedTrap:2; driver:"Hunt"; speed:165.23 }
        ListElement { speedTrap:2; driver:"Fittipaldi"; speed:175.23 }
        ListElement { speedTrap:2; driver:"Stewart"; speed:168.23 }
        ListElement { speedTrap:3; driver:"Hunt"; speed:104.87 }
        ListElement { speedTrap:3; driver:"Fittipaldi"; speed:104.43 }
        ListElement { speedTrap:3; driver:"Stewart"; speed:94.83 }
        ListElement { speedTrap:4; driver:"Hunt"; speed:107.87 }
        ListElement { speedTrap:4; driver:"Fittipaldi"; speed:111.84 }
        ListElement { speedTrap:4; driver:"Stewart"; speed:106.84 }
        ListElement { speedTrap:5; driver:"Hunt"; speed:94.87 }
        ListElement { speedTrap:5; driver:"Stewart"; speed:92.37 }
        ListElement { speedTrap:5; driver:"Fittipaldi"; speed:99.37 }
        ListElement { speedTrap:6; driver:"Hunt"; speed:52.87 }
        ListElement { speedTrap:6; driver:"Fittipaldi"; speed:42.87 }
        ListElement { speedTrap:6; driver:"Stewart"; speed:55.87 }
        ListElement { speedTrap:7; driver:"Hunt"; speed:77.87 }
        ListElement { speedTrap:7; driver:"Fittipaldi"; speed:72.87 }
        ListElement { speedTrap:7; driver:"Stewart"; speed:87.87 }
        ListElement { speedTrap:8; driver:"Hunt"; speed:94.17 }
        ListElement { speedTrap:8; driver:"Fittipaldi"; speed:98.17 }
        ListElement { speedTrap:8; driver:"Stewart"; speed:84.17 }
        ListElement { speedTrap:9; driver:"Hunt"; speed:91.87 }
        ListElement { speedTrap:9; driver:"Fittipaldi"; speed:71.87 }
        ListElement { speedTrap:9; driver:"Stewart"; speed:81.87 }
        ListElement { speedTrap:10; driver:"Hunt"; speed:104.87 }
        ListElement { speedTrap:10; driver:"Fittipaldi"; speed:115.87 }
        ListElement { speedTrap:10; driver:"Stewart"; speed:119.87 }
        ListElement { speedTrap:11; driver:"Hunt"; speed:162.87 }
        ListElement { speedTrap:11; driver:"Fittipaldi"; speed:155.84 }
        ListElement { speedTrap:11; driver:"Stewart"; speed:152.84 }
        ListElement { speedTrap:12; driver:"Hunt"; speed:181.87 }
        ListElement { speedTrap:12; driver:"Fittipaldi"; speed:161.85 }
        ListElement { speedTrap:12; driver:"Stewart"; speed:167.85 }
        ListElement { speedTrap:13; driver:"Hunt"; speed:155.87 }
        ListElement { speedTrap:13; driver:"Fittipaldi"; speed:154.87 }
        ListElement { speedTrap:13; driver:"Stewart"; speed:164.87 }
        ListElement { speedTrap:14; driver:"Hunt"; speed:197.57 }
        ListElement { speedTrap:14; driver:"Fittipaldi"; speed:187.54 }
        ListElement { speedTrap:14; driver:"Stewart"; speed:180.54 }
        ListElement { speedTrap:15; driver:"Fittipaldi"; speed:216.87 }
        ListElement { speedTrap:15; driver:"Hunt"; speed:207.87 }
        ListElement { speedTrap:15; driver:"Stewart"; speed:197.87 }
        ListElement { speedTrap:16; driver:"Hunt"; speed:82.87 }
        ListElement { speedTrap:16; driver:"Fittipaldi"; speed:79.37 }
        ListElement { speedTrap:16; driver:"Stewart"; speed:85.37 }
        ListElement { speedTrap:17; driver:"Hunt"; speed:153.87 }
        ListElement { speedTrap:17; driver:"Fittipaldi"; speed:143.87 }
        ListElement { speedTrap:17; driver:"Stewart"; speed:133.87 }
        ListElement { speedTrap:18; driver:"Hunt"; speed:89.87 }
        ListElement { speedTrap:18; driver:"Fittipaldi"; speed:95.85 }
        ListElement { speedTrap:18; driver:"Stewart"; speed:98.85 }
        ListElement { speedTrap:19; driver:"Hunt"; speed:169.87 }
        ListElement { speedTrap:19; driver:"Stewart"; speed:167.87 }
        ListElement { speedTrap:19; driver:"Fittipaldi"; speed:154.87 }
}
