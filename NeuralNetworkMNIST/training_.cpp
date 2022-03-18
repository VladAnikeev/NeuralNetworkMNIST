#define _USE_MATH_DEFINES
#include <iostream>
#include <string> 
#include <fstream>
#include <random>
#include <cmath>
#include "Matrix.h"

int main()
{
    std::ifstream fout("mnist_train.csv");      //Открытие файла  
    neural_network beta(784, 100, 10, 0.2);     //Создание нейронной сети
    char character_buffer = 0;                  //Односимвольный буфер
    std::string buf("");                        //Строковый буфер
    double in_array[784];                       //Массив для данных неройнной сети
    int correct_answer = 0;                     //Правильный ответ
    int сorrect_answers_from_neural = 0;        //Правильные ответы от нейронной сети                           
    double out_array[10];                       //Верные выходные данные

     //Перебор всех тренировочных данных
    for (double g = 1; g < 120001; g++)
    {
        fout.get(character_buffer);             //Получения верного ответа
        correct_answer = character_buffer - 48;//Перевод в дробный формат
        for (int k = 0; k < 10; k++)            //Снижение занчений не верных ответов
        {
            out_array[k] = 0.01;                //Нулевые значение привидут к деградированию 
        }
        out_array[correct_answer] = 0.99;      //Верный ответ

        fout.get(character_buffer);             //Убираем запятую
        character_buffer = 0;

        for (int i = 0; !fout.eof() and (character_buffer != '\n'); ++i)//чтение из файла
        {
            while (fout.get(character_buffer) and (character_buffer != '\n') and (character_buffer != ','))
            {
                buf += character_buffer;
            }
            in_array[i] = (std::stod(buf) / 255 * 0.99) + 0.01;
            buf = "";
        }

        Matrix in_data(in_array, 1, 784);
        Matrix out_data(out_array, 1, 10);


        if (beta.train(in_data, out_data) == correct_answer)//подсчет верных ответов
        {
            ++сorrect_answers_from_neural;
        }
        std::cout << "#" << g << "  " << (double)(сorrect_answers_from_neural / g) << " " << сorrect_answers_from_neural << std::endl;
    }
    return 0;
}