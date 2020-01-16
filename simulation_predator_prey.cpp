#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

const string ANT = "ant";
const string DOODLEBUG = "doodlebug";
const int DEFAULT_WIDTH = 20;
const int DEFAULT_BUG_COUNT = 5;
const int DEFAULT_ANT_COUNT = 100;

class Organism;
class Ant;
class Doodlebug;
class Garden;

struct Coord{
    int row;
    int col;
    Coord(int row=-1, int col=-1){
        this->row = row;
        this->col = col;
    }
    friend ostream& operator<<(ostream& outs, const Coord& c);
};
ostream& operator<<(ostream& outs, const Coord& c){
    outs << "(" << c.row << "," << c.col << ")";
    return outs;
}

class Organism{
private:
    string type;
    Coord coords;
    Garden* garden;
    int counterBreed;


public:

    Organism(string type, Coord coords, Garden* garden=nullptr ){
        this->garden = garden;
        counterBreed = 0;
        this->coords = coords;
        this->type = type;
    }

    int getCounterBreed() const {
        return counterBreed;
    }

    void incrementCounterBreed() {
        counterBreed++;
    }
    void clearCounterBreed() {
        counterBreed = 0;
    }

    const Coord &getCoords() const {
        return coords;
    }

    void setCoords(const Coord &coords) {
        this->coords = coords;
    }

    Garden* getGarden(){
        return this->garden;
    }

    const string &getType() const {
        return type;
    }

    virtual void move() = 0;

    int generateRandDirection(){
        int direction = rand() % 4;
        return direction;
    }

    Coord getTargetSquare(int direction){

        // Encoding {0,1,2,3} as {Up, Right, Down, Left} respectively
        int r = this->getCoords().row;
        int c = this->getCoords().col;
        switch (direction){
            // Up
            case 0:
                return Coord(r-1, c);
            // Right
            case 1:
                return Coord(r,c+1);
            // Down
            case 2:
                return Coord(r+1,c);
            // Left
            case 3:
                return Coord(r, c-1);
            default:
                return Coord(r,c);

        }
    }

    friend ostream& operator<<(ostream& outs, const Organism& o){
        return o.print(outs);
    }
    virtual ostream& print(ostream& outs) const = 0;

protected:
    vector<int> getEmptyAdjacent();
};


class Ant : public Organism{
public:
    Ant(Coord coords, Garden* garden, string type=ANT) : Organism(type, coords, garden){
    };
    ~Ant();
    void move();
    void breed();
    virtual ostream& print(ostream& outs) const override{
        outs << 'O';
        return outs;
    }

};

class Doodlebug : public Organism{
private:
    int counterStarve;
public:
    Doodlebug(Coord coords, Garden* garden, string type=DOODLEBUG) : Organism(type, coords, garden){
        counterStarve = 0;
    };
    void move();
    void breed();
    void starve();
    virtual ostream& print(ostream& outs) const override{
        outs << 'X';
        return outs;
    }

    int getCounterStarve() const {
        return counterStarve;
    }

    void incrementCounterStarve() {
        counterStarve++;
    }
    void clearCounterStarve() {
        counterStarve = 0;
    }
    ~Doodlebug();
};


class Garden{
private:
    int width;
    int nBugs;
    int nAnts;
    int steps;
    vector<Ant*> antList;
    vector<Doodlebug*> doodlebugList;
    vector<vector<Organism*>> board;

public:
    const vector<Ant *> &getAntList() const {
        return antList;
    }

    void deleteFromAntListByInd(const int i) {
        antList.erase(antList.begin() + i);
    }

    const vector<Doodlebug *> &getDoodlebugList() const {
        return doodlebugList;
    }

    void deleteFromDoodlebugListByInd(const int i) {
        doodlebugList.erase(doodlebugList.begin() + i);
    }

    Garden(int width=DEFAULT_WIDTH, int nBugs=DEFAULT_BUG_COUNT, int nAnts=DEFAULT_ANT_COUNT){
        this->nBugs = nBugs;
        this->nAnts = nAnts;
        this->width = width;
        steps = 0;
        board.resize(width);
        for(int i = 0; i < width; i++){
            board[i].resize(width);
        }

        // Fill board with null pointers
        for(int i = 0; i < width; i++){
            for(int j = 0; j < width; j++){
                board[i][j] = nullptr;
            }
        }

        // Select random squares to place bugs and ants
        vector<int> numberList;
        int n = width*width;
        for(int i =0; i<n; i++){
            numberList.push_back(i);
        }
        vector<int> randomList;
        for(int i = 0; i < nBugs+nAnts; i++){
            int ind = rand() % n;
            randomList.push_back(numberList[ind]);
            numberList.erase(numberList.begin()+ind);
            n--;
        }

        // Place the bugs
        for(int i =0; i < nBugs; i++){
            Coord c = coordFromInt(randomList[i]);
            this->newDoodlebug(c);
        }

        // Place the ants
        for(int i =nBugs; i < nBugs+nAnts; i++){
            Coord c = coordFromInt(randomList[i]);
            this->newAnt(c);
        }

    }
    Coord coordFromInt(int a){
        int x = a / width;
        int y = a % width;
        return Coord(x,y);
    }
    void printBoard(){
        for(int i = 0; i < width; i++){
            for (int j =0; j < width; j++){
                Organism * square = board[i][j];
                cout << '|';
                if(square == nullptr){
                    cout << " " ;
                }
                else{
                    cout << *square ;
                }
            }
            cout << '|' << endl;

        }
    }
    Organism* getSquare(Coord c){
        return board[c.row][c.col];
    }
    void setSquare(Coord c, Organism* o){
        board[c.row][c.col] = o;
    }

    bool isInGarden(Coord coord){
        if(coord.row >=0 && coord.row < this->width){
            return (coord.col >=0 && coord.col < this->width);
        }
        return false;
    }
    bool isEmpty(Coord coord){
        if(isInGarden(coord)){
            return !getSquare(coord);
        }
        else{
            return false;
        }
    }

    bool hasAnt(Coord c){
        if(isInGarden(c)){
            return !isEmpty(c) && (getSquare(c)->getType() == ANT);
        }
        else{
            return false;
        }
    }

    void newAnt(Coord c){
        Ant* a = new Ant(c,this);
        antList.push_back(a);
        board[c.row][c.col] = a;
    }
    void newDoodlebug(Coord c){
        Doodlebug* d = new Doodlebug(c,this);
        doodlebugList.push_back(d);
        board[c.row][c.col] = d;
    }

    void runStep(){

        vector<Doodlebug*> dl = doodlebugList;

        //DOODLEBUGS - move
        for(vector<Doodlebug*>::iterator it = dl.begin(); it != dl.end();){
            Doodlebug* dbug = *it;
            dbug->move();
            // Starve
            if(dbug->getCounterStarve() == 3){
                // Starve
                dbug->starve();
                it = dl.erase(it);
                continue;
            }
            // Breed
            else if(dbug->getCounterBreed() >=8){
                dbug->breed();

            }
            it++;
        }
        vector<Ant*> al = antList;

        //ANTS - move
        for(vector<Ant*>::iterator it = al.begin(); it != al.end();){
            Ant* ant = *it;
            ant->move();
            // Breed
            if(ant->getCounterBreed() >= 3){
                ant-> breed();
            }
            it++;
        }
    }

    bool userContinue(){
        char inp;
        cout << endl << "Continue simulation? (Y/N)";
        cin >> inp;
        cout << endl;
        return (inp == 'y' || inp == 'Y');

    }
};
vector<int> Organism::getEmptyAdjacent(){
    vector<int> emptyAdjacent;
    Garden * g = this->getGarden();
    for (int dir = 0; dir < 4; dir++){
        Coord target = this->getTargetSquare(dir);

        if(g->isEmpty(target)){
            emptyAdjacent.push_back(dir);
        }
    }
    return emptyAdjacent;
}

void Ant::move(){
    int dir = this->generateRandDirection();
    Coord target = this->getTargetSquare(dir);
    Garden * g = this->getGarden();

    if (g->isEmpty(target)){
        Coord currentCoords = this->getCoords();
        this->setCoords(target);
        g->setSquare(target,this);
        g->setSquare(currentCoords,nullptr);
    }
    this->incrementCounterBreed();
}

void Ant::breed(){
    vector<int> emptyAdj = getEmptyAdjacent();
    if(emptyAdj.size() > 0){
        int randInd = rand() % emptyAdj.size();
        Coord target = this->getTargetSquare(emptyAdj[randInd]);
        this->getGarden()->newAnt(target);
        this->clearCounterBreed();
    }
}

void Doodlebug::move(){
    vector<int> antAdjacent;
    Garden * g = this->getGarden();

    // Look for adjacent ants
    for (int dir = 0; dir < 4; dir++) {
        Coord target = this->getTargetSquare(dir);

        if (g->hasAnt(target)) {
            antAdjacent.push_back(dir);
        }
    }
    if(antAdjacent.size() > 0){
        // Choose a random adjacent ant and eat it
        int randInd = rand() % antAdjacent.size();
        Coord newSquare = this->getTargetSquare(antAdjacent[randInd]);
        Ant* ant = (Ant*)(g->getSquare(newSquare));
        delete ant;

        // Put this dooodlebug in that spot
        Coord currentCoords = this->getCoords();
        this->setCoords(newSquare);
        g->setSquare(newSquare,this);
        g->setSquare(currentCoords,nullptr);

    }
    else{
        int dir = this->generateRandDirection();
        Coord target = this->getTargetSquare(dir);

        if (g->isEmpty(target)){
            Coord currentCoords = this->getCoords();
            this->setCoords(target);
            g->setSquare(target,this);
            g->setSquare(currentCoords,nullptr);
        }
        this->incrementCounterStarve();
    }
    this->incrementCounterBreed();
    }

void Doodlebug::breed(){
    vector<int> emptyAdj = getEmptyAdjacent();
    if(emptyAdj.size() > 0){
        int randInd = rand() % emptyAdj.size();
        Coord target = this->getTargetSquare(emptyAdj[randInd]);
        this->getGarden()->newDoodlebug(target);
        this->clearCounterBreed();
    }
}

void Doodlebug::starve(){
    delete this;
}

Doodlebug::~Doodlebug(){
    Garden * g = this->getGarden();

    //Remove from Doodlebug List
    vector<Doodlebug*>::iterator it;
    vector<Doodlebug*> dl = g->getDoodlebugList();
    it = find(dl.begin(), dl.end(), this);
    if (it != dl.end())
    {
        int ind = it - dl.begin();
        g->deleteFromDoodlebugListByInd(ind);
    }

    //Remove from Board
    g->setSquare(this->getCoords(),nullptr);

}
Ant::~Ant(){
    Garden * g = this->getGarden();

    //Remove from Ant list
    vector<Ant*>::iterator it;
    vector<Ant*> al = g->getAntList();
    it = find(al.begin(), al.end(), this);
    if (it != al.end()){
        int ind = it - al.begin();
        g->deleteFromAntListByInd(ind);
    }
    // Remove from board
    g->setSquare(this->getCoords(),nullptr);
}

int main() {
    srand(time(NULL));
    cout << endl;
    Garden g; //Default values, width:20, dbugs:5, ants:200
    g.printBoard();

    while(g.userContinue()){
        g.runStep();
        g.printBoard();
    }
    return 0;
}
