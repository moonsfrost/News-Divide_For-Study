import os
import sys

path = sys.argv[1]
Folder = os.listdir(path)
temp = open('.\\temp',"w")
for file in Folder:
    temp.write(file)
    temp.write('\n')