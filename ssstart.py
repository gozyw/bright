#! /usr/bin/python
import os
cmd = 'screen -S Shadowsocks ssserver -c /usr/local/lib/python2.7/dist-packages/shadowsocks/config.json'
os.system(cmd)
