#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std; //нужен класс персонажа!!

class Character {
private:
    string name;
    string ans;
public:
    Character(string name, string ans) {
        this -> name = name;
        this -> ans = ans;
    }
    string getName() {
        return this -> name;
    }
    char getAns(unsigned int c) {
        return (this -> ans)[c];
    }
};

class Question {
private:
    unsigned int num;
    string text;
public:
    Question(unsigned int num, string text) {
        this -> num = num;
        this -> text = text;
    }
    string getText() {
        return this -> text;
    }
    unsigned int getNum() {
        return this -> num;
    }
};

//создание вектора Character и Question

void make_questions(vector <Question>& ref_q) { //вернуть ссылку на вектор вопросов
    //Question* q = (Question *)malloc(sizeof(Question)*15);
    //vector <Question> q;
    string s;
    unsigned int i = 0;
    ifstream file("Questions.txt");
    while (getline(file, s)) {
        Question a(i, s);
        //*(q + i) = a;
        ref_q.push_back(a);
        ++i;
    }
    file.close();
    //vector <Question>& ref_q = q;
    //return ref_q;
}

/*vector <string>&*/void read_desk(vector <string>& ref_ans) { //построчно считывает в вектор строки с информацией по вопросам
    ifstream file("Desk.txt");
    //vector <string> ans;
    //vector <string>& ref_ans = ans;
    string s;
    while (getline(file, s)) {
        ref_ans.push_back(s);
    }
    file.close();
    //vector <string>& ref_ans = ans;
    //return ref_ans;
}

void make_characters(vector <string>& ref_ans, vector <Character>& ref_c) { //вернуть ссылку на вектор героев
    //Character* c = (Character *)malloc(sizeof(Character)*16);
    //vector <Character> c;
    unsigned int i = 0;
    ifstream file("Characters.txt");
    string s;
    while (getline(file, s)) {
        Character a(s, ref_ans[i]);
        //*(c + i) = a;
        ref_c.push_back(a);
        ++i;
    }
    file.close();
    //vector <Character>& ref_c = c;
    //return ref_c;
}

Question choose_question(vector <Character>& nes_ch, unsigned int quantity, /*const*/ vector <Question>& ref_q) {//возвращае тнаилучший вопрос, на вход вектор "подходящих" персов и количество вопросов
    double k_max = 0;
    unsigned int num = -1;
    for (unsigned int i = 0; i < quantity; ++i) {
        double yes = 0;
        double no = 0;
        for (unsigned int j = 0; j < nes_ch.size(); ++j) {
                char c = nes_ch[j].getAns(i);
                if (c == '1')
                    yes++;
                else
                    no++;
        }
        /*cout << "yes = " << yes << endl;
        cout << "no = " << no << endl;
        cout <<  (yes + no) / (abs(yes - no) + 1) << endl << endl;*/
        double d = (yes + no) / (abs(yes - no) + 1);
        //cout << d << endl;
        if (d > k_max) {
            k_max = d;
            num = i;
        }
    }
    return ref_q[num];
}

void choose_characters(Question q, vector <Character>& nes_ch) { //отбор персонажей по данному ответом, возвращается их вектор
    cout << q.getText() << endl << "Введите ответ: ";
    string answer;
    unsigned int num = q.getNum();
    char c;
    getline(cin, answer);
    //cout << answer;
    if (answer == "Yes")
        c = '1';
    else {
        if (answer == "No")
            c = '0';
        else
            c = '_';
    }
    //cout << nes_ch.size();
    //vector <Character> help = nes_ch;
    for (int i = nes_ch.size() - 1; i > -1; --i) {
        char s = nes_ch[i].getAns(num);
        if (s != c)
            nes_ch.erase(nes_ch.begin() + i);
    }
    for (int i = 0; i < nes_ch.size(); ++i) {
        cout << nes_ch[i].getName() << endl;
    }
    //return nes_ch;
}
int main()
{
    setlocale(LC_CTYPE, "rus"); //локалка для кириллицы
    //формирование всех исходных данных
    vector <Question> q;
    vector <Question>& ref_q = q;
    make_questions(ref_q); //работает
    /*cout << ref_q.size() << endl << endl;
    for (unsigned int i = 0; i < ref_q.size(); ++i) {
        cout << ref_q[i].getText() << endl;
    }*/
    vector <string> ans;
    vector <string>& ref_ans = ans;
    read_desk(ref_ans); //работает
    /*for (unsigned int i = 0; i < ref_ans.size(); ++i) {
        cout << ref_ans[i] << endl;
    }
    cout << ref_ans.size();*/
    vector <Character> c;
    vector <Character>& ref_c = c;
    make_characters(ref_ans, ref_c); //работает
    /*cout << "c.size() = " << ref_c.size() << endl;
    for (unsigned int i = 0; i < ref_c.size(); ++i) {
        cout << ref_c[i].getName() << endl;
    }*/
    unsigned int quantity = ref_q.size();
    string s;
    while (ref_c.size() > 1) {
        Question w = choose_question(ref_c, quantity, /*const*/ ref_q);
        choose_characters(w, ref_c);
    }
    if (ref_c.size() == 1)
        cout << ref_c[0].getName();
    else
        cout << "ERROR";
    return 0;
}
