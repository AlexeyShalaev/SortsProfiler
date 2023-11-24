import os

import matplotlib.pyplot as plt
import numpy as np

BEGIN = 500
END = 4000
STEP = 100


def plot_array(data, title, save_path=None):
    plt.figure(figsize=(10, 5))
    times = np.arange(BEGIN, END + STEP, STEP)
    for key, value in data.items():
        plt.plot(times, value, label=key)
    plt.title(title)
    plt.xlabel('Array size')
    plt.ylabel('Microseconds')
    plt.legend()

    if save_path:
        plt.savefig(save_path)
        plt.close()
    else:
        plt.show()


def process_files_in_directory(directory_path):
    for filename in os.listdir(directory_path):
        if filename.endswith(".txt"):
            file_path = os.path.join(directory_path, filename)
            with open(file_path, 'r') as file:
                data = {}
                for line in file.readlines():
                    values = line.split(':')
                    if len(values) == 2:
                        data[values[0]] = list(map(int, values[1].strip().split()))
            title = filename.replace('.txt', '')
            plot_path = os.path.abspath(os.path.join('Graphics', f'{title}.png'))
            plot_array(data, title, plot_path)


if __name__ == "__main__":
    directory = "Measurements"  # Укажите путь к вашей папке
    process_files_in_directory(directory)
