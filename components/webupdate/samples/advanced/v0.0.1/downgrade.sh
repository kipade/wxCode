#!/bin/sh
# Author: Francesco Montorsi
# RCS-ID: $Id: downgrade.sh 313 2005-10-23 19:29:38Z frm $
# Purpose: this script should be used after testing the WebUpdater, and thus
#          after having upgraded this ADVANCED sample from v0.0.1 to v1.5.0,
#          to "downgrade" it back to version v0.0.1
#          This is very useful to test the WebUpdater again...


cp -r local_0_0_1.xml local.xml
cp -r simpledata_0_0_1.txt simpledata.txt

# remove addons
rm -rf addon1
rm -rf addon2
rm -rf addon3

rm -f test.txt
