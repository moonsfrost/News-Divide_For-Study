from newspaper import Article
import sys

Url = sys.argv[1]
path = sys.argv[2]
file = open(path,'w')

news = Article(Url,language='zh')
try :
    news.download()
    news.parse()
    file.write(news.title)
    file.write('\n')
    file.write(news.text)
except :
    file.write('$')