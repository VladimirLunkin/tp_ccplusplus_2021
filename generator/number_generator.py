from random import randint


file = open("data.txt", "w")

quantity = 100_000_000
max_num = 10_000

file.write(str(quantity) + '\n')

for i in range(quantity):
    file.write(str(randint(-max_num, max_num)) + '\n')

file.close()
