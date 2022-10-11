#include <cmath>
#include <iostream>

using namespace std;

double f(double x, int choice); // Функция обеспечивающая связь между выбором функции пользователем и самой функцией
double f1(double x); // Первая фунцкия
double f2(double x); // Вторая и т.д. 
double f3(double x);
double f4(double x);
double f5(double x);

double a = 666, b = 666; //Глобальные переменные отвечающие за отрезок

void algorithm_1_1_1(double x, double h, int choice); //метод Дэвиса-Свенна-Кэмпи
double algorithm_1_2_3(double eps, int choice); //метод Фибоначчи
double algorithm_1_2_5(double eps, int choice); //метод параболической аппроксимации Пауэлла

double Fubonachi(int n); //функция считающая числа Фабоначчи

int main()
{
	setlocale(LC_ALL, "RUS");
	int choiceA, choiceF; //Переменные хранящие выбранный пользователем алгоритм и функциюю соответсвенно
	double x0, h, eps;
	cout << "Выберите нужный алгоритм : \n" << "1 - метод Дэвиса-Свенна-Кэмпи\n" << "2 - метод Фибоначчи\n" << "3 - метод параболической аппроксимации Пауэлла" << endl;
	cin >> choiceA;
	cout << "Введите номер функции: " << endl;
	cin >> choiceF;
	if (choiceA == 1) // Если выбран метод Дэвиса-Свенна-Кэмпи
	{
		cout << "Введите x0" << endl;
		cin >> x0;
		x0 = x0 + 0.001;
		cout << "Введите шаг h" << endl;
		cin >> h;
		algorithm_1_1_1(x0, h, choiceF);
		a = a - 0.001;
		b = b - 0.001;
		cout << "Results: " << endl << "a = " << a << endl << "b = " << b << endl;
		return 0;
	}
	cout << "Введите начало отрезка - число a: " << endl;
	cin >> a;
	cout << "Введите конец отрезка - число b: " << endl;
	cin >> b;
	if (choiceA == 2)
	{
		cout << "Введите эпсилон: " << endl;
		cin >> eps;
		x0 = algorithm_1_2_3(eps, choiceF);
		cout << "Results: " << endl << "x* = " << x0 << endl << "f(x*) = " << f(x0, choiceF) << endl;
		return 0;
	}
	if (choiceA == 3)
	{
		cout << "Введите эпсилон: " << endl;
		cin >> eps;
		x0 = algorithm_1_2_5(eps, choiceF);
		cout << "Results: " << endl << "x* = " << x0 << endl << "f(x*) = " << f(x0, choiceF) << endl;
		return 0;
	}
}

void algorithm_1_1_1(double x, double h, int choice) //метод Дэвиса-Свенна-Кэмпи
{
	int k;
	double x1, xk, xk2;
	if (f(x, choice) > f(x + h, choice)) // Шаг 2
	{
		a = x;
		x1 = x + h;
		k = 2;
	}
	else
		// Шаг 3 снизу
	{
		if (f(x - h, choice) >= f(x, choice))
		{
			a = x - h;
			b = x + h;
			return;
		}
		else
		{
			b = x;
			x1 = x - h;
			h = (-1) * h;
			k = 2;
		}
	}
	while ((a == 666) || (b == 666)) // Шаг 4 + Шаг 5
	{
		xk = x + pow(2, k - 1) * h;
		xk2 = x + pow(2, k - 2) * h;
		if (f(xk2, choice) <= f(xk, choice))
		{
			if (h > 0) b = xk;
			else a = xk;
			break;
		}
		else
		{
			if (h > 0) a = xk2;
			else b = xk2;
			k = k + 1;
		}
	}
}

double algorithm_1_2_3(double eps, int choice) //метод Фабоначчи
{
	int n = 0, k;
	double Fn = 1, F1 = 1, F2 = 1, x1, x2;
	double d = eps / 10;
	while (Fn < (b - a) / (2 * eps)) //шаг 1
	{
		F2 = Fn;
		Fn = Fn + F1;
		F1 = F2;
		n++;
	}
	k = 0; //шаг 2
	x1 = a + (Fubonachi(n - 2) / Fn) * (b - a); //шаг 3
	x2 = a + (Fubonachi(n - 1) / Fn) * (b - a); //шаг 3

	while (0 == 0) //шаги 4 - 6
	{
		if (f(x1, choice) <= f(x2, choice)) //шаг 5
		{
			b = x2;
			x2 = x1;
			x1 = a + (Fubonachi(n - k - 3) / Fubonachi(n - k - 1)) * (b - a);
		}
		else
		{
			a = x1;
			x1 = x2;
			x2 = a + (Fubonachi(n - k - 2) / Fubonachi(n - k - 1)) * (b - a);
		}
		if (k = n - 3) //шаг 6
		{
			x2 = x1 + d;
			if (f(x1, choice) <= f(x2, choice)) b = x2;
			else a = x1;
			break;
		}
		else k = k + 1;
	}

	return (a + b) / 2; //шаг 7
}

double algorithm_1_2_5(double eps, int choice) //метод параболической аппроксимации Пауэлла
{
	double x = 0, x1, x2, x3, x4;
	double numbers[4][2];

	//Шаг 1
	x1 = a;
	x2 = (a + b) / 2;
	x3 = b;

	while (0 == 0)
	{
		//Шаг 2
		if ((f(x1, choice) > f(x2, choice)) && (f(x3, choice) > f(x2, choice))) x = x2;
		if ((f(x2, choice) > f(x1, choice)) && (f(x3, choice) > f(x1, choice))) x = x1;
		if ((f(x2, choice) > f(x3, choice)) && (f(x1, choice) > f(x3, choice))) x = x3;

		//Шаг 3
		x4 = 0.5 * ((pow(x2, 2) - pow(x3, 2)) * f(x1, choice) + (pow(x3, 2) - pow(x1, 2)) * f(x2, choice) + (pow(x1, 2) - pow(x2, 2)) * f(x3, choice)) / ((x2 - x3) * f(x1, choice) + (x3 - x1) * f(x2, choice) + (x1 - x2) * f(x3, choice));

		//Шаг 4 и шаг 7
		if (abs(x4 - x) <= eps) return x4;

		//Шаг 5
		numbers[0][0] = x1;
		numbers[1][0] = x2;
		numbers[2][0] = x3;
		numbers[3][0] = x4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j >= (i + 1); j--)
			{
				if (numbers[j][0] < numbers[j - 1][0])
				{
					x = numbers[j][0];
					numbers[j][0] = numbers[j - 1][0];
					numbers[j - 1][0] = x;
				}
			}
		}

		//Шаг 6
		numbers[0][1] = f(numbers[0][0], choice);
		numbers[1][1] = f(numbers[1][0], choice);
		numbers[2][1] = f(numbers[2][0], choice);
		numbers[3][1] = f(numbers[3][0], choice);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 3; j >= (i + 1); j--)
			{
				if (numbers[j][1] < numbers[j - 1][1])
				{
					x = numbers[j][1];
					numbers[j][1] = numbers[j - 1][1];
					numbers[j - 1][1] = x;

					x = numbers[j][0];
					numbers[j][0] = numbers[j - 1][0];
					numbers[j - 1][0] = x;
				}
			}
		}

		x1 = numbers[0][0];
		x2 = numbers[1][0];
		x3 = numbers[2][0];

	}

	return x4;
}

double Fubonachi(int n) //счёт чисел Фабоначчи
{
	int Fn = 1, F1 = 1, F2 = 1;
	for (int i = 0; i < n; i = i++)
	{
		F2 = Fn;
		Fn = Fn + F1;
		F1 = F2;
	}
	return Fn;
}

double f(double x, int choice)
{
	switch (choice)
	{
	case 1: return f1(x);
	case 2: return f2(x);
	case 3: return f3(x);
	case 4: return f4(x);
	case 5: return f5(x);
	}
}

//Снизу функции
double f1(double x)
{
	double f;
	f = 4 * pow(x, 3) - 8 * pow(x, 2) - 11 * x + 5;
	return f;
}
double f2(double x)
{
	double f;
	f = x + 3 / pow(x, 2);
	return f;
}
double f3(double x)
{
	double f;
	f = (x + 2.5) / (4 - pow(x, 2));
	return f;
}
double f4(double x)
{
	double f;
	f = (-1) * sin(x) - sin(3 * x) / 3;
	return f;
}
double f5(double x)
{
	double f;
	f = (-2) * sin(x) - sin(2 * x) - (2 * sin(3 * x)) / 3;
	return f;
}