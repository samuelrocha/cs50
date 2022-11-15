import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        name = request.form.get('name')
        day = request.form.get("day")
        month = request.form.get("month")

        if not day.isnumeric() or not month.isnumeric() or not name:
            return redirect("/?error=invalid")

        day = int(day)
        month = int(month)

        if month > 12 or month < 1 or day > 31 or day < 1:
            return redirect("/?error=True")

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/?success=True")

    else:

        rows = db.execute("SELECT name, day, month FROM birthdays")
        error = request.args.get("error")
        success = request.args.get("success")

        return render_template("index.html", birthdays=rows, error=error, success=success)


