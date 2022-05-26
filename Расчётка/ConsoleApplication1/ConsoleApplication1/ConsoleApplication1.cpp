// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <string>

#include <conio.h>

#include <fstream>

#include <new>

using namespace std;


int max_row = 0;//Количество строк в списке смежности

int max_col = 0;//Максимальное количество столбцов в строке списка смежности

std::string path = "Graph.txt";//Путь к файлу со списком смежности

std::ifstream fin;

std::string memory_file[100];//Массив для сохранения данных из файла где хранится список смежности

int memory_file_size = 0;//Хранит количество строк в списке смежности

char seps[] = " ,\t\n";//Разделители

int max_vertex_length = 50;//максимальная длинна названия вершины графа (влияет на выделение памяти)

int max_edges_length = 20;//максимальная длинна названия дуги графа (влияет на выделение памяти)


//процедура расчета количества вершин(vertex) в строке
int count_vertex_in_row(std::string& row, char* seps)
{
    char* vertex = NULL;//Указатель на символьную строку с именем вершины

    char* next_vertex = NULL;//Указатель на следующую символьную строку с именем вершины

    int count_vertex = 0;//Счетчик количества вершин в строке

    int len_row = row.length() + 1;//Длина строки

    char* ch_row = new char[len_row];//выделение памяти под копию строки strtok_s работает только с char*

    strcpy_s(ch_row, len_row, row.c_str());//копирование string в char*

    vertex = strtok_s(ch_row, seps, &next_vertex);//Выборка названия первой вершины из строки

    //выбираем все вершины из строки
    while (vertex != NULL)
    {
        // взять вершину:
        if (vertex != NULL)
        {
            vertex = strtok_s(NULL, seps, &next_vertex);//Выборка названия следующей вершины из строки

            count_vertex++;
        }
    }
    return count_vertex;
}

//процедура выборки произвольной вершины из строки (num - порядковый номер вершины название которой мы хотим получить) 
char* get_vertex(std::string& row, char* seps, int num)
{
    char* vertex = NULL;

    char* next_vertex = NULL;

    int count_vertex = 0;

    int len_row = row.length() + 1;

    char* ch_row = new char[len_row];

    strcpy_s(ch_row, len_row, row.c_str());

    vertex = strtok_s(ch_row, seps, &next_vertex);

    //выбираем все вершины из строки;
    while ((vertex != NULL) && (num != 0))
    {
        // взять вершину:
        if (count_vertex == num)break;

        if (vertex != NULL)
        {
            vertex = strtok_s(NULL, seps, &next_vertex);

            count_vertex++;
        }
    }
    return vertex;
}

/*Поиск порядкового номера вершины в списке вершин
(vert - название вершины порядковый номер которой мы ищим в массиве ввершин)
(arr_vert - массив всех вершин)
(maxCount - количество вершин в arr_vert)
*/
int find_in_vertex(char* vert, char** arr_vert, int maxCount)
{
    int find_pos = 0;

    if (vert != NULL)
    {
        for (int i = 0; i < maxCount; i++)
            if (strcmp(arr_vert[i], vert) == 0)
            {
                find_pos = i;
                break;
            }
    }
    return find_pos;
}


int main()
{
    //ввод данных из файла в массив
    std::setlocale(LC_ALL, "ru");

    fin.open(path);
    //open file and create array 
    if (!fin.is_open())
    {
        std::cout << "Ошибка открытия файла!" << std::endl;
    }
    else
    {
        std::cout << "Файл открыт!" << std::endl;

        std::string input_string;//Строка для ввода данных из файла

        //счетчик строк
        int cInStr = 0;//Счетчик кол-во строк

        while (!fin.eof())
        {
            input_string = "";

            std::getline(fin, input_string);

            if (input_string.length() == 0)break;

            else memory_file[cInStr++] = input_string;
        }
        memory_file_size = cInStr;
    }
    fin.close();

    //расчет максимального количества вершин в строке
    for (int i = 0; i < memory_file_size; i++)
    {
        int current_col = 0;//Счетчик кол-во вершин в строке

        current_col = count_vertex_in_row(memory_file[i], seps);

        if (current_col > 0)
        {
            if (max_col < current_col)max_col = current_col;
        }
    }
    max_row = memory_file_size;

    std::cout << "max_col " << max_col << " max_row " << max_row << std::endl;

    //---------------------------------------------------------------------------
    //массив вершин
    char** array_vertex;//Массив для списка вершин

    array_vertex = new char* [max_row];

    for (int i = 0; i < max_col; i++)
    {
        array_vertex[i] = new char[max_vertex_length];
    }
    for (int i = 0; i < max_row; i++)
    {
        array_vertex[i] = (char*)"";
    }

    //Выборка всех возможных вершин
    for (int i = 0; i < max_row; i++)
    {
        array_vertex[i] = get_vertex(memory_file[i], seps, 0);
    }

    //for debug
    //for (int i = 0; i < max_row; i++)std::cout << array_vertex[i] << std::endl;

    //вывод список смежности
    std::cout << std::endl << std::endl;
    std::cout << "******************" << std::endl;
    std::cout << "*СПИСОК СМЕЖНОСТИ*" << std::endl;
    std::cout << "******************" << std::endl;
    for (int i = 0; i < memory_file_size; i++)
    {
        std::cout << memory_file[i] << std::endl;
    }

    std::cout << std::endl << std::endl;
    std::cout << "*******************" << std::endl;
    std::cout << "*СПИСОК РЕБЕР(ДУГ)*" << std::endl;
    std::cout << "*******************" << std::endl;
    //перебор всех ребер или дуг
    int count_edges = 0;//Количество ребер
    int max_count_edges = max_row * 3;
    //new*********************************************************************
    int** matrix_edg;//Матрица edges

    matrix_edg = new int* [max_count_edges];

    for (int i = 0; i < max_count_edges; i++)
    {
        matrix_edg[i] = new int[3];
    }
    //иннициализация матрицы edges
    for (int i = 0; i < max_count_edges; i++)
        for (int j = 0; j < 3; j++)
        {
            matrix_edg[i][j] = 0;
        }
    //выбираем все ребра
    for (int i = 0; i < max_row; i++)
    {
        //std::cout << "текущаяя вершина" << array_vertex[i] << std::endl;
        for (int j = 1; j < max_col; j++)
        {
            char* current_vertex = get_vertex(memory_file[i], seps, j);

            if (current_vertex != NULL)
            {
                int pos = find_in_vertex(current_vertex, array_vertex, max_row);

                matrix_edg[count_edges][0] = i;
                matrix_edg[count_edges][1] = pos;
                matrix_edg[count_edges][2] = 1;

                std::cout << "e" << count_edges + 1 << "(v" << matrix_edg[count_edges][0] + 1 << ",v" << matrix_edg[count_edges][1] + 1 << ")" << std::endl;
                //--------------------------------
                count_edges++;
            }

        }
    }
    /* для отладки список всех ребер без исключения пересекающихся
    std::cout << std::endl;
    for (int i = 0; i < max_count_edges; i++)
        std::cout << i << "->" << matrix_edg[i][0] << "," << matrix_edg[i][1] << "," << matrix_edg[i][2] << std::endl;
    */

    //убираем дубликаты ребер 
    for (int i = 0; i < max_count_edges; i++)
    {
        //for debug
        for (int j = i + 1; j < max_count_edges - 1; j++) {
            if (matrix_edg[j][2] > 0)
                if (matrix_edg[i][1] == matrix_edg[j][0] && matrix_edg[i][0] == matrix_edg[j][1])
                    matrix_edg[j][2] = 0;
        }
    }
    std::cout << std::endl << std::endl;
    std::cout << "******************" << std::endl;
    std::cout << "*ГРАФ ИНЦИНДЕНЦИЙ*" << std::endl;
    std::cout << "******************" << std::endl;

    for (int j = 0; j < max_row; j++)
    {
        std::cout << "V[" << array_vertex[j] << "]";

        for (int i = 0; i < max_count_edges; i++)
        {
            if ((matrix_edg[i][0] == j || matrix_edg[i][1] == j) && matrix_edg[i][2] > 0)

                std::cout << " E[" << i + 1 << "]";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < max_count_edges; i++)
    {
        if (matrix_edg[i][0] >= 0 && matrix_edg[i][1] >= 0 && matrix_edg[i][2] > 0)
        {
            std::cout << "E[" << i + 1 << "] V[" << array_vertex[matrix_edg[i][0]] << "] V[" << array_vertex[matrix_edg[i][1]] << "]" << std::endl;
        }
    }
    return 0;
}
