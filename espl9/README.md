# Lab 9 - Python and Shell Commands
In this lab you are going to use Python and shell commands to parse a CSV file, print some statistics about its content, and calculate the final grades. The file contains error-codes describing errors made by different students and how much to reduce for each errorcode. 
The format of the file is: 
`student\terror_code1:1|error_code2:1|error_code3:0.5...`
 where the number after each error_code is used to give partial reduction. 1 means full reduction. Any number less than 1, means a partial reduction for its relevant error_code.

Example:

    Danny no_README:1|wrong_file_name:1|code_repetition:0.5|no_task2:1 