# SortsProfiler

## Генератор тестовых данных & Реализация гибридного алгоритма MERGE+INSERTION SORT

- [array_sorters](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/MeasurementGenerator/array_sorters.h) (Сортировки массивов)
- [array_generators](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/MeasurementGenerator/array_generators.h) (Генератор массивов)
- [main](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/MeasurementGenerator/main.cpp) (Генерация тестовых данных и их сортировка)

## Исходные данные, использованные для построения графиков

Каждый файл состоит из 3 строк (каждая строка имеет вид <название группы>: <массив микросекунд>):
- RandomArray - массивы, которые заполнены случайными значениями в некотором диапазоне.
- RandomReversedSortedArray - массивы, которые отсортированы в обратном порядке по невозрастанию.
- PartiallySortedArray - массивы, которые «почти» отсортированы.

### Dataset
- [MergeSortTimes](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Measurements/MergeSortTimes.txt) - измерения времени работы стандартной реализации алгоритма MERGE SORT
- [MergeSortHybridTimes_5](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Measurements/MergeSortHybridTimes_5.txt) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 5 элементах в массиве)
- [MergeSortHybridTimes_10](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Measurements/MergeSortHybridTimes_10.txt) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 10 элементах в массиве)
- [MergeSortHybridTimes_20](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Measurements/MergeSortHybridTimes_20.txt) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 20 элементах в массиве)
- [MergeSortHybridTimes_50](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Measurements/MergeSortHybridTimes_50.txt) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 50 элементах в массиве)

  
## Генератора графиков
[Visualizer](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Visualizer/main.py)

## Графики

Каждый график состоит из 3 сущностей (каждая отображает время работы сортировки для выбранной сортировки на рахзных видах массивов):
- RandomArray - массивы, которые заполнены случайными значениями в некотором диапазоне.
- RandomReversedSortedArray - массивы, которые отсортированы в обратном порядке по невозрастанию.
- PartiallySortedArray - массивы, которые «почти» отсортированы.

### Dataset
- [MergeSortTimes](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Graphics/MergeSortTimes.png) - измерения времени работы стандартной реализации алгоритма MERGE SORT
- [MergeSortHybridTimes_5](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Graphics/MergeSortHybridTimes_5.png) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 5 элементах в массиве)
- [MergeSortHybridTimes_10](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Graphics/MergeSortHybridTimes_10.png) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 10 элементах в массиве)
- [MergeSortHybridTimes_20](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Graphics/MergeSortHybridTimes_20.png) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 20 элементах в массиве)
- [MergeSortHybridTimes_50](https://github.com/AlexeyShalaev/SortsProfiler/blob/master/Graphics/MergeSortHybridTimes_50.png) - измерения времени работы гибридного алгоритма MERGE+INSERTION SORT (INSERTION SORT вызывается при 50 элементах в массиве)
