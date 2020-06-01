import re

def main():
    """Main entry point of the application"""
    sentence = input('Text: ')
    print_grade_value(coleman_liau_index(sentence))

def count_total_letters(value):
    """Count how many alphanumeric characters are in the string"""

    regex = r'([a-zA-Z])'
    return len(re.findall(regex, value))


def count_total_words(value):
    """Count how many words are in the sentence"""

    regex = r"(?=\S*['-])([a-zA-Z'-]+)|\w+"
    return len(re.findall(regex, value))

def count_total_sentences(value):
    """Count how many words are in the sentence"""

    regex = r"[A-Za-z,;'s]+[.?!]"
    return len(re.findall(regex, value))

def get_average(one, two):
    return one / two * 100.0

def coleman_liau_index(value):
    """Calculate the reading level of a sentence using the Coleman-liau index"""
    average_letters = get_average(count_total_letters(value), count_total_words(value))
    average_sentences = get_average(count_total_sentences(value), count_total_words(value))
    return round(0.0588 * average_letters - 0.296 * average_sentences - 15.8)


def print_grade_value(value):
    """print formatter grade value for coleman liau index"""
    if value < 1:
        print('Before Grade 1.')
    elif value > 16:
        print('Grade 16+')
    else:
        print(f'Grade {value}')


# def run_tests():
#     list_of_strings = [
#         "One fish. Two fish. Red fish. Blue fish.",
#         "Would you like them here or there? I would not like them here or there. I would not like them anywhere.",
#         "Congratulations! Today is your day. You're off to Great Places! You're off and away!",
#         "Harry Potter was a highly unusual boy in many ways. For one thing, he hated the summer holidays more than any other time of year. For another, he really wanted to do his homework, but was forced to do it in secret, in the dead of the night. And he also happened to be a wizard.",
#         "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.",
#         "Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, 'and what is the use of a book,' thought Alice 'without pictures or conversation?'",
#         "When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.",
#         "There are more things in Heaven and Earth, Horatio, than are dreamt of in your philosophy.",
#         "It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.",
#         "A large class of computational problems involve the determination of properties of graphs, digraphs, integers, arrays of integers, finite families of finite sets, boolean formulas and elements of other countable domains."
#     ]

#     for test in list_of_strings:
#         print_grade_value(coleman_liau_index(test))


# run_tests()
main()