from cs50 import get_string


def main():
    # user input
    text = get_string("Text: ")


    # split into words
    words = text.split()


    # word count
    word_count = len(words)


    # letter count
    letter_count = 0
    for char in text:
        if char.isalpha():
            letter_count += 1


    # sentence count -> . ! ?
    sentence_count = 0
    for char in text:
        if char == "." or char == "!" or char == "?":
            sentence_count += 1

    # cl index
    let = letter_count / word_count * 100
    sen = sentence_count / word_count * 100
    cl_index = 0.0588 * let - 0.296 * sen - 15.8
    print(cl_index)
    if cl_index >= 16:
        print("Grade 16+")
    elif cl_index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(cl_index)}")


main()