from cs50 import get_float

coins = [25, 10, 5, 1]

money = -1
while money < 0:
    money = get_float("Change owed: ")

cents = int(money * 100)

amount = 0
for coin in coins:
    rest = cents % coin
    amount += cents // coin
    cents = rest
print(amount)