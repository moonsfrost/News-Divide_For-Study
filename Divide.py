import thulac
import sys

input=sys.argv[1]
output=sys.argv[2]
thu1=thulac.thulac(seg_only=True) 
thu1.cut_f(input,output) 