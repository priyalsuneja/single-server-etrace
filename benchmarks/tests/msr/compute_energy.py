f = open("mm_signal_out")
f_output = open(".temp_output/output.txt")
# f_elf = open(".temp_output/elf.txt")

# get main function address
main_addr = f_output.readlines()[1].split()[1]
print(main_addr)

# get list of energies from file
energies = []
addresses = []
prev_energy = 0.0
with open(".temp_output/functions.txt", "w") as a:
    for i, line in enumerate(f.readlines()):
        if (i%2 == 0):
            if (i == 0):
                energies.append(0.0)
                prev_energy = float(line)
            else:
                energies.append(float(line) - prev_energy)
        else:
            addresses.append("0x" + line.split()[0])
            a.write("0x" + line.split()[0])


'''
withAddr2lineContext(Path("build/mm_signal")) as c:
    # get function for each address
    for i, addr in enumerate(addresses):
        func = c.get_function(addr)
        if (functions_to_energy.has_key(func):
            functions_to_energy[addr] = functions_to_energy[addr] + energies[i]
        else:
            functions_to_energy[addr] = energies[i]
'''

