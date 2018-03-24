import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import matplotlib.pyplot as plt


class EkfLoader:
    def __init__(self):
        self.time, self.uwb_x, self.uwb_z, self.dd_x, self.dd_z, self.imu_yaw, self.dd_yaw, self.ekf_x, self.ekf_z,\
            self.ekf_yaw = [], [], [], [], [], [], [], [], [], []
        return

    def load_file(self, filename):
        text_file = open(filename, "r")
        lines = text_file.readlines()

        for line in lines:
            ekf_values = [float(x) for x in line.rstrip('\r\n').split(',')]
            self.time.append(ekf_values[0])
            self.uwb_x.append(ekf_values[1])
            self.dd_x.append(ekf_values[2])
            self.uwb_z.append(ekf_values[3])
            self.dd_z.append(ekf_values[4])
            self.imu_yaw.append(ekf_values[5])
            self.dd_yaw.append(ekf_values[6])
            self.ekf_x.append(ekf_values[7])
            self.ekf_z.append(ekf_values[8])
            self.ekf_yaw.append(ekf_values[9])

        text_file.close()

    def plot_ekf(self):
        mpl.rcParams['legend.fontsize'] = 10

        fig = plt.figure()
        ax = fig.gca(projection='3d')
        y = np.linspace(0, 0, len(self.time))

        ax.plot(self.uwb_x, self.uwb_z, y, label='UWB XZ')
        ax.plot(self.dd_x, self.dd_z, y, label='Differential Drive XZ')
        ax.plot(self.ekf_x, self.ekf_z, y, label='EKF XZ')
        ax.legend()
        plt.show()
