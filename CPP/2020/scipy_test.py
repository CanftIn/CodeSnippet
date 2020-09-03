from scipy.interpolate import griddata
import numpy as np

#最邻近重采样二维数组
def resize_image(data):
    points = np.transpose(np.where(data))
    values = data.flatten()
    row,col = data.shape
    grid_x, grid_y = np.mgrid[0:row-1:row*2j,0:col-1:col*2j]
    return griddata(points,values,(grid_x, grid_y),method = 'nearest')

a = np.arange(1,7).reshape(2,3)
print(resize_image(a))