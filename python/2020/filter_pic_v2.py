from PIL import Image
import os
import shutil
import numpy as np

def list_file(file_dir):
  for file in os.listdir(file_dir):
    #file = files.replace(".png", "")
    read_file(file)

def read_file(file):
  img = Image.open("../overlap/" + file)
  width = img.size[0]
  height = img.size[1]
  img_array = np.array(img)
  #print(img_array)
  #print(img_array.shape)

  if np.max((img_array[:,:,0] == 80) * (img_array[:,:,1] == 0) * (img_array[:,:,2] == 0)) == 1:
      print(file)
      shutil.copyfile("../overlap/" + file, "../overlap_filter/" + file)
      os.remove("../overlap/" + file)
      return

list_file("../overlap")