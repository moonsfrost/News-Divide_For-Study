from pathlib import Path
from newspaper import Article
import sys

Url = sys.argv[1]
path = sys.argv[2]
file = open(path,'w')

news = Article(Url,lang='zh')
news.download()
news.parse()

file.write(news.title)
file.write('\n')
file.write(news.text)