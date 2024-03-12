from cs50 import get_string


def main():
    # get input
    user_text = get_string("Text: ")

    # calculate average letters per 100 words
    avg_letters = average_letters_per_words(user_text)

    # calculate average sentences per 100 words
    avg_sentences = average_sentences(user_text)

    # do the index to find the grade
    grade = coleman_liau_index(avg_letters, avg_sentences)

    # print the grade
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def average_letters_per_words(text):
    # count the number of letters in a text
    char_counter = len(text)
    number_of_letters = 0.0
    pointer = 0
    while char_counter > 0:
        if text[pointer].isalpha() == True:
            number_of_letters += 1
            pointer += 1
        else:
            pointer += 1
        char_counter -= 1
        # print(f"number of letters: {number_of_letters}")

    # count the number of words in a text
    length = len(text)
    number_of_words = 1.0
    for i in range(length):
        if text[i].isspace() == True:
            number_of_words += 1
        # print(f"number of words: {number_of_words}")

    # average letters per word * 100
    average_letters = number_of_letters / number_of_words * 100
    # print(f"number of letters: {number_of_letters}")
    # print(f"average letters per 100 words: {average_letters}")

    return average_letters


def average_sentences(text):
    length = len(text)
    number_of_words = 1.0
    for i in range(length):
        if text[i].isspace() == True:
            number_of_words += 1
    # print(f"number of words: {number_of_words}")

    number_of_sentences = 0.0
    for i in range(length):
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            number_of_sentences += 1
    # print(f"number of sentences: {number_of_sentences}")
    avg_sentence = number_of_sentences / number_of_words * 100
    # print(f"average sentences per 100 words: {avg_sentence}")

    return avg_sentence


def coleman_liau_index(average_letters, average_sentences):
    index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8
    index = round(index)

    return int(index)


main()
