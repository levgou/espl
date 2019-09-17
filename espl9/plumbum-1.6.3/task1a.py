from task1 import save_error_stats_to_file

if __name__ == '__main__':
    
    file_name = 'lab10_grades.txt'
    freq_output_file = 'errorcodes.stats '

    save_error_stats_to_file(file_name, freq_output_file)