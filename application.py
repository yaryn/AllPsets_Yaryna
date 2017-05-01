from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

from datetime import datetime,timedelta
import time

# configure application
app = Flask(__name__)  # Flask is a microframework for Python based on Werkzeug, Jinja 2 and good intentions

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/") # http://flask.pocoo.org/
@login_required
def index():
    
    users_stocks=db.execute("SELECT symbol FROM purchases WHERE us_id=:id GROUP BY symbol", id=session["user_id"])
    rows=db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
    
    total_all=0
    
    if not users_stocks:
        return render_template("index.html", cash=usd(rows[0]["cash"]), total_all=usd(rows[0]["cash"]))

    else:    
        stocks=[]
    
        for u_s in users_stocks:
            symbol_new=lookup(u_s["symbol"])
            
            count_all = db.execute("SELECT SUM(count) FROM purchases WHERE us_id=:id AND symbol = :symbol", id=session["user_id"], symbol=symbol_new["symbol"])
            p_old = db.execute("SELECT price FROM purchases WHERE us_id=:id AND symbol = :symbol", id=session["user_id"], symbol=symbol_new["symbol"])
            if count_all[0]["SUM(count)"]!=0:
                new_data={}
            
                new_data["symbol"]=symbol_new["symbol"]    
                new_data["name"]=symbol_new["name"]
                new_data["price_old"]=p_old[0]["price"]
                new_data["price"]=symbol_new["price"]
                new_data["count"]=count_all[0]["SUM(count)"]
                new_data["total"]=new_data["price"]*new_data["count"]
                #new_data["total_all"]=total_all+total
                stocks.append(new_data)
        
        for i in range(len(stocks)):
            total_all += stocks[i]["total"]
        total_all += rows[0]["cash"]
        
        for i in range(len(stocks)):
            stocks[i]["price"] = usd(stocks[i]["price"])
            stocks[i]["total"] = usd(stocks[i]["total"])   

    # request.form["name"]
    return render_template("index.html", stocks=stocks, cash=usd(rows[0]["cash"]), total_all=usd(total_all))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method=="POST":
## Require that a user input a stock’s symbol. 
## Render an apology if the input is blank or the symbol does not exist 
## (as per the return value of lookup).
#
## Odds are you’ll want to call lookup to look up a stock’s current price.
        symbol=lookup(request.form.get("AAPL"))
        if not symbol:
            return apology("not found, try other symbol")
## Require that a user input a number of shares.
## Render an apology if the input is not a positive integer.
        count=int(request.form.get("count"))
        if not count or count<=0:
            return apology("enter count of stocks")
            
        
## SELECT how much cash the user currently has in users
        rest_of_money=db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])
        rest_of_money=int(rest_of_money[0]["cash"])
        rest=symbol["price"]*count
        # Working with timestamps: http://www.idiotinside.com/2015/03/14/working-with-date-and-time-python-892/
        current_timestamp = time.time()
        datetime_ts = datetime.fromtimestamp(current_timestamp).strftime('%Y-%m-%d %H:%M:%S')
        if rest<rest_of_money:
            resulta = db.execute("INSERT INTO purchases (symbol, stocks_name, count, price, us_id, date) VALUES (:symbol, :stocks_name, :count, :price, :us_id, :date)", symbol=symbol["symbol"], stocks_name = symbol["name"], count=count, price=symbol["price"], us_id=session["user_id"], date=datetime_ts)
            if resulta:
                db.execute("UPDATE users SET cash=cash-:price_all WHERE id=:user_id", price_all=rest, user_id=session["user_id"])
                return redirect(url_for("index"))
        else:
            apology("you can not to buy the number of shares at the current price")
    
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    rows=db.execute("SELECT symbol, count, stocks_name, price, date FROM purchases WHERE us_id=:id", id=session["user_id"])
    for i in rows:
        i["price"]=usd(i["price"])
    
    return render_template("history.html", stocks=rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")
        
# to change their passwords - passwordchange
@app.route("/passwordchange", methods=["GET", "POST"])
def passwordchange():
    """To change passwords."""

    # forget any user_id
    #session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password")
        
        # ensure password was submitted
        if not request.form.get("passwordnew"):
            return apology("must provide new password")
            
        # ensure password was submitted
        if not request.form.get("passwordnew2"):
            return apology("must provide new password 2")
            
        if session["user_id"]:
            # query database for username 
            rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
            # ensure username exists and password is correct
            if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
                return apology("invalid old password")
                
            password=request.form.get("passwordnew")
            if password==request.form.get("passwordnew2"):
                hash=pwd_context.encrypt(password)
                db.execute("UPDATE users SET hash=:hash", hash=hash)
            else:
                return apology("must new password not = new password2")
    
            # remember which user has logged in
            #session["user_id"] = rows[0]["id"]
    
            # redirect user to home page
            return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("passwordchange.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method=="POST":
        quote=lookup(request.form.get("AAPL"))
        if not quote:
            return apology("not found")
        else:
            quote["price"] = usd(quote["price"])
            return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        
        # ensure password was submitted
        elif not request.form.get("password_2"):
            return apology("must provide password_2")
            
        # ensure password was == password_2
        elif  request.form.get("password") != request.form.get("password_2"):
            return apology("password 1 not equal password 2")
        
        # query database for username
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=pwd_context.encrypt(request.form.get("password")))
        # ensure username exists and password is correct
        if not result:
            return apology("you must provide different username")
        else:
            # remember which user has logged in
            session["user_id"] = result
            # redirect user to home page
            return redirect(url_for("index"))
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method=="POST":
        symbol=lookup(request.form.get("AAPL"))
        if not symbol:
            return apology("enter other symbol")
            
        shares=int(request.form.get("count"))
        if not shares or shares<0:
            return apology("enter number of shares which you can to sell")
            
        #rows=db.execute("SELECT symbol, stocks_name, count, price FROM purchases WHERE us_id=:id AND symbol=:symbol", id=session["user_id"], symbol=symbol["symbol"])
        rows=db.execute("SELECT SUM(count) FROM purchases WHERE us_id=:id AND symbol=:symbol", id=session["user_id"], symbol=symbol["symbol"])
        if not rows[0]["SUM(count)"]:
            return apology("this stok are not your")
        
        #minus=rows[0]["count"]*rows[0]["price"]
        plus=symbol["price"]*shares
            
        if rows[0]["SUM(count)"]<shares:
            return apology("you want to sey very many stocks")
        else:
            db.execute("UPDATE users SET cash=cash+:price_all WHERE id=:user_id", price_all=plus, user_id=session["user_id"])
            #db.execute("UPDATE purchases SET count=count-:m WHERE us_id = :user_id AND symbol=:symbol", m=shares, user_id=session["user_id"], symbol=symbol["symbol"])
            current_timestamp = time.time()
            datetime_ts = datetime.fromtimestamp(current_timestamp).strftime('%Y-%m-%d %H:%M:%S')
            db.execute("INSERT INTO purchases (symbol, stocks_name, count, price, us_id, date) VALUES (:symbol, :stocks_name, :count, :price, :us_id, :date)", symbol=symbol["symbol"], stocks_name = symbol["name"], count=-shares, price=symbol["price"], us_id=session["user_id"], date=datetime_ts)
            
           # rows_del=db.execute("SELECT symbol, count FROM purchases WHERE us_id=:id AND symbol=:symbol", id=session["user_id"], symbol=symbol["symbol"])
           # if rows_del[0]["count"]==0:
           #     cc=0
           #     db.execute("DELETE FROM purchases WHERE symbol=:symbol AND count=:count", symbol=symbol["symbol"], count=cc)
        return redirect(url_for("index"))
    else:
        return render_template("sell.html")
