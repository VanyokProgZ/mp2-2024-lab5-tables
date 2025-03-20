# ЛР 5. Таблицы

__Цель работы:__ 
Разработать программу, которая предоставляет возможность хранить данные в таблицах 4-х типов:

1)Таблицы на массивах (неупорядоченный массив и отсортированный массив)

2)Упорядоченная таблица (сбалансированное бинарное дерево поиска)

3)Хэш-таблица

В качестве данных использовать полиномы из лабораторной работы 4. Для осуществления арифметических выражениий можно используется код из лабораторной работы 3.


__Особенности реализации:__

1. Работа происходит сразу с таблицами всех типов.
1. Пользователь может положить в таблицу свой полином, с заданием ему некоторого наименования (ключа).
1. Пользователь может запросить (найти в/извлечь из) таблицы полином с заданным наименованием.
1. В ходе выполнения программы у пользователя должна оставаться возможность производить операции с полиномами (в виде арифметических выражений), а так же размещать полученный результат в таблицу.
1. Во время работы программы происходит логирования количества произведенных операций. Пример:
Пользователь ввел свой полином и запросил положить его в таблица, программа в ответ выводит на экран или в файл, какое действие произошло и сколько операций потребовалось на нее у разных типов таблиц. Аналогично с поиском и извлечением.
