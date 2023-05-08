f = open("mm_signal_out")
f_output = open(".temp_output/output.txt")
f_elf = open(".temp_output/offset.txt")

# get main function address
main_addr = int(f_output.readlines()[1].split()[1], 16)
print("main " + str(main_addr))

# get main virtual offset
main_offset = int(f_elf.readlines()[0].split()[0], 16)
print("offset " + str(main_offset))

program_offset = main_addr - main_offset

# get list of energies from file
energies = []
addresses = []
prev_energy = 0.0
total_energy = 0.0
with open(".temp_output/addresses.txt", "w") as a:
    with open(".temp_output/energies.txt", "w") as e:
        for i, line in enumerate(f.readlines()):
            if (i%2 == 0):
                if i==0:
                    e.write(str(0.0) + "\n");
                else:
                    e.write(str(float(line.split()[0]) - prev_energy) + "\n");
                    total_energy += float(line.split()[0]) - prev_energy
                prev_energy = float(line.split()[0])
            else:
                address = "0x" + line.split()[0]
                offset = int(address, 16) - program_offset
                a.write(str(hex(offset)) + "\n")
        e.write(str(total_energy))


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
