#include <iostream>
#include <cstdio>
#include <string.h>
#include <vector>
using namespace std;

const int WARRIOR_NUM = 5;
const int WEAPON_NUM = 3;
const int CITY_LIFE = 10;
const int MAX_LIFE = 10000000;
const int RED_WARRIOR = 0;
const int BLUE_WARRIOR = 1;

class Weapon;
class Warrior;
class City{
    private:
        int no;
        int nLifeValue;
        int flag = -1;
        int lastWinner = -1;
        Warrior *warriors[2];

    public:
        City(int no_, int nLifeValue_) : no(no_), nLifeValue(nLifeValue_) {
            warriors[0] = NULL;
            warriors[1] = NULL;
        }

        void addLife(int nLifeValue_ = CITY_LIFE) {
            nLifeValue += nLifeValue_;
        }

        void takeLife(int life_) {
            nLifeValue -= life_;
        }

        int takeAllLife() {
            int temp = nLifeValue;
            nLifeValue = 0;
            return temp;
        }

        int getOffensive() {
            if (flag != -1) {
                return flag;
            }
            if (no % 2 == 0) {
                return BLUE_WARRIOR;
            } else {
                return RED_WARRIOR;
            }
        }

        void changeFlag(const int time, const int h) {
            if (h != -1 && lastWinner == h)
            {
                flag = h;
                if (flag == RED_WARRIOR) {
                    printf("%.3d:40 red flag raised in city %d\n", time, no);
                } else {
                    printf("%.3d:40 blue flag raised in city %d\n", time, no);
                }
            }
            lastWinner = h;
        }

        ~City() {
            delete[] &warriors;
        }

        static int red;
        static int blue;
        static int redCount;
        static int blueCount;
        static int M;
        static int N;
        static vector<City*> cities;
        static int makingSeq[2][WARRIOR_NUM];

        static int getWIndex(int color_) {
            if (color_ == red) {
                return RED_WARRIOR;
            } else if (color_ == blue) {
                return BLUE_WARRIOR;
            } else {
                return -1;
            }
        }

        static string getHeadName(int color_) {
            if (color_ == red) {
                return "red";
            } else if (color_ == blue) {
                return "blue";
            } else {
                return "error";
            }
        }

        static int getOpponent(int color_) {
            if (color_ == red) {
                return blue;
            } else if (color_ == blue){
                return red;
            } else {
                return -1;
            }
        }

        static int getCount(int color) {
            if (color == red) {
                return redCount;
            } else if (color == blue) {
                return blueCount;
            } else {
                return -1;
            }
        }

        static void addCount(int color) {
            if (color == red) {
                redCount++;
            } else if (color == blue) {
                blueCount++;
            } else {
                return;
            }
        }

        static int leftLife(int color) {
            return cities[color]->nLifeValue;
        }

        static void initCities() {
            clearCities();
            red = 0;
            blue = N+1;
            redCount = 0;
            blueCount = 0;
            cities.push_back(new City(red, M));
            for (int i = 1; i <= N; i++) {
                cities.push_back(new City(i, 0));
            }
            cities.push_back(new City(blue, M));
        }

        static void clearCities() {
            if (cities.size() == 0) {
                return;
            }
            for (int i = 0; i <= N + 1; i++) {
                delete &cities[i];
            }
            vector<City *> temp;
            cities.swap(temp); 
        }

        static void produce(int color, int time);
        static void warriorsBorn(int time);
        static void lionsEscape(int time);
        static bool march(int time);
        static void produceLifeValue(int time);
        static void takeLifeValue(int time);
        static void useArrow(int time);
        static void useBomb(int time);
        static void fight(int time);
        static void HQreport(int time);
        static void warriorsReport(int time);
        static void clearBodies();
};

class Weapon{
    protected:
        int type;
        int nAttack;
        int nLife;
    public:
        static string weaponName[WEAPON_NUM];
        static int arrowR;
        int getATK() {
            return nAttack;
        }
        int getLife() {
            return nLife;
        }
        void setATK(int nAttack_){
            nAttack = nAttack_;
        }
        bool isWearOut() {
            return nAttack <= 0 && nLife <= 0;
        }
        virtual void isUsed() = 0;
};

class Sword : public Weapon {
    public:
        Sword(int nAttack_ = 0){
            type = 0;
            nAttack = nAttack_;
            nLife = nAttack;
        }
        void isUsed() {
            nAttack = nAttack * 8 / 10;
            nLife = nAttack;
        }
};

class Bomp : public Weapon {
    public:
        Bomp(){
            type = 1;
            nAttack = MAX_LIFE;
            nLife = 1;
        }
        void isUsed() {
            nLife--;
        }
};

class Arrow : public Weapon {
    public:
        Arrow(){
            type = 2;
            nAttack = arrowR;
            nLife = 3;
        }
        void isUsed() {
            nLife--;
        }
};

Weapon* getWeaponByType(const int type, const int nAttack_ = 0) {
    switch (type) {
        case 0:
            return new Sword(nAttack_);
        case 1:
            return new Bomp();
        case 2:
            return new Arrow();
        default:
            return NULL;
    }
}

class Warrior{
    protected:
        int color;
        int type;
        int no;
        int pos;
        string name;
        string headName;
        int nLifeValue;
        int nAttack;
        Weapon *weapons[WEAPON_NUM] = {NULL};

    public:
        static string warriorName[WARRIOR_NUM];
        static int initialATK[WARRIOR_NUM];
        static int initialLife[WARRIOR_NUM];

        static Warrior *initWarrior(const int color_, const int type_, const int no_);

        Warrior(const int color_, const int type_, const int no_) {
            color = color_;
            type = type_;
            no = no_;
            pos = color_;
            nLifeValue = initialLife[type_];
            nAttack = initialATK[type_];
            name = warriorName[type_];
            headName = City::getHeadName(color_);
            for (int i = 0; i < WEAPON_NUM; i++) {
                weapons[i] = NULL;
            }
            printf("%s %s %d born\n", headName.c_str(), name.c_str(), no);
        }

        void addLife(int value) {
            nLifeValue += value;
        }

        bool isDead() {
            return nLifeValue <= 0;
        }

        Weapon* getWeapons() {
            return *weapons;
        }

        void reportWeapons(int time = 0) {
            printf("%.3d:55 %s %s %d has ", time, headName.c_str(), name.c_str(), no);
            bool flag = false;
            for (int i = 2; i >= 0; i--) {
                if (weapons[i] != NULL) {
                    if (flag) {
                        printf(",");
                    }
                    flag = true;
                    printf("%s(%d)", Weapon::weaponName[i].c_str(), weapons[i]->getLife());
                }
            }
            if (!flag) {
                printf("no weapon");
            }
            printf("\n");
        }

        void shootArrow(Warrior &w, int time = 0);
        void throwBomb(Warrior &w, int time = 0);
        int getHit(bool isOffense);
        void attack(Warrior &w, int time = 0);
        void fightBack(Warrior &w, int time = 0);
        void Hurted(int hit);
        virtual void afterFight(Warrior &w, int time = 0) {
            return;
        }
        virtual int walk(int time = 0) {
            if (pos == City::getOpponent(color))
            {
                return pos;
            }
            if (color == City::red)
            {
                pos += 1;
            }
            else
            {
                pos -= 1;
            }
            return pos;
        }

        virtual void specialAction(const int time){
            return;
        }

        void isKilled(const int time) {
            printf("%.3d:40 %s %s %d was killed in city %d\n", time, headName.c_str(), name.c_str(), no , pos);
        }

        void takeLifeValue(const int value, const int time) {
            City::cities[color]->addLife(value);
            printf("%.3d:30 %s %s %d earned %d elements for his headquarter\n", time, headName.c_str(), name.c_str(), no , value);
        }

        friend class City;
        ~Warrior(){
            delete[] &weapons;
        }
};

void Warrior::shootArrow(Warrior &w, int time) {
    if (weapons[2] == NULL) {
        return;
    }
    int hit = weapons[2]->getATK();
    w.Hurted(hit);
    printf("%.3d:35 %s %s %d shot", time, headName.c_str(), name.c_str() , no);
    if (w.isDead()) {
        printf(" and killed %s %s %d", w.headName.c_str(), w.name.c_str(), w.no);
    }
    printf("\n");
}

void Warrior::throwBomb(Warrior &w, int time) {
    if (weapons[1] == NULL) {
        return;
    }
    int hit = weapons[1]->getATK();
    Hurted(hit);
    w.Hurted(hit);
    printf("%.3d:38 %s %s %d used a bomb and killed %s %s %d\n", time, headName.c_str(), name.c_str(), no, w.headName.c_str(), w.name.c_str(), w.no);
}

int Warrior::getHit(bool isOffense) {
    int hit = 0;
    if (isOffense) {
        hit = nAttack;
    } else {
        hit = nAttack / 2;
    }
    if (weapons[0] != NULL) {
        hit += weapons[0]->getATK();
        weapons[0]->isUsed();
        if (weapons[0]->isWearOut()) {
            delete &weapons[0];
            weapons[0] = NULL;
        }
    }
    return hit;
}

void Warrior::attack(Warrior &w, int time) {
    printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", time, headName.c_str(), name.c_str(), no, w.headName.c_str(), w.name.c_str(), w.no, pos, nLifeValue, nAttack);
    int hit = getHit(true);
    int temp = w.nLifeValue;
    w.Hurted(hit);
    if (!(w.isDead() || w.type == 1)) {
        w.fightBack(*this);
    }
    if (w.isDead() && w.type == 3) {
        addLife(temp);
    }
}

void Warrior::fightBack(Warrior &w, int time) {
    printf("%.3d:40 %s %s %d fought back against %s %s %d in city %d\n", time, headName.c_str(), name.c_str(), no, w.headName.c_str(), w.name.c_str(), w.no, pos);
    int hit = getHit(false);
    w.Hurted(hit);
}

void Warrior::Hurted(int hit = 0) {
    nLifeValue = nLifeValue > hit ? nLifeValue - hit : 0;
}

class Dragon : public Warrior{
    private:
        double morale;

    public:
        Dragon(const int color_, const int type_, const int no_):Warrior(color_, type_, no_) {
            weapons[no % 3] = getWeaponByType(no % 3, nLifeValue * 2 / 10);
            morale = (City::leftLife(color_) + 0.0) / initialLife[type_];
            printf("Its morale is %.2lf\n", morale);
        }
        void afterFight(Warrior &w, int time = 0) {
            if (w.isDead()) {
                morale += 0.2;
            } else {
                morale -= 0.2;
            }
        }

        void specialAction(const int time) {
            if (nLifeValue > 0 && morale > 0.8) {
                printf("%.3d:40 %s dragon %d yelled in city %d\n", time, headName.c_str(), no , pos);
            }
        }
};

class Ninja : public Warrior{
    public:
        Ninja(const int color_, const int type_, const int no_):Warrior(color_, type_, no_) {
            weapons[no % 3] = getWeaponByType(no % 3, nLifeValue * 2 / 10);
            weapons[(no+1) % 3] = getWeaponByType((no+1) % 3, nLifeValue * 2 / 10);
        }
};

class Iceman : public Warrior{
    public:
        Iceman(const int color_, const int type_, const int no_):Warrior(color_, type_, no_) {
            weapons[no % 3] = getWeaponByType(no % 3, nLifeValue * 2 / 10);
        }
        int walk(int time = 0){
            int opp = City::getOpponent(color);
            if (pos == opp)
            {
                return pos;
            }
            if (color == City::red)
            {
                int temp = pos + 2;
                pos  = temp > opp ? opp : temp;
            }
            else
            {
                int temp = pos - 2;
                pos = temp < opp ? opp : temp;
            }
            if (nLifeValue - 9 > 0) {
                nLifeValue -= 9;
                nAttack += 20;
            } else {
                nLifeValue = 1;
            }
            return pos;
        }
};

class Lion : public Warrior{
    private:
        int loyalty;

    public:
        static int K;
        Lion(const int color_, const int type_, const int no_) : Warrior(color_, type_, no_){
            loyalty = City::leftLife(color);
            printf("Its loyalty is %d\n", loyalty);
        }
        void afterFight(Warrior &w, int time = 0) {
            if (!w.isDead()) {
                loyalty -= K;
            }
        }

        void specialAction(const int time){
            if (loyalty <= 0) {
                nLifeValue = 0;
                printf("%.3d:05 %s lion %d run away\n", time, headName.c_str(), no);
            }
        }
};

class Wolf : public Warrior{
    public:
        Wolf(const int color_, const int type_, const int no_) : Warrior(color_, type_, no_){};
        void afterFight(Warrior &w, int time = 0) {
            if (w.isDead()) {
                Weapon *tempw = w.getWeapons();
                for (int i = 0; i < WEAPON_NUM; i++) {
                    if (weapons[i] == NULL) {
                        weapons[i] = &tempw[i];
                    }
                }
            }
        }
};



string Warrior::warriorName[WARRIOR_NUM] = {"dragon", "ninja", "iceman", "lion", "wolf"};
int Warrior::initialATK[WARRIOR_NUM];
int Warrior::initialLife[WARRIOR_NUM];
int Lion::K;
string Weapon::weaponName[WEAPON_NUM] = {"sword", "bomb", "arrow"};
int Weapon::arrowR;
int City::red;
int City::blue;
vector<City*> City::cities;
int City::redCount;
int City::blueCount;
int City::M;
int City::N;
int City::makingSeq[2][WARRIOR_NUM] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};

Warrior* Warrior::initWarrior(const int color_, const int type_, const int no_) {
    switch (type_) {
    case 0:
        return new Dragon(color_, type_, no_);
    case 1:
        return new Ninja(color_, type_, no_);
    case 2:
        return new Iceman(color_, type_, no_);
    case 3:
        return new Lion(color_, type_, no_);
    case 4:
        return new Wolf(color_, type_, no_);
    default:
        return NULL;
    }

}

void City::produce(int color, int time) {
    int count = getCount(color);
    int totalLife = leftLife(color);
    int w = color == red ? RED_WARRIOR : BLUE_WARRIOR;
    int index = makingSeq[w][count% 5];
    int lifeValue = Warrior::initialLife[index];
    string name = Warrior::warriorName[index];
    if (totalLife < lifeValue)
    {
        return;
    }
    cities[color]->takeLife(lifeValue);
    addCount(color);
    printf("%.3d:00 ", time);
    cities[color]->warriors[w] = Warrior::initWarrior(color, index, ++count);
}

void City::warriorsBorn(int time){
     produce(red, time);
     produce(blue, time);
}
void City::lionsEscape(int time){
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= 1; j++) {
            if (cities[i]->warriors[j]!=NULL) {
                cities[i]->warriors[j]->specialAction(time);
            }
        }
    }
}
bool City::march(int time) {
    bool takenRed = false;
    bool takenBlue = false;
    for (int i = N; i >= 0; i--) {
        if (cities[i]->warriors[0] != NULL)
        {
            int newPos = cities[i]->warriors[0]->walk(time);
            if (cities[newPos]->warriors[0] != NULL) {
                if (newPos == red) {
                    takenRed = true;
                } else if (newPos == blue) {
                    takenBlue = true;
                } else {
                    printf("error\n");
                    return true;
                }
            }
            cities[newPos]->warriors[0] = cities[i]->warriors[0];
            cities[i]->warriors[0] = NULL;
        }
    }
    for (int i = 1; i <= N +1; i++) {
        if (cities[i]->warriors[1] != NULL)
        {
            int newPos = cities[i]->warriors[1]->walk(time);
            if (cities[newPos]->warriors[1] != NULL) {
                if (newPos == red) {
                    takenRed = true;
                } else if (newPos == blue) {
                    takenBlue = true;
                } else {
                    printf("error\n");
                    return true;
                }
            }
            cities[newPos]->warriors[1] = cities[i]->warriors[1];
            cities[i]->warriors[1] = NULL;
        }
    }
    for (int i = 0; i <= N+1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (cities[i]->warriors[j] == NULL) {
                continue;
            }
            Warrior *w = cities[i]->warriors[j];
            int opp = getOpponent(w->color);
            if (w->pos == opp)
            {
                printf("%.3d:10 %s %s %d reached %s headquarter with %d elements and force %d\n", time, w->headName.c_str(), w->name.c_str(), w->no, City::getHeadName(opp).c_str(), w->nLifeValue, w->nAttack);
            }
            else
            {
                printf("%.3d:10 %s %s %d marched to city %d with %d elements and force %d\n", time, w->headName.c_str(), w->name.c_str(), w->no, w->pos, w->nLifeValue, w->nAttack);
            }
        }
    }
    if (takenRed) {
        printf("%.3d:10 red headquarter was taken\n", time);
    }
    if (takenBlue) {
        printf("%.3d:10 blue headquarter was taken\n", time);
    }
    return (takenBlue || takenRed);
}
void City::produceLifeValue(int time){
    for (int i = 1; i <= N; i++) {
        cities[i]->addLife();
    }
}
void City::takeLifeValue(int time){
    for (int i = 1; i <= N; i++) {
        if (cities[i]->warriors[RED_WARRIOR]!=NULL && cities[i]->warriors[BLUE_WARRIOR]==NULL) {
            cities[i]->warriors[RED_WARRIOR]->takeLifeValue(cities[i]->takeAllLife(), time);
        }
        if (cities[i]->warriors[RED_WARRIOR]==NULL && cities[i]->warriors[BLUE_WARRIOR]!=NULL) {
            cities[i]->warriors[BLUE_WARRIOR]->takeLifeValue(cities[i]->takeAllLife(), time);
        }
    }
}
void City::useArrow(int time) {
    for (int i = 1; i < N; i++) {
        if (cities[i]->warriors[RED_WARRIOR] != NULL && cities[i+1]->warriors[BLUE_WARRIOR] != NULL) {
            cities[i]->warriors[RED_WARRIOR]->shootArrow(*(cities[i + 1]->warriors[BLUE_WARRIOR]), time);
        }
    }
    for (int i = N; i > 1; i--) {
        if (cities[i]->warriors[BLUE_WARRIOR] != NULL && cities[i+1]->warriors[RED_WARRIOR] != NULL) {
            cities[i]->warriors[BLUE_WARRIOR]->shootArrow(*(cities[i + 1]->warriors[RED_WARRIOR]), time);
        }
    }
}
void City::useBomb(int time){
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= 1; j++) {
            int opp = j == 0 ? 1 : 0;
            if (cities[i]->warriors[j]!=NULL && cities[i]->warriors[opp]!=NULL && cities[i]->warriors[j]->weapons[1] != NULL) {
                if (cities[i]->warriors[j]->isDead() || cities[i]->warriors[opp]->isDead()) {
                    continue;
                }
                int hit = 0;
                if(cities[i]->getOffensive() == opp) {
                    hit = cities[i]->warriors[opp]->getHit(true);
                } else {
                    hit = cities[i]->warriors[opp]->getHit(false);
                }
                if (hit >= cities[i]->warriors[j]->nLifeValue) {
                    cities[i]->warriors[j]->throwBomb(*(cities[i]->warriors[opp]), time);
                }
            }
        }
    }
}
void City::fight(int time){
    for (int i = 1; i <= N; i++) {
        if (cities[i]->warriors[0]!=NULL && cities[i]->warriors[1]!=NULL) {
            if (cities[i]->warriors[0]->isDead() && cities[i]->warriors[1]->isDead()) {
                continue;
            }
            int offensive = cities[i]->getOffensive();
            int defense = offensive == 0 ? 1 : 0;
            for (int j = 0; j <= 1; j++) {
                int opp = j == 0 ? 1 : 0;
                if (cities[i]->warriors[j]->isDead())
                {
                    cities[i]->warriors[opp]->afterFight(*cities[i]->warriors[j], time);
                    if (cities[i]->warriors[opp]->type == 0 && offensive == opp)
                    {
                        cities[i]->warriors[opp]->specialAction(time);
                    }
                    cities[i]->changeFlag(time, opp);
                }
                continue;
            }
            cities[i]->warriors[offensive]->attack(*cities[i]->warriors[defense], time);
            if (!cities[i]->warriors[defense]->isDead()) {
                cities[i]->warriors[defense]->fightBack(*cities[i]->warriors[offensive], time);
                cities[i]->warriors[defense]->afterFight(*cities[i]->warriors[offensive], time);
                if (cities[i]->warriors[offensive]->isDead()) {
                    cities[i]->warriors[defense]->takeLifeValue(cities[i]->takeAllLife(), time);
                    cities[i]->changeFlag(time, defense);
                } else {
                    cities[i]->changeFlag(time, -1);
                }
            } else {
                cities[i]->warriors[defense]->isKilled(time);
            }
            if (!cities[i]->warriors[offensive]->isDead()) {
                cities[i]->warriors[offensive]->afterFight(*cities[i]->warriors[defense], time);
                if (cities[i]->warriors[defense]->isDead()) {
                    if (cities[i]->warriors[offensive]->type == 0) {
                        cities[i]->warriors[offensive]->specialAction(time);
                    }
                    cities[i]->warriors[offensive]->takeLifeValue(cities[i]->takeAllLife(), time);
                    cities[i]->changeFlag(time, offensive);
                } else {
                    cities[i]->changeFlag(time, -1);
                }
            } else {
                cities[i]->warriors[offensive]->isKilled(time);
            }
            if (cities[i]->warriors[defense]->isDead() && cities[i]->warriors[defense]->isDead()) {
                cities[i]->changeFlag(time, -1);
            }
        }
    }
}
void City::HQreport(int time) {
    printf("%.3d:50 %d elements in red headquarter\n", time, cities[red]->nLifeValue);
    printf("%.3d:50 %d elements in blue headquarter\n", time, cities[blue]->nLifeValue);
}
void City::warriorsReport(int time) {
    for (int i = 0; i <= N+1; i++) {
        if (cities[i]->warriors[0] != NULL) {
            cities[i]->warriors[0]->reportWeapons(time);
        }
    }
    for (int i = 0; i <= N+1; i++) {
        if (cities[i]->warriors[1] != NULL) {
            cities[i]->warriors[1]->reportWeapons(time);
        }
    }
}
void City::clearBodies() {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= 1; j++) {
            if (cities[i]->warriors[j] != NULL && cities[i]->warriors[j]->isDead()) {
                delete &cities[i]->warriors[j];
                cities[i]->warriors[j] = NULL;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int T;
        cin >> City::M >> City::N >> Weapon::arrowR >> Lion::K >> T;
        for (int j = 0; j < WARRIOR_NUM; j++) {
            cin >> Warrior::initialLife[j];
        }
        for (int j = 0; j < WARRIOR_NUM; j++) {
            cin >> Warrior::initialATK[j];
        }
        cout << "Case:" << i << endl;
        int t = 0;
        City::initCities();
        while (t*60 <= T)
        {
            City::warriorsBorn(t);
            if (t*60+5 >  T) {
                break;
            }
            City::lionsEscape(t);
            if (t*60+10 >  T) {
                break;
            }
            bool end = City::march(t);
            if (end || t*60+20 >  T) {
                break;
            }
            City::produceLifeValue(t);
            if (t*60+30 >  T) {
                break;
            }
            City::takeLifeValue(t);
            if (t*60 + 35 > T) {
                break;
            }
            City::useArrow(t);
            if (t*60+38 >  T) {
                break;
            }
            City::useBomb(t);
            if (t*60+40 >  T) {
                break;
            }
            City::fight(t);
            City::clearBodies();
            if (t*60+50 > T) {
                break;
            }
            City::HQreport(t);
            if (t*60+55 > T) {
                break;
            }
            City::warriorsReport(t);
            t++;
        }
    }
    return 0;
}


