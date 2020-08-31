from keras.datasets import mnist
import matplotlib.pyplot as plt
import numpy as np
'''
(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

print(train_images.shape)
print(train_images.ndim)
print(train_images.dtype)

digit = train_images[4]
#plt.imshow(digit, cmap=plt.cm.binary)
#plt.show()

my_slice = train_images[10:100]
print(my_slice.shape)

my_slice = train_images[:, 14:, 14:]
print(my_slice.shape)
'''

def naive_vector_dot(x, y):
  assert len(x, shape) == 1
  assert len(y, shape) == 1
  assert x.shape[0] == y.shape[0]

  z = 0.
  for i in range(x.shape[0]):
    z += x[i] * y[i]
  return z

def naive_matrix_vector_dot(x, y):
  assert len(x.shape) == 2
  assert len(y.shape) == 1
  assert x.shape[1] == y.shape[0]

  z = np.zeros(x.shape[0])
  for i in range(x.shape[0]):
    for j in range(x.shape[1]):
      z[i] += x[i, j] * y[j]
  return z

if __name__ == "__main__":
    x = np.array([[5, 78, 2, 34, 0],
                  [6, 79, 3, 35, 1],
                  [7, 80, 4, 36, 2]])
    y = np.array([12, 3, 6, 14, 7])
    z = naive_matrix_vector_dot(x, y)
    print(z)