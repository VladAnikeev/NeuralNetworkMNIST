#define _USE_MATH_DEFINES
#include <iostream>
#include <string> 
#include <fstream>
#include <random>
#include <cmath>
#include "Matrix.h"

int main()
{
    std::ifstream fout("mnist_train.csv");      //�������� �����  
    neural_network beta(784, 100, 10, 0.2);     //�������� ��������� ����
    char character_buffer = 0;                  //�������������� �����
    std::string buf("");                        //��������� �����
    double in_array[784];                       //������ ��� ������ ��������� ����
    int correct_answer = 0;                     //���������� �����
    int �orrect_answers_from_neural = 0;        //���������� ������ �� ��������� ����                           
    double out_array[10];                       //������ �������� ������

     //������� ���� ������������� ������
    for (double g = 1; g < 120001; g++)
    {
        fout.get(character_buffer);             //��������� ������� ������
        correct_answer = character_buffer - 48;//������� � ������� ������
        for (int k = 0; k < 10; k++)            //�������� �������� �� ������ �������
        {
            out_array[k] = 0.01;                //������� �������� �������� � �������������� 
        }
        out_array[correct_answer] = 0.99;      //������ �����

        fout.get(character_buffer);             //������� �������
        character_buffer = 0;

        for (int i = 0; !fout.eof() and (character_buffer != '\n'); ++i)//������ �� �����
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


        if (beta.train(in_data, out_data) == correct_answer)//������� ������ �������
        {
            ++�orrect_answers_from_neural;
        }
        std::cout << "#" << g << "  " << (double)(�orrect_answers_from_neural / g) << " " << �orrect_answers_from_neural << std::endl;
    }
    return 0;
}