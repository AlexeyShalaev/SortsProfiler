import os

import matplotlib.pyplot as plt
import numpy as np

BEGIN = 500
END = 4000
STEP = 100


def plot_array(data, save_path=None):
    plt.figure(figsize=(10, 5))
    times = np.arange(BEGIN, END + STEP, STEP)
    for key, value in data.items():
        plt.plot(times, value, label=key)
    plt.xlabel('Array size')
    plt.ylabel('Microseconds')
    plt.legend()

    if save_path:
        plt.savefig(save_path)
        plt.close()
    else:
        plt.show()


def process_files_in_directory(directory_path):
    data = {}
    for filename in os.listdir(directory_path):
        if filename.endswith(".txt"):
            file_path = os.path.join(directory_path, filename)
            title = filename.replace('.txt', '')
            with open(file_path, 'r') as file:  
                for line in file.readlines():
                    values = line.split(':')
                    if len(values) == 2 and values[0] == 'PartiallySortedArray':
                        data[title] = list(map(int, values[1].strip().split()))
    plot_path = os.path.abspath(os.path.join('.', f'PartiallySortedArray.png'))
    plot_array(data, plot_path)


if __name__ == "__main__":
    directory = "Measurements"  # Укажите путь к вашей папке
    process_files_in_directory(directory)
