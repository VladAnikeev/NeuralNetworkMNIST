#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string> 
#include <fstream>
#include <random>
#include <cmath>
#include "Matrix.h"
using namespace sf;

int main()
{
    neural_network my_network(784, 100, 10, 0.2);   //Создание нейронной сети
    my_network.read("neurons.dat");                 //Заполнение коэфициентов нейронной сети


    int x = 0;
    int y = 0;
    // Объект, который, собственно, является главным окном приложения
    RenderWindow window(VideoMode(560, 560), "'Enter' - verify       'Esc' - clear");
    double in_array[784];                          //Массив для входных данных
    for (int i = 0; i < 784; i++)
    {
        in_array[i] = 0;
    }

    Matrix in_matrix(1, 784);                      //Матрица для работа с нейронной сетью
    bool painting = 0;                             //Для нажатия левой кнопки
    Vector2i pixelPos;                             //Для координат курсора
    Vector2f pos;                                  //Уходим от коорд окна

    Event event;
    int X;
    int Y;
    RectangleShape rectangle(Vector2f(20.f, 20.f));
    while (window.isOpen())                        //Главный цикл приложения: выполняется, пока открыто окно
    {
        // Обрабатываем очередь событий в цикле
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)        //Закрытие окна
                window.close();                     // тогда закрываем его
            else if (event.type == Event::MouseButtonPressed)
            {                                       //Если нажата клавиша мыши
                if (event.key.code == Mouse::Left)  //именно левая
                {
                    painting = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {                                      //Отжатие кнопки мыши
                painting = false;
            }
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Enter)
                {                                 //Угадавоние нарисованой цифры
                    in_matrix.overwriting(in_array);
                    std::wstring numer = "Your number: " + std::to_wstring(my_network.query(in_matrix));
                    window.setTitle(numer);
                }
                else if (event.key.code == Keyboard::Escape)
                {                                //Очистка
                    for (int i = 0; i < 784; i++)
                    {
                        in_array[i] = 0;
                    }
                }
            }
        }
        if (painting)                           //Внесение изменений от пользователя/рисование
        {
            pixelPos = Mouse::getPosition(window);
            pos = window.mapPixelToCoords(pixelPos);
            X = pos.x / 20;
            Y = pos.y / 20;
            in_array[Y * 28 + X] = 255;
        }
        window.clear(Color(0, 0, 0, 0));        //Очистка
        for (int i = 0; i < 784; i++)           //Отрисовка квадратиков
        {
            x = i % 28;
            y = (i - x) / 28;
            rectangle.setFillColor(Color(in_array[i], in_array[i], in_array[i]));
            rectangle.setPosition(x * 20, y * 20);
            window.draw(rectangle);
        }
        // Отрисовка окна
        window.display();
    }

    return 0;
}
