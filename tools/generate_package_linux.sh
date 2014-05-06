#!/bin/sh

CHARTS_TEMP_DIR=temp_dir
CHARTS_TEMP_DIR_FULL=../$CHARTS_TEMP_DIR

if [ "$1" = "" ]
then
    echo Usage: $0 version [branch or SHA]
    echo Branch defaults to master.
    echo Creates the package in parent dir.
    echo A temporary dir $CHARTS_TEMP_DIR_FULL is utilized for intermediate steps.
fi

if [ "$2" = "" ]
then
    CHARTS_BRANCH=origin/master
else
    CHARTS_BRANCH=$2
fi

CHARTS_VERSION=$1
CHARTS_CURRENT_DIR=$PWD
CHARTS_BUILD_DIR=$CHARTS_TEMP_DIR_FULL/tempbuild
CHARTS_PACKAGE_UNTAR_NAME=qt-charts-enterprise-src-$CHARTS_VERSION
CHARTS_PACKAGE_UNTAR_DIR=$CHARTS_TEMP_DIR_FULL/$CHARTS_PACKAGE_UNTAR_NAME
CHARTS_TEMP_TAR=qt-charts-enterprise-src-temp-$CHARTS_VERSION.tar
CHARTS_TEMP_TAR_FULL=$CHARTS_TEMP_DIR_FULL/$CHARTS_TEMP_TAR
CHARTS_FINAL_TAR=$CHARTS_CURRENT_DIR/../charts-enterprise-src-$CHARTS_VERSION.tar
CHARTS_FINAL_ZIP=$CHARTS_CURRENT_DIR/../charts-enterprise-src-$CHARTS_VERSION.zip
CHARTS_FINAL_7Z=$CHARTS_CURRENT_DIR/../charts-enterprise-src-$CHARTS_VERSION.7z

CHARTS_EXAMPLES_UNTAR_NAME=qt-charts-enterprise-examples-$CHARTS_VERSION
CHARTS_EXAMPLES_UNTAR_DIR=$CHARTS_TEMP_DIR_FULL/$CHARTS_EXAMPLES_UNTAR_NAME
CHARTS_EXAMPLES_TEMP_TAR=qt-charts-enterprise-examples-temp-$CHARTS_VERSION.tar
CHARTS_EXAMPLES_TEMP_TAR_FULL=$CHARTS_TEMP_DIR_FULL/$CHARTS_EXAMPLES_TEMP_TAR
CHARTS_EXAMPLES_FINAL_TAR=$CHARTS_CURRENT_DIR/../charts-enterprise-examples-$CHARTS_VERSION.tar
CHARTS_EXAMPLES_FINAL_7Z=$CHARTS_CURRENT_DIR/../charts-enterprise-examples-$CHARTS_VERSION.7z

# CHARTS_DOCS_UNTAR_NAME=qt-charts-enterprise-docs-$CHARTS_VERSION
CHARTS_DOCS_UNTAR_NAME=doc
CHARTS_DOCS_UNTAR_DIR=$CHARTS_TEMP_DIR_FULL/$CHARTS_DOCS_UNTAR_NAME
CHARTS_DOCS_TEMP_TAR=qt-charts-enterprise-docs-temp-$CHARTS_VERSION.tar
CHARTS_DOCS_TEMP_TAR_FULL=$CHARTS_TEMP_DIR_FULL/$CHARTS_DOCS_TEMP_TAR
CHARTS_DOCS_FINAL_TAR=$CHARTS_CURRENT_DIR/../charts-enterprise-doc-$CHARTS_VERSION.tar
CHARTS_DOCS_FINAL_ZIP=$CHARTS_CURRENT_DIR/../charts-enterprise-doc-$CHARTS_VERSION.zip
CHARTS_DOCS_FINAL_7Z=$CHARTS_CURRENT_DIR/../charts-enterprise-doc-$CHARTS_VERSION.7z

echo Exporting $CHARTS_BRANCH to $CHARTS_TEMP_TAR_FULL...
rm -r -f $CHARTS_TEMP_DIR_FULL 2> /dev/null
mkdir -p $CHARTS_TEMP_DIR_FULL 2> /dev/null
git fetch
git archive --format tar --output $CHARTS_TEMP_TAR_FULL $CHARTS_BRANCH

echo Unpacking $CHARTS_TEMP_TAR_FULL to $CHARTS_PACKAGE_UNTAR_DIR and $CHARTS_BUILD_DIR...
mkdir -p $CHARTS_PACKAGE_UNTAR_DIR 2> /dev/null
mkdir -p $CHARTS_BUILD_DIR 2> /dev/null
tar -xvf $CHARTS_TEMP_TAR_FULL -C $CHARTS_PACKAGE_UNTAR_DIR > /dev/null
tar -xvf $CHARTS_TEMP_TAR_FULL -C $CHARTS_BUILD_DIR > /dev/null
#Workaround for git archive bug
rm -r -f $CHARTS_PACKAGE_UNTAR_DIR/tools
rm -r -f $CHARTS_PACKAGE_UNTAR_DIR/tests
rm -r -f $CHARTS_BUILD_DIR/tools
rm -r -f $CHARTS_BUILD_DIR/tests

echo Creating package for examples and demos
mkdir -p $CHARTS_EXAMPLES_UNTAR_DIR 2> /dev/null
cp -r $CHARTS_BUILD_DIR/examples $CHARTS_EXAMPLES_UNTAR_DIR
cp -r $CHARTS_BUILD_DIR/demos $CHARTS_EXAMPLES_UNTAR_DIR
cd $CHARTS_EXAMPLES_UNTAR_DIR
tar -cvf $CHARTS_EXAMPLES_FINAL_TAR * >/dev/null
gzip $CHARTS_EXAMPLES_FINAL_TAR >/dev/null
7z a $CHARTS_EXAMPLES_FINAL_7Z * >/dev/null
cd $CHARTS_CURRENT_DIR

echo Generating includes, mkspecs, and docs in $CHARTS_BUILD_DIR...
cd $CHARTS_BUILD_DIR
mkdir -p .git 2> /dev/null
qmake > /dev/null 2> /dev/null
make docs > /dev/null 2> /dev/null
cd $CHARTS_CURRENT_DIR

echo Creating package for docs
mkdir -p $CHARTS_DOCS_UNTAR_DIR 2> /dev/null
mkdir - $CHARTS_DOCS_UNTAR_DIR/qtcharts 2> /dev/null
cp $CHARTS_BUILD_DIR/doc/qch/qtcharts.qch $CHARTS_DOCS_UNTAR_DIR
cp $CHARTS_BUILD_DIR/doc/html/examples-manifest.xml $CHARTS_DOCS_UNTAR_DIR/qtcharts
cp $CHARTS_BUILD_DIR/doc/html/demos-manifest.xml $CHARTS_DOCS_UNTAR_DIR/qtcharts
7z a $CHARTS_DOCS_FINAL_7Z $CHARTS_DOCS_UNTAR_DIR > /dev/null
cd $CHARTS_CURRENT_DIR

echo Copying generated files to $CHARTS_PACKAGE_UNTAR_DIR
cp -r $CHARTS_BUILD_DIR/doc/qch $CHARTS_PACKAGE_UNTAR_DIR/doc/qch
cp -r $CHARTS_BUILD_DIR/doc/html $CHARTS_PACKAGE_UNTAR_DIR/doc/html

echo Repackaging $CHARTS_PACKAGE_UNTAR_DIR to $CHARTS_FINAL_TAR
rm $CHARTS_FINAL_TAR 2> /dev/null
cd $CHARTS_TEMP_DIR_FULL
tar -cvf $CHARTS_FINAL_TAR $CHARTS_PACKAGE_UNTAR_NAME >/dev/null
gzip $CHARTS_FINAL_TAR >/dev/null
echo Zip $CHARTS_PACKAGE_UNTAR_NAME
zip -r -l $CHARTS_FINAL_ZIP $CHARTS_PACKAGE_UNTAR_NAME >/dev/null
7z a $CHARTS_FINAL_7Z $CHARTS_PACKAGE_UNTAR_NAME >/dev/null
cd $CHARTS_CURRENT_DIR

exit 0
