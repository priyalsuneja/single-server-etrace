import csv

def get_data():
    f = open('output.txt')
    text = f.readlines()

    energy = text[1].split()
    energy = [(energy[0] + ' ' + energy[1])[0:-1], float(energy[2][0:-1])]

    data = []
    for i in range(5, len(text) - 3):
        row = reverse_and_cast(text[i].split())
        data.append(row)

    return energy, data 

def reverse_and_cast(input):
    return [input[1], int(input[0].replace(',', ''))]

energy, data = get_data()

with open('data.csv', 'w') as f:
    writer = csv.writer(f)

    writer.writerow(['label', 'data'])
    writer.writerow(energy)

    for row in data:
        writer.writerow(row)
