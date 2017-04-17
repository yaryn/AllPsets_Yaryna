from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer

import os
import sys

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets              # count=100
    tweets = helpers.get_user_timeline(screen_name, 100) 
# queries Twitter’s API for a user’s most recent 100 tweets ^.

    # TODO
    # if screen_name can not exist
    if tweets == None:
        return redirect(url_for("index"))
    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzer = Analyzer(positives, negatives) # instantiate analyzer
    
    
    positive, negative, neutral = 0.0, 0.0, 0.0
# classifies each tweet as positive, negative, or neutral
    for i in tweets:
        score = analyzer.analyze(i)
        if score > 0.0:
            positive = positive + 1
        elif score < 0.0:
            negative = negative + 1
        else:
            neutral = neutral + 1
# generates a chart that accurately depicts those sentiments as percentages
# and If a user has tweeted fewer than 100 times, classify as many tweets as exist
    # The method len() returns the number of elements in the list
    count_tweets = len(tweets)
    positive = (positive / count_tweets) * 100
    negative = (negative / count_tweets) * 100
    neutral = (neutral / count_tweets) * 100
    
    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
## https://apps.twitter.com/app/13648556/keys
## export API_KEY=iRchR719VUlKFiHlaohfIo6sX
## export API_SECRET=w7HO9piCd7sN8TCKIUBmzxZiHNu8yHW1co8MceXgHU8CM680Ix
## flask run