#!/bin/bash

function pretty_message()
{
    if [ $# -ne 0 ]; then
        echo -e $(date +%Y.%m.%d-%H:%M:%S) "$@"
    else
        echo
    fi
}

if [ x"$g_dry_run" == xy -o x"$g_dry_run" == xyes ]; then
    first=pretty_message
else
    first=
fi

while true
do  
    pretty_message "@@@@@@@@@@ starting shadowsocks ... @@@@@@@@@@"

    $first ssserver -c /home/zyw/bright/config.json
    if [ $? -ne 0 ]; then
	pretty_message "running failed"
    else
	pretty_message "exit normal"
	break
fi
done
