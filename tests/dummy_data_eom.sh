#!/bin/sh

#$Id: dummy_data_eom.sh 713 2014-07-07 17:01:48Z serge $

for s in 1 2 3 4 5; do echo -n "hello=$s&bla=$s$s& blax=777<EOM>" | nc localhost 1234; echo; done;