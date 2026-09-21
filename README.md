# Функции калькулятора:
- [ ] ReadNumber
- [ ] RunCalculatorCycle
- [ ] s
- [ ] l
- [ ] + <число>
- [ ] -
- [ ] *
- [ ] /
- [ ] **
- [ ] =
- [ ] : <число>
- [ ] c
- [ ] q

# Тесты
## ReadNumber
### Число
1. Положительное  
   Ввод: 8 =  
   Вывод: 8
2. Ноль  
   Ввод: 0 =  
   Вывод: 0
3. Отрицательное  
   Ввод: -8 =  
   Вывод: -8
4. Плюс перед числом  
   Ввод: +8 =  
   Вывод: 8
### Не число
1. Пустая строка  
   Ввод:  
   Вывод: Error: Numeric operand expected
2. Символ алфавита  
   Ввод: a =  
   Вывод: Error: Numeric operand expected
3. Спецсимвол  
   Ввод: ; =  
   Вывод: Error: Numeric operand expected
4. Символ алфавита и число  
   Ввод: a4 =  
   Вывод: Error: Numeric operand expected
5. Число и символ алфавита  
   Ввод: 4a =  
   Вывод: Error: Numeric operand expected
6. Спецсимвол и число  
   Ввод: ;4 =  
   Вывод: Error: Numeric operand expected
7. Число и спецсимвол  
   Ввод: 4; =  
   Вывод: Error: Numeric operand expected
8. Слово  
   Ввод: четыре =  
   Вывод: Error: Numeric operand expected
9. Минус среди чисел  
   Ввод: 1-4 =  
   Вывод: Error: Numeric operand expected
10. Минус после числа (после минуса должно быть число)  
   Ввод: 14- =  
   Вывод: Error: Numeric operand expected
11. Плюс среди чисел  
    Ввод: 1+4 =  
    Вывод: Error: Numeric operand expected
12. Плюс после числа (после плюса должно быть число)  
    Ввод: 14+ =  
    Вывод: Error: Numeric operand expected
    
