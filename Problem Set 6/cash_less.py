from cs50 import get_float
from math import floor

def main():
    print(get_change(get_positive_float()))

def get_change(value):
    """Returns total number of coins required to make change from a given value (uses 25, 10, 5, 1)."""

    # store the coin values as they are used multiple times
    quarter_coin = 25
    dime_coin = 10
    nickel_coin = 5

    whole_number = floor(value * 100)

    # At each coin increment we filter out the previous higher value and
    # then check for how many times that coin goes into the remaining amount
    quarters = whole_number // quarter_coin
    dimes = (whole_number % quarter_coin) // dime_coin
    nickels = ((whole_number % quarter_coin) % dime_coin) // nickel_coin

    # Since pennies are a 1 we only need the remainder after filtering out every other coin
    pennies = ((whole_number % quarter_coin) % dime_coin) % nickel_coin

    # return wholeNumber // 25
    return quarters + dimes + nickels + pennies

def get_positive_float():
    """Gets a positive float value input by the user."""
    while True:
        result = get_float("Change owed: ")

        # Ensures the user enters a positive value
        if result > 0:
            break;

    return result

main()