# Multi-thread searching in file

Написать программу mtfind, производящую поиск подстроки в текстовом файле по маске с использованием многопоточности.

Вывод программы должен быть в следующем формате:
- На первой строке - количество найденных вхождений. 
- Далее информация о каждом вхождении, каждое на отдельной строке, через пробел: номер строки, позиция в строке, само найденное вхождение.

Дополнения:
- В текстовом файле кодировка только 7-bit ASCII.
- Поиск с учетом регистра.
- Каждое вхождение может быть только на одной строке. Маска не может содержать символа перевода строки.

ПРИМЕР
Файл input.txt:
1  I've paid my dues
2  Time after time.
3  I've done my sentence
4  But committed no crime.
5  And bad mistakes ?
6  I've made a few.
7  I've had my share of sand kicked in my face
8  But I've come through.
  
Запуск программы: mtfind --path input.txt --pattern .ad
Ожидаемый результат:
3
5 4 bad
6 5 mad
7 5 had 
