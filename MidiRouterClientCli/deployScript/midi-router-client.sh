#!/bin/sh
LD_LIBRARY_PATH=/opt/midi-router-client-cli/lib:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH
/opt/midi-router-client-cli/bin/midi-router-client-cli "$@"
