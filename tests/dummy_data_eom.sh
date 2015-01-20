#!/bin/sh

# $Revision: 1419 $ $Date:: 2015-01-20 #$ $Author: serge $

for s in 1 2 3 4 5; do echo -n "hello=$s&bla=$s$s& blax=777<EOM>" | nc localhost 1234; echo; done;