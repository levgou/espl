"""
    1.a Calculate statistics for each error code,
        and output results to a file called errorcodes.stats in the following format: errorcode|frequency.

    1.b Calculate the grade of each student and write the grades to a new file called final_grades
        in the following format: student|grade. To calculate the grades,
        get the max points to reduce for each error-code from error-codes
        (format: error-code\tpoints to reduce, and multiply it by the number after ":"
        in the grades_error-codes file
        (to calculate partial/full reduction). For example,
        if a student has the following error codes:memory:1 and general:0.5, then his/her grade would be 87.5.
"""
from collections import Counter
import matplotlib.pyplot as plt
from pprint import pprint

def get_codes_and_num_from_lines(line):
    split_lines = line.split('\t')
    if len(split_lines) > 1:
        pipe_split = split_lines[1].split('|')
        return [part.split(':') for part in pipe_split if part != '\n']


def get_codes_from_lines(line):
    return [split_line[0] for split_line in get_codes_and_num_from_lines(line)]


def error_code_occurrence_stats(file_path):
    with open(file_path, 'r') as f:
        lines = f.readlines()

    codes = []
    for line in lines:
        codes.extend(get_codes_from_lines(line))

    c = Counter(codes)
    del c['\n']
    return c


def save_error_stats_to_file(input_file, output_file):
    with open(output_file, 'w') as f:
        for err, freq in error_code_occurrence_stats(input_file).items():
            f.write('{}|{}\n'.format(err, freq))


def save_grades_to_file(grades_dict, output_file):
    with open(output_file, 'w') as f:
        for student, grade in grades_dict.items():
            f.write(f'{student}|{grade}\n')


def get_err_weights_from_file(err_weight_file):
    with open(err_weight_file, 'r') as f:
        split_lines = [line.strip().split('\t') for line in f.readlines()]

    return {err_w[0]: float(err_w[1]) for err_w in split_lines}


def calc_grade_for_student(input_file, err_weight_file, ignore_err='NO_ERROR_AT_ALL'):
    weights = get_err_weights_from_file(err_weight_file)

    with open(input_file, 'r') as f:
        lines = f.readlines()

    grades = {}
    for line in lines:
        s_name = line.split('\t')[0]
        errs = get_codes_and_num_from_lines(line)

        grades[s_name] = 100
        for err, score in errs:
            if err == ignore_err:
                continue

            grades[s_name] -= weights[err] * float(score)

    return grades


def show_histogram(grades_dict):

    unique_values = set(grades_dict.values())
    num_bins = len(unique_values)

    plt.hist(grades_dict.values(), num_bins, facecolor='blue', alpha=0.5)

    plt.xlabel('Grade')
    plt.ylabel('#Occur')
    plt.title('Grades histogram')

    plt.show()


def most_freq_err_and_occurrence(input_file):
    err_occurrences = error_code_occurrence_stats(input_file)
    return err_occurrences.most_common()[0]


def print_most_freq_err_stats(input_file, err_weight_file):
    weights = get_err_weights_from_file(err_weight_file)
    err, occurance_count = most_freq_err_and_occurrence(input_file)
    print('Most freq err[{}], freq[{}], weight [{}]'.format(err, occurance_count, weights[err]))

