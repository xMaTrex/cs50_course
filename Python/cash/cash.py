from cs50 import get_float


def main():
    while True:
        change_owed = get_float("Change owed: ")
        if change_owed > 0:
            break

    cents = change_owed * 100

    quarters = calc_quarters(cents)
    cents = cents - quarters * 25

    dimes = calc_dimes(cents)
    cents = cents - dimes * 10

    nickels = calc_nickels(cents)
    cents = cents - nickels * 5

    pennies = calc_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickels + pennies

    print(coins)


def calc_quarters(cents):
    quarters = 0
    while cents >= 25:
        cents -= 25
        quarters += 1
    return quarters


def calc_dimes(cents):
    dimes = 0
    while cents >= 10:
        cents -= 10
        dimes += 1
    return dimes


def calc_nickels(cents):
    nickels = 0
    while cents >= 5:
        cents -= 5
        nickels += 1
    return nickels


def calc_pennies(cents):
    pennies = 0
    while cents >= 1:
        cents -= 1
        pennies += 1
    return pennies


main()