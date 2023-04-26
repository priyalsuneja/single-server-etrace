energies = open(".temp_output/energies.txt")
functions = open(".temp_output/functions.txt")

functions_to_energies = {}

for line in functions.readlines():
    energy = float(energies.readline().split()[0])
    function = line.split()[0]
    if function not in functions_to_energies:
        functions_to_energies[function] = 0.0
    functions_to_energies[function] += energy

total_energy = float(energies.readline().split()[0])
for function in functions_to_energies:
    functions_to_energies[function] = functions_to_energies[function] / total_energy * 100

print(functions_to_energies)
