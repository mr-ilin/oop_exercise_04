#include <iostream>
#include <vector>
#include <string>
#include <utility>

/*
Разработать шаблоны классов согласно варианту задания. Вариант 7: 6-угольник, 8-угольник и треугольник
Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. 
Классы должны иметь только публичные поля. В классах не должно быть методов, только поля. Ф
игуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. 
Для хранения координат фигур необходимо использовать шаблон  std::pair.
Например:
template <class T>
struct Square{
    using vertex_t = std::pair<T,T>;
    vertex_t a,b,c,d;
};

Необходимо реализовать две шаблонных функции:
1.	Функция print печати фигур на экран std::cout  (печататься должны координаты вершин фигур). 
    Функция должна принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).
2.	Функция square вычисления суммарной площади фигур.
    Функция должна принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).

Создать программу, которая позволяет:
•	Создает набор фигур согласно варианту задания (как минимум по одной фигуре каждого типа с координатами типа int и координатоми типа double).
•	Сохраняет фигуры в std::tuple
•	Печатает на экран содержимое std::tuple с помощью шаблонной функции print.
•	Вычисляет суммарную площадь фигур в std::tuple и выводит значение на экран.

При реализации шаблонных функций допускается использование вспомогательных шаблонов std::enable_if, std::tuple_size, std::is_same.
*/

// Шаблонная структура для шестиугольника
template <class T>
struct Hexagon {
    using type = T;
    using vertex = std::pair<T, T>;

    vertex center;
    T radius;
    bool valid;
    std::vector<vertex> path;

    Hexagon() : center(), radius(), valid(false) {}

    Hexagon(vertex center, T radius) : center(center), radius(radius) {
        if (radius > 0) {
            valid = true;
            count_vertexes(*this);
        } else {
            valid = false;
        }
    }

    ~Hexagon() = default;
};

template <class T>
void count_vertexes(Hexagon<T>& hex) {
    // Заполняем вектор вершин по формуле
    const double epsilon = 0.001;
    for (size_t i = 0; i < 6; ++i) {
        double vertex_x = hex.center.first + hex.radius * cos( (M_2_PI * i) / 6 );
        double vertex_y = hex.center.second + hex.radius * sin ( (M_2_PI * i) / 6 );

        // Сравниваем погрешность при приведении к типу T
        if ( abs(vertex_x - static_cast<T>(vertex_x)) > epsilon || abs(vertex_y - static_cast<T>(vertex_y)) > epsilon ) {
            hex.valid = false;
        }

        hex.path.push_back(std::make_pair(static_cast<T>(vertex_x), static_cast<T>(vertex_y)));
    }
}

// Шаблонная структура для восьмиугольника
template <class T>
struct Octagon {
    using type = T;
    using vertex = std::pair<T, T>;

    vertex center;
    T radius;
    bool valid;
    std::vector<vertex> path;

    Octagon() : center(), radius(), valid(false) {}

    Octagon(vertex center, T radius) : center(center), radius(radius) {
        if (radius > 0) {
            valid = true;
            count_vertexes(*this);
        } else {
            valid = false;
        }
    }

    ~Octagon() = default;
};

template <class T>
void count_vertexes(Octagon<T>& octa) {
    // Заполняем вектор вершин по формуле
    const double epsilon = 0.001;
    for (size_t i = 0; i < 3; ++i) {
        double vertex_x = octa.center.first + octa.radius * cos( (M_2_PI * i) / 8 );
        double vertex_y = octa.center.second + octa.radius * sin ( (M_2_PI * i) / 8 );

        // Сравниваем погрешность при приведении к типу T
        if ( abs(vertex_x - static_cast<T>(vertex_x)) > epsilon || abs(vertex_y - static_cast<T>(vertex_y)) > epsilon ) {
            octa.valid = false;
        }

        octa.path.push_back(std::make_pair(static_cast<T>(vertex_x), static_cast<T>(vertex_y)));
    }
}

// Шаблонная структура для треугольника
template <class T>
struct Triangle {
    using type = T;
    using vertex = std::pair<T, T>;

    vertex center;
    T radius;
    bool valid;
    std::vector<vertex> path;

    Triangle() : center(), radius(), valid(false) {}

    Triangle(vertex center, T radius) : center(center), radius(radius) {
        if (radius > 0) {
            valid = true;
            count_vertexes(*this);
        } else {
            valid = false;
        } 
    }

    ~Triangle() = default;
};

template <class T>
void count_vertexes(Triangle<T>& triangle) {
    // Заполняем вектор вершин по формуле
    const double epsilon = 0.001;
    for (size_t i = 0; i < 3; ++i) {
        double vertex_x = triangle.center.first + triangle.radius * cos( (M_2_PI * i) / 3 );
        double vertex_y = triangle.center.second + triangle.radius * sin ( (M_2_PI * i) / 3 );

        // Сравниваем погрешность при приведении к типу T
        if ( abs(vertex_x - static_cast<T>(vertex_x)) > epsilon || abs(vertex_y - static_cast<T>(vertex_y)) > epsilon ) {
            triangle.valid = false;
        }

        triangle.path.push_back(std::make_pair(static_cast<T>(vertex_x), static_cast<T>(vertex_y)));
    }
}

// Печать Octagon
template<class T>
typename std::enable_if<std::is_same<T, Octagon<typename T::type>>::value, void>::type print(T& figure) {
    if (figure.valid) {
        for (auto vertex : figure.path)
            std::cout << "(" << vertex.first << ", " << vertex.second << ") ";
        std::cout << std::endl;
    } else {
        std::cout << "Wrong Octagon" << std::endl;
    }
}
// Площадь Octagon
template<class T>
typename std::enable_if<std::is_same<T, Octagon<typename T::type>>::value, typename T::type>::type square(T& figure) {
    if (figure.valid) {
        return 4 * figure.radius * figure.radius * sqrt(2);
    } else {
        return 0;
    }  
}

// Печать Triangle
template<class T>
typename std::enable_if<std::is_same<T, Triangle<typename T::type>>::value, void>::type print(T& figure) {
    if (figure.valid) {
        for (auto vertex : figure.path)
            std::cout << "(" << vertex.first << ", " << vertex.second << ") ";
        std::cout << std::endl;
    } else {
        std::cout << "Wrong Triangle" << std::endl;
    }
}
// Площадь Triangle
template<class T>
typename std::enable_if<std::is_same<T, Triangle<typename T::type>>::value, typename T::type>::type square(T& figure) {
    if (figure.valid) {
        return (3 * sqrt(3) * figure.radius * figure.radius) / 4;
    } else {
        return 0;
    }  
}

// Печать Hexagon
template<class T>
typename std::enable_if<std::is_same<T, Hexagon<typename T::type>>::value, void>::type print(T& figure) {
    if (figure.valid) {
        for (auto vertex : figure.path)
            std::cout << "(" << vertex.first << ", " << vertex.second << ") ";
        std::cout << std::endl;
    } else {
        std::cout << "Wrong Hexagon" << std::endl;
    }
}
// Площадь Hexagon
template<class T>
typename std::enable_if<std::is_same<T, Hexagon<typename T::type>>::value, typename T::type>::type square(T& figure) {
    if (figure.valid) {
        return (3 * sqrt(3) * figure.radius * figure.radius) / 2;
    } else {
        return 0;
    }  
}

// Печать Tuple
template <class T, size_t index> 
typename std::enable_if<index >= std::tuple_size<T>::value, void>::type print_tuple(T&){
    std::cout << std::endl;
}

template <class T, size_t index> 
typename std::enable_if<index < std::tuple_size<T>::value, void>::type print_tuple(T& tuple){
    auto figure = std::get<index>(tuple);
    print(figure);
    print_tuple<T,index+1>(tuple);
}

// Площадь Tuple
template <class T, size_t index>
double square_tuple(T& tuple){
    auto item = std::get<index>(tuple);
    double value = square(item);
    
    if constexpr ((index+1) < std::tuple_size<T>::value) {
        return value + square_tuple<T,index+1>(tuple);
    }
    return value;
}

int main() {
    Hexagon<double> d_hex({10,10},2);
    Octagon<float> d_oct({0,1}, 3);
    Triangle<double> d_tri({0,0}, 6);
    Hexagon<int> i_hex({0,0},4);
    Octagon<char> c_oct({1,1}, 5);
    Triangle<size_t> s_tri({0,0}, 6);

    std::tuple < decltype(d_hex), decltype(d_oct), decltype(d_tri), decltype(i_hex), decltype(c_oct), decltype(s_tri) > tuple {
        d_hex, d_oct, d_tri, i_hex, c_oct, s_tri
    };
    print_tuple<decltype(tuple), 0>(tuple);
    std::cout << "Total square = " << square_tuple<decltype(tuple), 0>(tuple) << std::endl;
    return 0;
}
