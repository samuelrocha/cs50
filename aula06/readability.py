from cs50 import get_string

plain_text = get_string("Text: ")

letters = 0
sentences = 0
for letter in plain_text:
    if letter.isalpha():
        letters += 1
    elif letter in ['?', '.', '!']:
        sentences += 1

words = len(plain_text.split(' '))  

L = letters / words * 100
S = sentences / words * 100
grade = round(0.0588 * L - 0.296 * S - 15.8) 
if grade < 1:
    print("Before Grade 1...")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")