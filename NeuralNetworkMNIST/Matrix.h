#pragma once
#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
	double* value;//хранит саму матрицу с размером X*Y
	int X, Y, size;//данные размера мматрицы
public:
	Matrix();							//Конструктор по умолчанию
	Matrix(int x, int y);				//Конструктор с размером матрицы
	Matrix(double* input, int x, int y);//Конструктор для переноса матрциы 
	Matrix(Matrix& right);				//Конструктор копирования 
	~Matrix();							//Деконструктор 

	void sigmoid();						//Примение сигмойдной функции на каждый элемент матрицы 
	void out();							//Вывод матрицы /использовалась для проверки на каждом этапы создания неройнной сети 
	void random();						//Рандом в нормальном распределении с отклонением 0.5 от 0
	void random(int n);					//Рандом в нормальном распределении с отклонением n в степени -0.5 от 0
	void T();							//Транспонирование матрицы
	void overwriting(double* array);	//Перезапись 
	int index_max();					//Максимальное значение 
	void write(std::ofstream& fout);	//Запись в файл
	void read(std::ifstream& fin, int offset);//Чтения с файла с позиции
	Matrix transposed();				//Транспонирование матрицы с возращением  матрицы
	Matrix subtract_from_one();			//Вычетание от единицы 

	Matrix operator-(const Matrix& right);
	Matrix operator*(const Matrix& right);
	Matrix operator=(const Matrix& right);
	Matrix operator^(const Matrix& right);//Поэлементное умножение 
	void operator+= (const Matrix& right);
	Matrix operator*(const double& right);
};

Matrix::Matrix() :X(0), Y(0), size(0), value(NULL)//Конструктор по умолчанию
{
}
Matrix::Matrix(int x, int y) : X(x), Y(y), size(x* y)//конструктор в котором зануляется массив 
{
	value = new double[size];
	for (int i = 0; i < size; ++i)
	{
		value[i] = 0;
	}
}
Matrix::Matrix(double* input, int x, int y) :X(x), Y(y), size(x* y)//Конструктор для переноса матрциы 
{
	value = new double[size];
	for (int i = 0; i < size; ++i)
	{
		value[i] = input[i];
	}
}
Matrix::Matrix(Matrix& right)//Конструктор копирования 
{
	X = right.X;
	Y = right.Y;
	size = right.size;
	value = new double[size];
	for (int i = 0; i < size; ++i)
	{
		value[i] = right.value[i];
	}

}
Matrix::~Matrix()
{
	delete[] value;
}

void Matrix::sigmoid()//Примение сигмойдной функции на каждый элемент матрицы 
{
	for (int i = 0; i < size; ++i)
	{
		value[i] = 1 / (1 + (1 / (pow(M_E, value[i]))));
	}
}
void Matrix::out()//ввывод матрицы
{

	for (int i = 0; i < size; ++i)
	{
		//std::cout.width(7);
		if ((i % 28) == 0)
			std::cout << std::endl;
		std::cout << value[i] << " ";
	}
	std::cout << std::endl;
}
void Matrix::random()//Рандомит в нормальном распределении с отклонением 0.5
{
	std::mt19937 gen(0);
	std::normal_distribution<> d(0, 0.5);

	for (int i = 0; i < size; ++i)
	{
		value[i] = d(gen);

	}
}
void Matrix::random(int n)//Рандом в нормальном распределении с отклонением -0.5
{
	std::default_random_engine generator;
	std::normal_distribution<double> d(0, pow(n, -0.5));
	for (int i = 0; i < size; ++i)
	{
		value[i] = d(generator);

	}
}

void Matrix::T()//Транспонирование матрицы
{
	double* temporary = new double[size];
	int n = 0;
	for (int i = 0; i < Y; ++i)
	{
		for (int j = i; j < size; j = j + Y)
		{
			temporary[n] = value[j];
			++n;
		}
	}
	delete[] value;
	value = temporary;

	int swap = X;
	X = Y;
	Y = swap;
}

void Matrix::overwriting(double* array)//Перезапись 
{
	for (int i = 0; i < size; ++i)
	{
		value[i] = array[i];
	}
}
void Matrix::write(std::ofstream& fout)//Запись
{
	for (int i = 0; i < size; ++i)
	{
		fout.write((char*)&value[i], sizeof value[i]);
	}
}

void Matrix::read(std::ifstream& fin, int offset)//Чтение с позиции
{
	fin.seekg(offset * sizeof value[0], std::ios::beg);
	for (int i = 0; i < size; ++i)
	{
		fin.read((char*)&value[i], sizeof value[i]);
	}
}
int Matrix::index_max()//Максимальное значение 
{
	int max_index = 0;
	for (int i = 1; i < size; ++i)
	{
		if (value[max_index] < value[i])
		{
			max_index = i;
		}
	}
	return max_index;
}

Matrix Matrix::transposed()//Транспонирование матрицы возращением
{
	Matrix new_matrix(X, Y);
	int n = 0;
	for (int i = 0; i < Y; ++i)
	{
		for (int j = i; j < size; j = j + Y)
		{
			new_matrix.value[n] = value[j];
			++n;
		}
	}
	new_matrix.X = Y;
	new_matrix.Y = X;
	return new_matrix;
}

Matrix Matrix::subtract_from_one()//Вычетание от единицы
{
	double* difference = new double[size];
	for (int i = 0; i < size; ++i)
	{
		difference[i] = 1 - value[i];
	}
	Matrix differnce_matrix(difference, X, Y);
	delete[] difference;
	return differnce_matrix;
}

Matrix Matrix::operator-(const Matrix& right)
{
	double* difference = new double[size];
	for (int i = 0; i < size; ++i)
	{
		difference[i] = value[i] - right.value[i];
	}
	Matrix differnce_matrix(difference, X, Y);
	delete[] difference;
	return differnce_matrix;
}

Matrix Matrix::operator*(const Matrix& right)
{
	Matrix new_matrix(X, right.Y);
	for (int i = 0; i < X; ++i)
	{
		double* c = new_matrix.value + i * right.Y;
		for (int j = 0; j < right.Y; ++j)
			c[j] = 0;
		for (int n = 0; n < Y; ++n)
		{
			const double* b = right.value + n * right.Y;
			double a = value[i * Y + n];
			for (int j = 0; j < right.Y; ++j)
				c[j] += a * b[j];
		}
	}
	return  new_matrix;
}
Matrix Matrix::operator=(const Matrix& right)
{
	X = right.X;
	Y = right.Y;
	size = right.size;
	if (value != NULL)
		delete[] value;
	value = new double[size];
	for (int i = 0; i < size; ++i)
	{
		value[i] = right.value[i];
	}
	return *this;
}

Matrix Matrix::operator^(const Matrix& right)//Поэлеметное умножение 
{
	Matrix new_matrix(X, Y);
	for (int i = 0; i < size; ++i)
	{
		new_matrix.value[i] = value[i] * right.value[i];
	}
	return new_matrix;
}
void Matrix::operator+=(const Matrix& right)
{
	for (int i = 0; i < size; ++i)
	{
		value[i] += right.value[i];
	}
}

Matrix Matrix::operator*(const double& right)//Умножение на число
{
	for (int i = 0; i < size; ++i)
	{
		value[i] *= right;
	}
	return *this;
}



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class neural_network
{
private:
	int inodes, hnodes, onodes;	//Размер неронной сети
	double lr;					//Коэфициент обучения
	Matrix wih,					//Коэфициенты между входным и среднем слоем
		who;					//Коэфициенты между среднем и выходным слоем
public:
	neural_network();			//Конструктор по умолчанию
	neural_network(int inputnodes, int hiddennodes, int outputnodes, double learningrate);//Конструктор по созданию нейронной сети
	~neural_network();

	int train(Matrix& input_list, Matrix& targets_list);//Тренер
	int query(Matrix& input_list);	//Опрос неройнной сети
	void read(std::string fin);		//Чтение из файла
	void write(std::string fout);	//Запись в файл
};

neural_network::neural_network(int inputnodes, int hiddennodes, int outputnodes, double learningrate)
	:inodes(inputnodes), hnodes(hiddennodes), onodes(outputnodes), lr(learningrate),
	wih(hnodes, inodes), who(onodes, hnodes)
{
	wih.random(hnodes);
	who.random(onodes);
}

neural_network::~neural_network()
{
}

int neural_network::train(Matrix& input_list, Matrix& targets_list)
{
	input_list.T();					//Подготовка входных данных

	Matrix hidden_outputs;			//Промежуточные значения
	hidden_outputs = wih.operator*(input_list);
	hidden_outputs.sigmoid();

	Matrix final_outputs;			//Выходные значения
	final_outputs = who.operator*(hidden_outputs);
	final_outputs.sigmoid();


	Matrix output_errors;			//Ошибка выходных данных
	output_errors = (targets_list.transposed()) - final_outputs;


	Matrix hidden_errors(hnodes, 1);//Ошибка промежуточных данных 
	hidden_errors = (who.transposed()).operator*(output_errors);
	//Корректировка 
	who.operator+=
		((output_errors ^ final_outputs ^ final_outputs.subtract_from_one())
			* (hidden_outputs.transposed()) * (lr));

	wih.operator+=
		(((hidden_errors ^ hidden_outputs ^ hidden_outputs.subtract_from_one())
			* input_list.transposed()) * lr);

	return final_outputs.index_max();//Вывод максимального значения
}
int neural_network::query(Matrix& input_list)
{
	Matrix final_outpusts(inodes, 1);

	final_outpusts = wih.operator*(input_list.transposed());//Получения промежуточных 
	final_outpusts.sigmoid();

	final_outpusts = who.operator*(final_outpusts);			//Получения выходных
	final_outpusts.sigmoid();

	return final_outpusts.index_max();						//вывод максимального значения
}
void neural_network::read(std::string fin)
{
	std::ifstream file(fin, std::ios_base::in | std::ios_base::binary);
	who.read(file, 0);
	wih.read(file, onodes * hnodes);
	file.close();
}
void neural_network::write(std::string fout)
{
	std::ofstream file(fout, std::ios_base::out | std::ios_base::app | std::ios_base::binary);
	who.write(file);
	wih.write(file);
	file.close();
}
#endif 