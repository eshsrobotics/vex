import collections
from typing import List
from itertools import accumulate

COLOR_NAMES = ["green", "purple", "orange"]
Shelf = collections.namedtuple("Shelf", COLOR_NAMES)

input_data = [
    Shelf(green=10, purple=0, orange=0),  # Bottom-most
    Shelf(green=0, purple=2, orange=0),
    Shelf(green=0, purple=0, orange=0),
    Shelf(green=1, purple=0, orange=0),
    Shelf(green=0, purple=1, orange=0)   # Uppermost
]


def calculate_score(input_data: List[Shelf]) -> int:
    """
    Calculates the Shelf-Bot score for the given input scenario.

    The lowest shelf will have index 0, and increasing scores for higher
    shelves.
    """
    color_multipliers = [0] * 3

    # TODO: Replace this embarrassing linear search with a more Pythonic
    # approach:
    # https://stackoverflow.com/questions/35410523/pythonic-way-to-find-highest-values-and-indexes-in-list
    for color in range(3):
        index_of_maximum = -1
        for i in range(len(input_data)):
            if input_data[i][color] > 0:
                # print(f"Number of {COLOR_NAMES[color]} cubes at shelf {i+1} ({input_data[i][color]}) is nonzero; setting index_of_maximum to {i}")
                index_of_maximum = i

        color_multipliers[color] = 0 if index_of_maximum == -1 else index_of_maximum + 1

    # print(f"Multipliers: {[COLOR_NAMES[i] + ': ' + str(color_multipliers[i]) for i in range(3)]}")

    # Calculate the total score for all the colors.
    # tup[color] is the number of cubes of a given color o the current shelf.
    # color_multipliers[color] is the scoring factor.
    score = 0
    for color in range(3):
        for i in range(len(input_data)):
            color_count = input_data[i][color]
            shelf_number = i + 1
            score += (color_count * color_multipliers[color] * shelf_number)
        print(f"Total score for {COLOR_NAMES[color]} cubes: {sum([input_data[i][color] * (i+1) * color_multipliers[color] for i in range(len(input_data))])}")

    return score


if __name__ == "__main__":
    print(f"Total score: {calculate_score(input_data)}")
