#Extract titles from a directory of json files. This is used as test data for tuning the match headlines script. This is a hack, you should probably never need to use this, if you are lucky.

import re

#list the files in the dir.
from os import listdir
from os.path import isfile, join


jsonFilePath = "/home/osboxes/bubbla/data/kaj/tracks/"
jsonFiles = [ f for f in listdir(jsonFilePath) if isfile(join(jsonFilePath,f)) ]
outfile = open("soundcloudHeadlines","w")

#Print it to outfile
for file in jsonFiles:
	f=open(jsonFilePath+file, "r")
	lines=f.read()
	matches=re.findall(r'title\":\"(.+?)\"',lines)
	print matches[0]
	outfile.write("\n"+matches[0])

outfile.close()
