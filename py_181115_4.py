import numpy
from numpy import random as rnd

print('Задание 4')

print('Введите количество строк n')
n = int(input())
print('Введите количество столбцов m')
m = int(input())

a = [ [-1] * m  for i in range(n) ]

print('Наберите 1, чтобы заполнить матрицу самостоятельно.')
print('Наберите 2, чтобы заполнить матрицу случайным образом.')

while 42:
    q = int(input())

    if (q == 1):
        for i in range(n):
            for j in range(m):
                print("A[", i, "][", j, "] = ?")
                x = int(input())
                a[i][j] = x
        break

    if (q == 2):
        for i in range(n):
            for j in range(m):
                x = rnd.randint(0, 100)
                a[i][j] = x
        break

print()
print('Матрица:')
print('\n'.join([''.join(['{:5}'.format(item) for item in row])
      for row in a]))



set1 = []
set2 = []
k = int(0)

print()
print('Ответ:')
for k in range(n):
    for i in range(k+1, n):
        for j in range(m):
            if a[k][j] not in set1:
                x = int(a[k][j])
                set1.append(x)

            if a[i][j] not in set2:
                x = int(a[i][j])
                set2.append(x)

        set1.sort()
        set2.sort()

        if (set1 == set2):
            print('Строка ', k, ' похожа на строку ', i, ' ')

        set1 = []
        set2 = []

for k in range(m):
    for i in range(k+1, m):
        for j in range(n):
            if a[j][k] not in set1:
                x = int(a[j][k])
                set1.append(x)

            if a[j][i] not in set2:
                x = int(a[j][i])
                set2.append(x)

        set1.sort()
        set2.sort()

        if (set1 == set2):
            print('Столбец ', k, ' похож на столбец ', i, ' ')

        set1 = []
        set2 = []
