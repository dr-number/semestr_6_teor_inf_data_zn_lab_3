#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

struct Sym {
public:
    char symbol;
    int count;
    float frequency;
public:
    Sym(char _symbol, int _count, float _frequency)  // конструктор объекта
    {
        symbol = _symbol;
        count = _count;
        frequency = _frequency;
    }
};

void koding(vector <char> t, char alf[], int k, vector <char>* t1)
{
    for (int i = 0; i < t.size(); i++)
    {
        if (t[i] >= 'А' && t[i] <= 'Я')
        {
            for (int j = 0; j < 32; j++)
            {
                if (t[i] == alf[j])
                {
                    (*t1).push_back(alf[(j + k) % 32]);
                }
            }
        }
        else
        {
            (*t1).push_back(t[i]);
        }
    }

}


void dekoding(vector <char> t, char alf[], int k, vector <char>* t1)
{
    for (int i = 0; i < t.size(); i++)
    {
        if (t[i] >= 'А' && t[i] <= 'Я')
        {
            for (int j = 0; j < 32; j++)
            {
                if (t[i] == alf[j])
                {
                    (*t1).push_back(alf[(j - k + 32) % 32]);
                }
            }
        }
        else
        {
            (*t1).push_back(t[i]);
        }
    }

}

void analisis(vector <char> t, int* count1)
{
    int count[256]{};
    list<Sym> initList = *new list<Sym>();

    for (int i = 0; i < t.size(); i++)
    {
        count[static_cast<int>(t[i]) + 128]++;
    }

    for (int i = -64 + 128; i < -32 + 128; i++)
    {
        count1[i + 64 - 128] += count[i] + count[i + 32];
    }

}

void printAndOut(ofstream &_fout, string text) {
    _fout << text;
    cout << text;
}

int main()
{
    setlocale(LC_ALL, "ru");

    const string PATH = "D:\\СИБСТРИН ИНФА\\семестр6\\2324, Теория информации, данные, знания, 12 (экзамен, заоч. (5, 6 сем.) (310а-з, 310з гр.) )\\Лабораторная работа №3\\";
    const string INPUT = "7.txt";

    string pathin = PATH + INPUT; // "input.txt";
    string pathout = PATH + INPUT + "_output.txt";

    ifstream fin;
    ofstream fout;

    fin.open(pathin);
    fout.open(pathout);

    printAndOut(fout, "Тема: Программа кодирования/раскодирования сообщений шифром Цезаря\n");
    printAndOut(fout, "Выполнил: студент группы 310з Ларионов Никита Юрьевич\n");
    printAndOut(fout, "Проверил: доцент кафедры ИСТ, к.т.н.Чапаева Светлана Геннадьевна\n");

    vector <char> t;

    char ch;

    while (fin.get(ch))
    {
        t.push_back(ch);
    }

    char alf[32] = {};

    for (int i = 0; i < 32; i++)
    {
        alf[i] = char(int('А') + i);
    }

    int count1[32]{};
    analisis(t, count1);

    float sumSymbols = 0;

    for (int i = 0; i < 32; i++)
    {
        sumSymbols += count1[i];
    }


    list<Sym> initList = *new list<Sym>();
    for (int i = 0; i < 32; i++)
    {
        initList.push_back(*new Sym(static_cast<char>(i - 64), count1[i], count1[i] / sumSymbols));
        //cout << static_cast<char>(i - 64) << \
        //    " " << count1[i] << endl;
    }

    initList.sort([](const Sym& a, const Sym& b) { return a.count < b.count; }); //Сортировка по количеству символа
    initList.reverse();

    cout << "Символ" << std::setw(14) << "Количество" << " " << "Частота" << endl;
    for (std::list<Sym>::iterator it = initList.begin(); it != initList.end(); ++it) {
        cout << it->symbol << std::setw(10) << it->count << std::setw(12) << it->frequency << std::setw(6) << endl;
    }

    cout << "Введите величину сдвига ";
    int k;
    cin >> k;

    printAndOut(fout, "Величина сдвига: k= " + to_string(k) + "\n");
    printAndOut(fout, "Закодированный текст:\n");

    for (int i = 0; i < t.size(); i++)
    {
        cout << t[i];
        fout << t[i];
    }

    //cout << "Кодируем(1) или декодируем(2)? ";
    //int f;
    //cin >> f;

    vector <char> t1;

    //if (f==1) koding(t, alf, k, &t1);
    //else dekoding(t, alf, k, &t1);

    dekoding(t, alf, k, &t1);
    printAndOut(fout, "Раскодированный текст:\n");

    for (int i = 0; i < t1.size(); i++)
    {
        cout << t1[i];
        fout << t1[i];
    }
}

