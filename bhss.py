#! /usr/bin/python
import os
import commands
import time

def execCmd(cmd):
    return os.popen(cmd)

while True:
    time.sleep(1)
    cmd = "ps uxwww | grep shadowsocks | grep -v grep | awk '{print $2}'"
    ret = commands.getoutput(cmd)    
    if ret == '':
        print "no ss start it"
        cmd = 'nohup ssserver -c /usr/local/lib/python2.7/dist-packages/shadowsocks/config.json &'
        os.system(cmd)
        time.sleep(10)
