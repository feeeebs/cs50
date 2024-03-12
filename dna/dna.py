import csv
import sys


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Command line must include a csv file and text file")
        sys.exit(1)

    # Read database file into a variable
    with open(sys.argv[1], "r") as file:
        dna_reader = csv.DictReader(file)
        dna_database = []
        for row in dna_reader:
            dna_database.append(dict(row))

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        dna_sequence = file.read()

    # Find longest match of each STR in DNA sequence
    dna_subsequences = []

    for key in dna_database[0].keys():
        dna_subsequences.append(key)
    dna_subsequences.pop(0)

    # store longest match for each dna subsequence
    matches = []
    # run longest_match for each dna subsequence
    for i in range(len(dna_subsequences)):
        matches.append(str(longest_match(dna_sequence, dna_subsequences[i])))

    # Check database for matching profiles
    for i in range(len(dna_database)):
        # check dna_database[i] for each sequence
        index_of_match = 0
        value_to_check = dna_database[i].get(dna_subsequences[index_of_match])
        while value_to_check == matches[index_of_match]:
            index_of_match += 1
            if index_of_match == len(dna_subsequences):
                print(f"{dna_database[i].get('name')}")
                return
            value_to_check = dna_database[i].get(dna_subsequences[index_of_match])

    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
