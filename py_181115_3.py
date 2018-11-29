print( "Задание 3" )
print( "Введите размер квадратной матрицы" )
n = int( input() )

a = [ [-1] * n  for i in range(n) ]

i = int(1)
j = int(0)
k = int(0)
p = n // 2



for k in range(1, p+1, 1):
    for j in range(k-1, n-k+1, 1):
        a[k-1][j] = i
        i += 1
    for j in range(k, n-k+1, 1):
        a[j][n-k] = i
        i += 1
    for j in range(n-k-1, k-2, -1):
        a[n-k][j] = i
        i += 1
    for j in range(n-k-1, k-1, -1):
        a[j][k-1] = i
        i += 1

if (n % 2 == 1):
    a[p][p] = n*n

print('\n'.join([''.join(['{:5}'.format(item) for item in row])
      for row in a]))
