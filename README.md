# Лабораторная работа № 3-4 "Разработка STL-подобных контейнеров, итераторов и алгоритмов"

Данная лабораторная работа посвящена разработке STL-подобных контейнеров, итераторов и алгоритмов.
Основная цель работы состоит в формировании понимая базовых принципов работы основных компонентов STL (Standard Template Library – библиотека стандартных шаблонов):
контейнеров, итераторов и алгоритмов (рис. 1), речь о которых пойдет в дальнейшем при изучении стандартной библиотеки C++ во втором семестре курса.


*  **Контейнеры** используются для управления коллекциями объектов определенного типа на базе той или иной структуры данных.
Контейнеры реализуются как шаблонные классы.


*  **Алгоритмы** предназначены для обработки элементов коллекций (поиска, копирования из одного контейнера в другой и т.д.).
Алгоритмы реализуются как шаблонные функции.


*  Один и тот же алгоритм должен работать с любым типом контейнера.
Для достижения этой цели служат **итераторы**, которые представляют собой классы, реализующие стандартный интерфейс,
напоминающий интерфейс обычных указателей (`++`, `->`, `*` и т.д.).
В тоже время для каждого контейнера создается свой итератор, знающий, как реализовать эти операции в терминах данного контейнера.

Лабораторная работа состоит из трех частей, в каждой из которой требуется реализовать
соответствующую часть STL – контейнер, итератор и алгоритмы – в соответствии с вариантом.

Полный текст задания доступен [тут](https://vk.com/doc-136542675_594344324).