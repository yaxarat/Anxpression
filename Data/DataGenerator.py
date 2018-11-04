import random

current = 70
change = 0.013

text_file = open("Output.txt", "w")

for x in range(0, 10000):
    weight = random.uniform(0, 1.5)

    if 0.95 <= weight <= 1.05:
        current += change
        current *= weight
        text_file.write(",%s" % current)
    else:
        current += change
        text_file.write(",%s" % current)

text_file.close()
