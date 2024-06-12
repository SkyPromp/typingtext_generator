# Typingtest Generators
This project will be able to generate multiple typing tests depending on the parameters.

## Words format
The words in the file, e.g. words.txt should be separated by newlines
## Compile
gcc -o run.exe filename
## words_numbers.c
examples  
  
run.exe
- File: words.txt
- Minimum number length: 2
- Maximum number length: 5
- Numbers to words ratio: 0.3
- Amount of words + numbers: 25

run.exe data.txt
- File: data.txt
- Minimum number length: 2
- Maximum number length: 5
- Numbers to words ratio: 0.3
- Amount of words + numbers: 25

run.exe 1 3 0.5 10
- File: words.txt
- Minimum number length: 1
- Maximum number length: 3
- Numbers to words ratio: 0.5
- Amount of words + numbers: 10

run.exe data.txt 1 3 0.5 10
- File: data.txt
- Minimum number length: 1
- Maximum number length: 3
- Numbers to words ratio: 0.5
- Amount of words + numbers: 10

