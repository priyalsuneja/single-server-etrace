f = open(".temp_output/elf.txt")
lines = f.readlines()
offset = ""
for line in lines:
    if len(line.split()) == 8:
        if line.split()[7] == "main":
            offset = line.split()[1]
            print("found main")
            break

# write offset to a text file
with open(".temp_output/offset.txt", "w") as a:
    a.write("0x" + offset)