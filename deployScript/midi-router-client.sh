#!/bin/sh
LD_LIBRARY_PATH=/opt/midi-router-client/lib:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH
/opt/midi-router-client/bin/midi-router-client "$@"
