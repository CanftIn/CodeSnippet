from keras.datasets import imdb

(train_data, train_labels), (test_data, test_labels) = imdb.load_data(
  num_words=10000)

print(train_data)