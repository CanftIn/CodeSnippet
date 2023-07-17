from PIL import Image
import os
import shutil

def list_file(file_dir):
  for file in os.listdir(file_dir):
    #file = files.replace(".png", "")
    read_file(file)

def read_file(file):
  img = Image.open("../overlap/" + file)
  width = img.size[0]
  height = img.size[1]
  for i in range(0, width):
    for j in range(0, height):
      data = (img.getpixel((i, j)))
      if (data[0] == 80 and data[1] == 0 and data[2] == 0):
        print(file)
        shutil.copyfile("../overlap/" + file, "../overlap_filter/" + file)
        os.remove("../overlap/" + file)
        return

list_file("../overlap")

