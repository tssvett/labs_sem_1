def correct_input(type_=int):  # Функция, определяющая корректность ввода на тип
    x = None
    incorrect_input = True  # Флаг который будем использовать в цикле

    while incorrect_input:  # Цикл с флагом заданным раннее
        try:
            x = type_(input())  # Вводим х, если тип соответсвует заданному в функции, то флаг false
            if x <= 0 or x == ' ':
                incorrect_input = True
                print('Error! Enter a correct positive integer: ')
            elif x == 196:
                incorrect_input = True
                print('Sorry, 196 is very problem number! Enter another correct positive number: ')
            else:
                incorrect_input = False
        except ValueError:  # Если тип не соответствует, выводим ошибку
            print('Error! Enter a correct positive  integer: ')
    return x  # Функция возвращает уже корректный х, который будем использовать далее


def input_number():  # Вводим корректный икс
    print('Enter a positive integer number: ')
    number = correct_input()
    return number


def reverse_number(number):  # Функция переворачивающая число
    array = []
    while number > 0:
        last_digit = number % 10  # Берем последнюю цифру числа и записываем в переменную
        number = number // 10  # Далее убираем число которое запомнили
        array.append(last_digit)  # добавляем это число в массив и повторям пока число больше нуля
    final_number = int(
        ''.join(map(str, array)))  # map(str) -> список в строку join убирает пробелы, int задает тип числу
    return final_number


def alrorithm_lishrell(number):  # непосредственно алгоритм нахождения чисел палиндромов
    is_processing = True
    counter = 0  # Счетчик итераций который требуют в выводе
    while is_processing:  # цикл сравнивает введенное число с этим же перевернутым числом
        if number != reverse_number(
                number):  # Если эти числа не равны, то по задаче мы должны складывать число и его перевернутое значение
            number += reverse_number(number)
            counter += 1  # Считаем итерации

        else:
            is_processing = False
    print(f'The palindrome number is obtained after {counter} iterations. The palindrome number is {number}.')
    return number


def y_n_input():  # функция которая в зависимости от y n выводит true or false
    is_process = True
    while is_process:
        print("Enter Y to continue or N to stop(Y/N): ")
        x = input()  # Вводим икс и далее сравниваем с доступными значениями
        if x not in ['y', 'n', 'Y', 'N']:
            print("Error has been detected!")
        if x in ['Y', 'y']:
            return True
        if x in ['N', 'n']:
            return False


def main():  # основное тело программы
    is_process = True
    while is_process:
        number = input_number()  # ввод корректного числа
        alrorithm_lishrell(number)  # работа алгоритма и его вывод в одной функции
        is_process = y_n_input()  # выход из зацикливания программы


if __name__ == '__main__':
    main()
