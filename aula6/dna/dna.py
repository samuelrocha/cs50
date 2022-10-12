import csv
from sys import argv, exit

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

with open(argv[1], 'r') as database:
    reader = csv.DictReader(database)
    people = []
    for line in reader:
        people.append(line)

with open(argv[2], 'r') as sequence:
    reader = sequence.readline()
    nucleotideos = {}
    for nucleotideo in people[0]:
        if nucleotideo == 'name':
            continue
        nucleotideos[nucleotideo] = 0

    length = len(reader)

    for shield in nucleotideos:
        i = count = 0
        length_shield = len(shield)
        sequence = False
        while i < length:
            if reader[i:i+length_shield] in shield:
                if sequence:
                    count += 1
                else:
                    count = 1
                if count > nucleotideos[shield]:
                    nucleotideos[shield] = count
                sequence = True
                i += length_shield - 1
            else:
                sequence = False
            i += 1

for person in people:
    for shield in nucleotideos:
        nucleotideos[shield] = str(nucleotideos[shield])
    nucleotideos['name'] = person['name']
    if nucleotideos == person:
        print(person['name'])
        exit()

print('No match')
exit()
