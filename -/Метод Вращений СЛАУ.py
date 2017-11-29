import numpy as np

matrix = np.matrix('1.0 2 3 8; 3 1 1 3; 2 3 1 5')
n = matrix.shape[0]
m = matrix.shape[1]
for k in range(0, m - 2):
    tMatrix = matrix[:, np.array(range(k, m))][np.array(range(k, n)), :]
    for i in range(0, tMatrix.shape[0] - 1):
        c = tMatrix[0, 0] / (np.sqrt(tMatrix[0, 0] ** 2 + tMatrix[1 + i, 0] ** 2))
        s = tMatrix[1 + i, 0] / (np.sqrt(tMatrix[0, 0] ** 2 + tMatrix[1 + i, 0] ** 2))
        t1 = tMatrix[0] * c + tMatrix[1 + i] * s
        t2 = tMatrix[0] * (-s) + tMatrix[1 + i] * c
        tMatrix[0], tMatrix[1 + i] = t1, t2
        for j in range(k, n):
            for z in range(k, m):
                matrix[j, z] = tMatrix[j - k, z - k]
answers = [0] * (n)
for i in range(n - 1, -1, -1):
    answers[i] = (matrix[i, n] - sum([matrix[i, k] * answers[k] for k in range(i + 1, n)])) / matrix[i, i]
print(matrix, '\n', [round(i,4) for i in answers])
