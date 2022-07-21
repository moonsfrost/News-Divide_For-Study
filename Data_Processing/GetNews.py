from newspaper import Article
import sys

Url = sys.argv[1]
path = sys.argv[2]

news = Article(Url,language='zh')
news.download()
news.parse()

file = open(path,'w')
file.write(news.title)
file.write('\n')
file.write(news.text)