#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <cmath>
#include <math.h>

// Абстрактный класс "Геометрическая фигура"
class Shape {
public:
    virtual double area() const = 0;
    virtual std::string name() const = 0;
    virtual ~Shape() {}
};

// Класс "Круг"
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    std::string name() const override {
        return "Круг";
    }
};

// Класс "Треугольник" (расчёт по формуле Герона)
class Triangle : public Shape {
private:
    double a, b, c;  // Длины сторон 
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double area() const override {
        double s = (a + b + c) / 2.0; // Полупериметр
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

    std::string name() const override {
        return "Треугольник";
    }
};

// Класс "Прямоугольник"
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    std::string name() const override {
        return "Прямоугольник";
    }
};

int main() {

    setlocale(LC_ALL, "ru");

    // Создаем массив указателей на объекты типа Shape
    std::vector<std::shared_ptr<Shape>> shapes;

    // Добавляем в массив различные фигуры
    shapes.push_back(std::make_shared<Circle>(5.0));           // Круг с радиусом 
    shapes.push_back(std::make_shared<Triangle>(3.0, 4.0, 5.0)); // Треугольник со сторонами 
    shapes.push_back(std::make_shared<Rectangle>(6.0, 7.0));     // Прямоугольник со сторонами 
    shapes.push_back(std::make_shared<Circle>(10.0));            // Круг с радиусом 
    shapes.push_back(std::make_shared<Triangle>(10.0, 13.0, 15.0)); // Треугольник со сторонами 
    shapes.push_back(std::make_shared<Rectangle>(22.0, 30.0));    // Прямоугольник со сторонами 

    // Сортировка фигур по площади (по возрастанию)
    std::sort(shapes.begin(), shapes.end(), [](const std::shared_ptr<Shape>& s1, const std::shared_ptr<Shape>& s2) {
        return s1->area() < s2->area();
        });

    // Выводим для каждой фигуры её тип и площадь 
    std::cout << "Фигуры, отсортированные по возрастанию площади:" << std::endl;
    for (const auto& shape : shapes) {
        std::cout << shape->name() << " с площадью: " << shape->area() << std::endl;
    }

    return 0;
}
