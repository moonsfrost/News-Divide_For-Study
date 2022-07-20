import os
import sys

path = input()
files = os.listdir(path)
for file in files:
    print(file)
