from cs50 import get_string

def reverse(number):
    new_number = []
    length = len(number) - 1
    for i, digit in enumerate(number):
        new_number.append(number[length - i])
    return new_number

def main():
    card_number = get_string("Number: ")
    reverse_number = reverse(card_number)

    result = 0
    for i, digit in enumerate(reverse_number):
        number = int(digit)
        if i % 2 == 1:
            x1 = (number * 2) // 10
            x2 = (number * 2) % 10
            result += x1 + x2
        else:
            result += number
    
    valid = result % 10 == 0
    flag = len(card_number)
    if valid and flag == 15 and card_number[0] == '3' and int(card_number[1]) in [4, 7]:
        print('AMEX')
    elif valid and flag == 16 and card_number[0] == '5' and int(card_number[1]) in list(range(1,6)):
        print('MASTERCARD')
    elif valid and (flag == 16 or flag == 13) and int(card_number[0]) == 4:
        print('VISA')
    else:
        print('INVALID')

main()