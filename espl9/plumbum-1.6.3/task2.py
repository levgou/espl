"""
2.a Calculate the grades again, but this time without reducing points for the most frequent error code.
    Print the results in the following format: <student name>: <grade> => <grade after factor>.
    In addition, print the average before and after the factor.

2.b Print the list of students who failed before the factor together
    with their original grade and their grade after the factor.

"""
from task1 import most_freq_err_and_occurrence, calc_grade_for_student

FMT = '{name}: {orig} => {new}'


def calc_grades_with_factor(input_file, _err_code_weights_file):
    most_freq_err = most_freq_err_and_occurrence(input_file)[0]
    s_grades = calc_grade_for_student(input_file, _err_code_weights_file, most_freq_err)
    return s_grades


def print_grades_with_factor(input_file, _err_code_weights_file):
    before_factor_dict = calc_grade_for_student(input_file, _err_code_weights_file)
    after_factor_dict = calc_grades_with_factor(input_file, _err_code_weights_file)

    for student, grade in after_factor_dict.items():
        print(FMT.format(name=student, orig=before_factor_dict[student], new=grade))

    old_avg = sum(before_factor_dict.values()) / len(before_factor_dict.values())
    new_avg = sum(after_factor_dict.values()) / len(after_factor_dict.values())
    print ('Old Avg: [{}], new: [{}]'.format(old_avg, new_avg))


def print_fail_before_factor(input_file, _err_code_weights_file):
    before_factor_dict = calc_grade_for_student(input_file, _err_code_weights_file)
    after_factor_dict = calc_grades_with_factor(input_file, _err_code_weights_file)

    for student, old_grade in before_factor_dict.items():
        if old_grade >= 56:
            continue

        print('{}, old:[{}], new:[{}]'.format(student, old_grade, after_factor_dict[student]))


if __name__ == '__main__':
    file_name = 'lab10_grades.txt'
    err_code_weights_file = 'error-codes.txt'

    # print(calc_grades_with_factor(file_name, err_code_weights_file))
    print_grades_with_factor(file_name, err_code_weights_file)
    print("#" * 30)
    print_fail_before_factor(file_name, err_code_weights_file)
