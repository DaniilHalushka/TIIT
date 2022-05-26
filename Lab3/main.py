import re


def create_set() -> list:
    """Заполнение множеств"""
    temp_set = set()
    m = int(input('Введите мощность множества: '))
    print('Введите элементы множества: ')
    for i in range(m):
        check_string(temp_set)
    lst = []
    for item in temp_set:
        lst.append(item)
    return lst


def print_set(my_set: list):
    """Отображение множества для пользователя"""
    print('Множество ', end=' {')
    for item in my_set:
        if item != my_set[len(my_set) - 1]:
            print(item, end=', ')
        else:
            print(item, end='')
    print('}')


def simm_diff_sets(set_1: list, set_2: list) -> list:
    """Функция, выполняющая симметрическую разность множеств """
    result = []
    is_repeat = 0
    for i in range(len(set_1)):
        is_repeat = 0
        for j in range(len(set_2)):
            if set_1[i] == set_2[j]:
                is_repeat = 1
                break
        if is_repeat == 0:
            result.append(set_1[i])
    for i in range(len(set_2)):
        is_repeat = 0
        for j in range(len(set_1)):
            if set_2[i] == set_1[j]:
                is_repeat = 1
                break
        if is_repeat == 0:
            result.append(set_2[i])
    result = list(result)
    return result

# regular expression


def check(inp: str) -> list:
    pattern = r'[a-zA-Z0-9]+'
    tmp_list = []
    inp = inp.split('{')[1]
    inp = inp.rsplit('}')[0]
    for word in inp.split(','):
        if re.search(pattern, word):
            tmp_list.append(word)
    return sorted(tmp_list)


def correct_input(inp: str) -> bool:
    pattern = r'[a-zA-Z0-9\<\>\{\}\,]'
    res = False
    for char in inp:
        if re.search(pattern, char):
            res = True
        else:
            return False
    return res


def check_string(set_i: list):
    inp = str(input())
    if inp[0] == "{":
        tmp_list = check(inp)
        s = '{'
        for item in tmp_list:
            if item != tmp_list[len(tmp_list) - 1]:
                s += str(item) + ', '
            else:
                s += str(item)
        s += '}'
        set_i.add(s)
    elif correct_input(inp):
        set_i.add(inp)
        return
    else:
        print('Введите корректное значение: ')
        check_string(set_i)
