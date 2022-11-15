import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    rows = db.execute(
        "SELECT symbol, sum(shares) FROM transactions WHERE user_id= ? GROUP BY symbol HAVING sum(shares) != 0", session["user_id"])

    stocks = []
    total = 0
    for i, row in enumerate(rows):
        stocks.append({})
        share = lookup(row['symbol'])
        stocks[i]['symbol'] = share['symbol']
        stocks[i]['name'] = share['name']
        stocks[i]['shares'] = row['sum(shares)']
        stocks[i]['price'] = share['price']
        stocks[i]['total'] = int(row['sum(shares)']) * float(share['price'])
        total += stocks[i]['total']
        stocks[i]['total'] = f'{stocks[i]["total"]:.2f}'

    row = db.execute("SELECT cash from users WHERE id = ?", session["user_id"])
    cash = float(row[0]['cash'])
    total += cash
    cash = f'{cash:.2f}'
    total = f'{total:.2f}'

    sold = request.args.get('sold')
    bought = request.args.get('bought')
    change = request.args.get('change')

    return render_template("index.html", stocks=stocks, total=total, cash=cash, sold=sold, bought=bought, change=change)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        share = lookup(request.form.get("symbol"))
        amount = request.form.get("shares")

        if not share:
            return apology("share not found")
        if not amount or not amount.isdigit():
            return apology("unreported amount")

        total_payable = float(share['price']) * int(amount)
        row = db.execute("SELECT cash FROM users WHERE id = ?",
                         session["user_id"])

        if row[0]["cash"] < total_payable:
            return apology("poor you have no money")

        balance = row[0]["cash"] - total_payable
        transacted = datetime.now()
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   balance, session["user_id"])

        db.execute("INSERT INTO transactions (symbol, shares, price, transacted, user_id) VALUES (?, ?, ?, ?, ?)",
                   share["symbol"], amount, share["price"], transacted, session["user_id"])
        return redirect("/?bought=True")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", stocks=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        share = lookup(request.form.get("symbol"))
        if share:
            phrase = f"A share of {share['name']} ({share['symbol']}) costs ${share['price']:.2f}."
        else:
            return apology("share not found")
        return render_template("quote.html", phrase=phrase)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        retype_password = request.form.get("confirmation")

        # Ensure username was submitted
        if not retype_password or not password or not username:
            return apology("fill in all fields")

        if password != retype_password:
            return apology("different passwords")

        row = db.execute("SELECT id FROM users WHERE username = ?", username)

        if len(row) == 1:
            return apology("The user already exists")

        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                        username, generate_password_hash(password))
        session["user_id"] = id

        return redirect("/")
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("inform the symbol")

        if not shares:
            return apology("inform the number of shares")

        row = db.execute(
            "SELECT symbol, sum(shares) FROM transactions WHERE symbol = ? AND user_id = ? GROUP BY symbol", symbol, session["user_id"])

        shares = int(shares)
        if shares > row[0]["sum(shares)"]:
            return apology("insufficient quotas")

        share = lookup(request.form.get("symbol"))
        transacted = datetime.now()

        db.execute("INSERT INTO transactions (symbol, shares, price, transacted, user_id) VALUES (?, ?, ?, ?, ?)",
                   share["symbol"], (shares * -1), share["price"], transacted, session["user_id"])

        row = db.execute("SELECT cash FROM users WHERE id = ?",
                         session["user_id"])
        balance = row[0]["cash"] + (share["price"] * shares)

        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   balance, session["user_id"])

        return redirect("/?sold=True")

    rows = db.execute(
        "SELECT symbol FROM transactions WHERE user_id= ? GROUP BY symbol HAVING sum(shares) != 0", session["user_id"])

    return render_template("sell.html", shares=rows)

@app.route("/config", methods=["GET", "POST"])
@login_required
def config():

    if request.method == "POST":
        
        current = request.form.get('password')
        new = request.form.get('new_password')
        new2 = request.form.get('new_password2')

        if not current:
            return apology("inform the current password")

        if not new:
            return apology("inform the new password")

        if not new == new2:
            return apology("different passwords")

        rows = db.execute('SELECT hash FROM users WHERE id = ?', session['user_id'])
        if not check_password_hash(rows[0]["hash"], current):
            return apology("current password incorrect")

        new = generate_password_hash(new)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new, session['user_id'])
        return redirect('/?change=True')

    return render_template('config.html')


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
