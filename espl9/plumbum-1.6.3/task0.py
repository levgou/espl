from plumbum import local
from collections import Counter

cat = local['cat']
sed = local['sed']
awk = local['awk']
wc = local['wc']
sort = local['sort']
uniq = local['uniq']


def names(file_path):
    regex = r's/\([a-Z]*\)[\t].*/\1/g'
    cmd = cat[file_path] | sed[regex]
    return cmd()


def num_students(file_path):
    regex = r's/\([a-Z]*\)[\t].*/\1/g'
    cmd = cat[file_path] | sed[regex] | wc['-w']
    return cmd()


def number_error_codes(file_path):
    sed1 = sed[r's/[a-Z]*[\t]\(.*\)/\1/g']
    sed2 = sed[r's/[|]/\n/g']
    sed3 = sed[r's/[:].*//g']

    cmd = cat[file_path] | sed1 | sed2 | sed3 | sort | uniq | awk['NF'] | wc['-l']
    return cmd()


def error_code_occurrence_stats(file_path):
    sed1 = sed[r's/[a-Z]*[\t]\(.*\)/\1/g']
    sed2 = sed[r's/[|]/\n/g']
    sed3 = sed[r's/[:].*//g']

    cmd = cat[file_path] | sed1 | sed2 | sed3 | awk['NF'] | sort | uniq['-c']
    return cmd()


if __name__ == '__main__':
    file_name = 'lab10_grades.txt'
    print(names(file_name))
    print(f'num_students: {num_students(file_name)}')
    print(error_code_occurrence_stats(file_name))
    print(f'number_error_codes: {number_error_codes(file_name)}')
