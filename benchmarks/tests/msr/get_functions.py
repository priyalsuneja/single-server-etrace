f = open(".temp_output/translated.txt")

with open(".temp_output/functions.txt", "w") as a:
    for i, line in enumerate(f.readlines()):
        if (i%2 == 0):
            a.write(line);

