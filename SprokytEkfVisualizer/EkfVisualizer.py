from EkfLoader import EkfLoader

filename = 'E:\Sprokyt\Projects\SprokytEKF\data\sensor_data_out.txt'
ekfLoader = EkfLoader()


def main():
    ekfLoader.load_file(filename)
    ekfLoader.plot_ekf()


if __name__== "__main__":
    main()
