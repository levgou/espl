from task1 import calc_grade_for_student, show_histogram


if __name__ == '__main__':
    
    file_name = 'lab10_grades.txt'
    freq_output_file = 'errorcodes.stats '
    grades_output_file = 'final_grades'
    err_code_weights_file = 'error-codes.txt'

    grades_dict = calc_grade_for_student(file_name, err_code_weights_file)

    show_histogram(grades_dict)