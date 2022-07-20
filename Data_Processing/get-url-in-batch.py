import os
import sys
from subprocess import Popen, PIPE

path = input()
files = os.listdir(path)

for file in files:
    location = "Geturl.exe"
    d = Popen([location],stdin=PIPE,stdout=PIPE,stderr=PIPE, encoding="UTF8")
    d.stdin.write()
