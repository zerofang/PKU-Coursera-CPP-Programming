#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int WARRIOR_NUM = 5;
const int WEAPON_NUM = 3;

class Headquarter;
class Warrior{
    // private:
    //     Headquarter * headquarter;
    //     int kindNo;
    //     int no;
    public:
        static string names[WARRIOR_NUM];
        static int lifeValues[WARRIOR_NUM];
        static string weapons[WEAPON_NUM];
        //Warrior(Headquarter *hq, int kindNo_, int no_);
};

class Headquarter{
    private:
        int totalLife;
        bool stopped;
        int totalWarriorNum;
        int count;
        int warriorNum[WARRIOR_NUM];
        int color;
        bool canmake[WARRIOR_NUM];

    public:
        static int makingseq[2][WARRIOR_NUM];
        Headquarter(int tl, int color_);
        void produce(int time);
        string getColor();
        bool isStopped();
        bool canMake();
};

string Warrior::names[WARRIOR_NUM] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::lifeValues[WARRIOR_NUM];
string Warrior::weapons[WEAPON_NUM] = {"sword", "bomb", "arrow"};
int Headquarter::makingseq[2][WARRIOR_NUM] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};

Headquarter::Headquarter(int tl, int color_){
            totalLife = tl;
            stopped = false;
            color = color_;
            totalWarriorNum = 0;
            count = 0;
            for (int i = 0; i < WARRIOR_NUM; i++) {
                warriorNum[i] = 0;
                canmake[i] = true;
            }
}

string Headquarter::getColor(){
    if (color == 0)
        return "red";
    return "blue";
}

bool Headquarter::isStopped(){
    return stopped;
}

bool Headquarter::canMake(){
    for (int i = 0; i < WARRIOR_NUM; i++) {
        if (canmake[i]==true){
            return true;
        }
    }
    return false;
}

void Headquarter::produce(int time){
    if (stopped) {
        return;
    }
    string myColor = getColor();
    int index = makingseq[color][count % 5];
    int lifeValue = Warrior::lifeValues[index];
    string name = Warrior::names[index];
    if (totalLife < lifeValue){
        if (!canMake()){
            stopped = true;
            printf("%03d ", time);
            cout << myColor << " headquarter stops making warriors" << endl;
            return;
        }
        count++;
        canmake[index] = false;
        produce(time);
        return;
    }
    totalLife -= lifeValue;
    warriorNum[index]++;
    totalWarriorNum++;
    count++;
    printf("%03d ", time);
    cout << myColor << " " << name << " " << totalWarriorNum << " born with strength " << lifeValue << "," << warriorNum[index] << " " << name << " in " << myColor << " headquarter" << endl;
    if (index == 0) {
        cout << "It has a " << Warrior::weapons[totalWarriorNum % 3] << ",and it's morale is ";
        printf("%.2f\n", (totalLife + 0.0) / lifeValue);
    } else if (index == 1) {
        cout << "It has a " << Warrior::weapons[totalWarriorNum % 3] << " and a " << Warrior::weapons[(totalWarriorNum + 1) % 3] << endl;
    } else if (index == 2) {
        cout << "It has a " << Warrior::weapons[totalWarriorNum % 3] << endl;
    } else if (index == 3) {
        cout << "It's loyalty is " << totalLife << endl;
    }
}

int main() {
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> m;
        Headquarter red(m, 0);
        Headquarter blue(m, 1);
        for (int j = 0; j < WARRIOR_NUM; j++) {
            cin >> Warrior::lifeValues[j];
        }
        cout << "Case:" << i << endl;
        int t = 0;
        while(!(red.isStopped()&&blue.isStopped())){
            red.produce(t);
            blue.produce(t);
            t++;
        }
    }
    return 0;
}

