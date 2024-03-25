#include <iostream>
#include <vector>
#include <set>
using namespace std;

double ArithmeticCoding(string str, const vector<pair<char, double>>& alphabet, double left, double right) {
    if (str.empty()) { //если символы закончились, то выводим центр конечного отрезка
        return (right - left) / 2 + left;
    }
    char ch = str[0]; //берем новый символ с начала строки
    auto it = find_if(alphabet.begin(), alphabet.end(), [&ch](const pair<char, double>& pair) {
        return pair.first == ch;
        }); //находим в нашем альфавите совпадение по символу (получаем итератор на этот элемент в векторе)
    int index = (int)(it - alphabet.begin()); //получаем индекс элемента с нужным нам символом (нужно потом для цикла)
    double frequencyOfChar = (*it).second; //получаем из найденного ранее элемента его частоту
    double length = right - left; //для удобства объявляем переменную текущей длины отрезка
    for (int i = 0; i < index; ++i) {
        left += length * alphabet[i].second; //пока не дойдем до нашего элемента по очереди двигаем левую часть отрезка
    }
    right = length * frequencyOfChar + left; //находим правую часть отрезка
    str.erase(str.begin()); //удаляем первый элемент строки, тк он нам больше не нужен
    cout << ch << "  " << left << "  " << right << endl; //вывод итераций
    return ArithmeticCoding(str, alphabet, left, right); //рекурсия будет вызываться до тех пор, пока в строка останется пуста
}

string ArithmeticDecoding(double codedNumber, const vector<pair<char, double>>& alphabet, int length) {
    string answer;
    for (int i = 0; i < length; ++i) {
        double left = 0;
        for (int j = 0; j < alphabet.size(); ++j) { //проходимся по всему альфавиту и выясняем подходящий под закодированное число символ (идем слева направо и ищем нужный отрезок)
            if (codedNumber <= alphabet[j].second + left) {
                cout << alphabet[j].first << "  " << codedNumber << endl;
                answer += alphabet[j].first;
                codedNumber = (codedNumber - left) / alphabet[j].second; //нормируем вещественное число
                break;
            }
            left += alphabet[j].second; //если отрезок не подошел, то смещаем левую границу для проверки следующего отрезка
        }
    }
    return answer;
}

int main()
{
    string str;
    set<char> chars;
    double frequency;
    vector<pair<char, double>> alphabet;
    cout << "Input the string: ";
    cin >> str;
    for (const auto& el : str) {
        chars.insert(el);
    }
    for (const auto& el : chars) {
        cout << "Input frequency of char " << el << ": ";
        cin >> frequency;
        alphabet.push_back({ el, frequency });
    }
    cout << endl;
    double codedNumber = ArithmeticCoding(str, alphabet, 0, 1);
    cout << "Your coded answer: " << codedNumber << endl;

    string decodedString = ArithmeticDecoding(codedNumber, alphabet, (int)str.length());
    cout << "Your decoded answer: " << decodedString;

    return 0;
}

