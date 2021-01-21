import matplotlib.pyplot as plt
import sys

# call example:
# python3 plot.py plik.txt -a
# draws f(x) = time(a.length)

if len(sys.argv) != 3 or (sys.argv[2] != '-a' and sys.argv[2] != '-b'):
    print("Program should be called as:")
    print("<pyton executable> plot.py <filename> -<string to watch to>")
    print("String to watch to should be 'a' or 'b'.")
    quit()

filename = sys.argv[1]
variable_string = sys.argv[2][1]

with open(filename) as file:
    print("Reading file... " + filename)

    testcases = [[], [], []]
    for line in file:
        numbers = []
        i = 0
        for char in line.strip().split():
            testcases[i].append(float(char))
            i = i + 1

variable_string_index = 0 if variable_string == 'a' else 1
plt.plot(testcases[2], testcases[variable_string_index])
plt.show()
