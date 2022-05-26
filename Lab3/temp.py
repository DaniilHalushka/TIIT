from main import *


def main():
    set1 = create_set()
    print_set(set1)
    set2 = create_set()
    print_set(set2)
    print('Результат разности двух множеств: ')
    print_set(simm_diff_sets(set1, set2))


main()