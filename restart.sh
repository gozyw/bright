ps ux | grep bhss.py | grep -v grep | awk '{print $2}' | xargs kill -9
ps ux | grep ssserver | grep -v grep | awk '{print $2}' | xargs kill -9
nohup /home/zyw/bright/bhss.py &> /home/zyw/bright/bh.log &
