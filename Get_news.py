import newspaper

url='https://news.cctv.com/tech'
news=newspaper.build(url, language='zh')
for article in news.articles:
    print(article.url)

len(news.articles) 