import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positive = set()
        self.negative = set()
        # TODO
        file = open(positives, "r") # positive-words
        for line in file:
            if not line.startswith(';'):
                self.positive.add(line.rstrip("\n"))
        file.close()
        
        file = open(negatives, "r")
        for line in file:
            if not line.startswith(';'):
                self.negative.add(line.rstrip("\n"))
        file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text) # tweet
        
        # TODO
        for i in tokens:
            if i.lower() in self.positive: # https://docs.python.org/3/library/stdtypes.html#str.lower
                score = score + 1
            elif i.lower() in self.negative:
                score = score - 1
            else:
                score = score
        return score