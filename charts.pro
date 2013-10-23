!include(config.pri) {
    error('Missing config.pri')
}

TEMPLATE = subdirs
SUBDIRS = src plugins
!nomake_demos_examples: SUBDIRS += demos examples
exists(tests): SUBDIRS += tests

development_build: message('Development build')

CONFIG += ordered
QMAKE_CXXFLAGS += -g -Wall
unix:QMAKE_DISTCLEAN += -r build bin include lib doc/html
win32:QMAKE_DISTCLEAN += /Q /s build bin include lib doc\\html

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/qtcommercialchart.prf
INSTALLS += feature

# docs
CHARTS_VERSION = 1.3.1
CHARTS_VERSION_TAG = 131

contains(QT_MAJOR_VERSION, 5) {
    QDOC_CONFFILE = qcharts-qt5.qdocconf
    DEFINES += QDOC_QT5
} else {
    QDOC_CONFFILE = qcharts-qt4.qdocconf
}

contains(QMAKE_HOST.os, Windows) {
    QDOC_CONF = $$CHART_BUILD_DOC_DIR\\docconf\\$$QDOC_CONFFILE
    win32-g++|qnx {
        VERSION_SETTINGS = \
            set QT_CHARTS_VERSION=$$CHARTS_VERSION&& set QT_CHARTS_VERSION_TAG=$$CHARTS_VERSION_TAG&&
    } else {
        VERSION_SETTINGS = \
            set QT_CHARTS_VERSION=$$CHARTS_VERSION $$escape_expand(\\n\\t) \
            set QT_CHARTS_VERSION_TAG=$$CHARTS_VERSION_TAG $$escape_expand(\\n\\t)
    }
} else {
    QDOC_CONF = $$CHART_BUILD_DOC_DIR/docconf/$$QDOC_CONFFILE
    VERSION_SETTINGS = \
        QT_CHARTS_VERSION=$$CHARTS_VERSION QT_CHARTS_VERSION_TAG=$$CHARTS_VERSION_TAG
}

contains(QT_MAJOR_VERSION, 5) {
    QDOC_CMD = qdoc
    HELPGENERATOR_CMD = qhelpgenerator -platform minimal
} else {
    QDOC_CMD = qdoc3
    HELPGENERATOR_CMD = qhelpgenerator
}

QHP_FILE = doc/html/qtcharts.qhp
QCH_FILE = doc/qch/qtcharts.qch

docs.target = docs
docs.depends = qch_docs FORCE
qch_docs.target = qch_docs
qch_docs.commands = $$HELPGENERATOR_CMD $$QHP_FILE -o $$QCH_FILE
qch_docs.depends = html_docs FORCE
html_docs.target = html_docs
html_docs.commands = $$VERSION_SETTINGS $$QDOC_CMD $$QDOC_CONF
html_docs.depends = FORCE

QMAKE_EXTRA_TARGETS += docs qch_docs html_docs

# coverage
unix:coverage:{
    QMAKE_DISTCLEAN += -r ./coverage
    QMAKE_CLEAN += build/*.gcda build/*.gcno
    QMAKE_EXTRA_TARGETS +=  buildcoverage runcoverage gencoverage

    buildcoverage.target = build_coverage
    buildcoverage.depends = all
    buildcoverage.commands = mkdir -p ./coverage; \
                             make -C src prepare_coverage;

    runcoverage.target = run_coverage
    runcoverage.depends = buildcoverage
    runcoverage.commands = for f in `ls ./bin/tst_*` ; do echo "processing \$\$f test..."; \$\$f >> unit.log; done ; exit 0;

    gencoverage.target = gen_coverage
    gencoverage.depends = runcoverage
    gencoverage.commands =  make -C src gen_coverage; \
                            genhtml  -o ./coverage ./coverage/coverage.info --prefix $$PWD
}

