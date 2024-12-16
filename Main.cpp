#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

double function(double x) 
{
    return x - 1.0 / (3 + sin(3.6 * x));
}

double first_derivative(double x) 
{
    double denom = 3 + sin(3.6 * x);
    return 1 + (3.6 * cos(3.6 * x)) / (denom * denom);
}

double second_derivative(double x) 
{
    double denom = 3 + sin(3.6 * x);
    double firstPart = (3.6 * cos(3.6 * x));
    double secondPart = (3.6 * -3.6 * sin(3.6 * x));
    return secondPart / (denom * denom) - (2 * firstPart * firstPart) / (denom * denom * denom);
}

int main() 
{
    setlocale(LC_ALL, "Rus");
    double epsilon = 0.00001;
    double x0 = 0.0;
    bool found = false;

    // ����� ���������� �������� x0
    for (x0 = 0.0; x0 <= 0.85 && !found; x0 += 0.01) 
    {
        if (function(x0) * second_derivative(x0) > 0) 
        {
            found = true;
        }
    }

    if (!found) 
    {
        cout << "�� ������� ����� ���������� ��������� �������� x0 �� ������� [0; 0.85]." << endl;
        return 1;
    }

    x0 -= 0.01; // ��������� x0 ����� ���������� �����
    double x = x0;
    int iteration = 0;

    auto start = chrono::high_resolution_clock::now();

    while (fabs(function(x)) > epsilon) 
    {
        x = x - function(x) / first_derivative(x);
        iteration++;
        cout << "�������� " << iteration << ": x = " << x << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "��������� �������� x0: " << x0 << endl;
    cout << "���������� ��������: " << iteration << endl;
    cout << "������: " << x << endl;
    cout << "����������� �����: " << duration << " �����������" << endl;

    return 0;
}
