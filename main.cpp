#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iterator>

using namespace std;

class Furniture {
public:
    string name;
    int count = 0;
    int art = 0;
};
class CountryHouse : public Furniture {
public:
    string waterproof;
    bool add() {
        cout << "Введите артикул:\t";
        cin >> art;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка ввода, введите число" << endl;
            add();
            return false;
        }
        cout << "Введите название:\t";
        cin >> name;
        cout << "Введите количество:\t";
        cin >> count;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка ввода, введите число" << endl;
            add();
            return false;
        }
        cout << "Водонепроницаемый(да/нет):\t";
        cin >> waterproof;
        count = articul(art, count);
        bool write = writeToFile("county.csv", art, name, count, waterproof);
        return true;
    }

    bool writeToFile(string file_name, int art, string name, int count, string waterproof) {
        ofstream CountryFurn;
        CountryFurn.open(file_name, ios_base::app);

        CountryFurn << art << "\t" << name << "\t" << count << "\t" << waterproof << endl;
        CountryFurn.close();
        return true;
    }

    int articul(int search_art, int countnew) {
        vector <string> record;
        ifstream CountryFurn;
        CountryFurn.open("county.csv");
        bool articulfound = false;
        string artplace;
        string nameplace;
        string countplace;
        int index = -1; // индекс строки в векторе 
        string last; // костыль для перехода на новую строчку
        while (getline(CountryFurn, artplace, '\t') && !articulfound) {
            vector <string> record;
            getline(CountryFurn, nameplace, '\t');
            getline(CountryFurn, countplace, '\t');
            getline(CountryFurn, last, '\n');
            int artt = atoi(artplace.c_str());      // перевод строки в целочисленный тип
            int count = atoi(countplace.c_str());
            index++;
            if (artt == search_art) {
                cout << "артикул нашелся" << endl;
                articulfound = true;
                countnew = countnew + count;
            help:
                cout << "1.Добавить\t" << "2.Удалить запись\t"<<"3.Показать" << endl;
                char a;
                cin >> a;
                switch (a) {
                case '1':writeToFile("county.csv", artt, nameplace, countnew, last);
                    remove(index);
                    cout << "Удаление произошло" << endl;
                    break;
                case '2':remove(index);
                cout << "Удаление произошло" << endl;
                    break;
                case '3': find(index);
                    break;
                default: cout << "Введите 1 или 2" << endl;
                cin.clear();
                cin.ignore(32767,'\n');
                    goto help;
                }

                
            }
        }
        CountryFurn.close();
        return countnew;
    }

    bool remove(int index) {
        vector<string> vec;
        ifstream DelC;
        DelC.open("county.csv");
        if (DelC.is_open()) {
            string str;
            while (getline(DelC, str)) {
                vec.push_back(str);
            }
            DelC.close();
            if (vec.size() < index) {
                return false;
            }
            vec.erase(vec.begin() + index);
            ofstream DelCC("county.csv");
            if (DelCC.is_open()) {
                copy(vec.begin(), vec.end(), ostream_iterator<string>(DelCC, "\n"));
                sort(vec.begin(), vec.end());
                DelCC.close();
                return true;

            }
            return false;
        }
        return false;
    }





    void read() {
        vector <string> record;
        ifstream CountryFurn;
        CountryFurn.open("county.csv");
        if (!CountryFurn.is_open()) {
            cout << "Файл не открылся" << endl;
        }
        else {
            cout << "Файл открыт" << endl;
            string field_one;
            while (getline(CountryFurn, field_one, ' ')) {
                record.push_back(field_one);
            }
            cout << record[0] << '\t' << endl;

        }
        CountryFurn.close();

    }

    bool find(int index) {
        vector<string> vec;
        ifstream DelC;
        DelC.open("county.csv");
        if (DelC.is_open()) {
            string str;
            while (getline(DelC, str)) {
                vec.push_back(str);
            }
            DelC.close();
            if (vec.size() < index) {
                return false;
            }
            cout << vec[index]<< endl;;
            return true;
        }
        cout<<"Искомого артикула не сущетсвует"<<endl;
        return false;
    }
};


class Flat : public Furniture {
public:
    char NeedLift;
};

int main() {
    setlocale(LC_ALL, "Russian");
    CountryHouse one;

sw:
    cout << "1.Добавить предмет\t" << "2.Показать все\t" << "3.Добавить количество\t" <<endl<< "4.Выйти\t"<<"5.Найти товар по артикулу" << endl;
    char a = 0;
    cin >> a;
    switch (a) {
    case '1': one.add();
        goto sw;
        break;
    case '2': one.read();
        goto sw;
        break;
    case '3':
        cout << "Введите артикул и кол-во" << endl;
        int artt, countt;
        cin >> artt;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка ввода, нужно ввести число" << endl;
            goto sw;
        }
        cin >> countt;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка ввода, нужно ввести число" << endl;
            goto sw;
        }
        one.articul(artt, countt);
        goto sw;
        break;
    case '4': break;
    case '5': 
        int arttt;
        cout<<"Введите артикул"<<endl;
        cin >> arttt;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка ввода, нужно ввести число" << endl;
            goto sw;
        }
        one.articul(arttt, 0);
        break;
    default: cout << "Ошибка!\t Введите 1-4" << endl;
        cin.clear();
        cin.ignore(32767,'\n');
        break;
    }
    goto sw;
    return 0;
}
