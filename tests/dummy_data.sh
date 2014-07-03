#!/bin/sh

#$Id: dummy_data.sh 652 2014-06-30 16:01:01Z serge $

for s in 1 2 3 4 5; do echo -n "hello=$s&bla=$s$s& blax=777" | nc localhost 1234; echo; done;