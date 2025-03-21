#include <cstdint>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <vector>
#include "tinymines.hpp"

Board::Board(int sizeX, int sizeY, int nMines) {
// Board* createBoard(int sizeX, int sizeY, int nMines) {
    int nSpaces = sizeX * sizeY;
    if(nMines >= nSpaces)
        throw std::range_error("too many mines");

    // init board
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->nMines = nMines;
    this->board = (uint8_t*) malloc(sizeof(uint8_t) * nSpaces);

    // populate mines
    std::set<int> mines;
    // TODO: this is nasty, find a better way
    while (mines.size() < nMines) {
        mines.insert(rand() % nSpaces);
    }
    std::set<int>::iterator m;
    for(m = mines.begin(); m != mines.end(); m++) {
        this->setMine(*m);
    }
}

Board::~Board() {
    free(this->board);
}

uint8_t *Board::getSpace(int x, int y) {
    int i = x * this->sizeX + y;
    return this->getSpace(i);
}

uint8_t *Board::getSpace(int i) {
    return &this->board[i];
}

void Board::setMine(int i) {
    uint8_t *space = this->getSpace(i);
    *space = *space | IS_MINE;
    // increment counts around mine
    std::vector<int> surr = *getSurrounding(i);
    std::vector<int>::iterator s;
    for(s = surr.begin(); s != surr.end(); ++s) {
        increment(*s);
    }
    delete &surr;
}

void Board::increment(int i) {
    uint8_t *space = this->getSpace(i);
    *space = *space + 1;
}

std::vector<int>* Board::getSurrounding(int i) {
    std::vector<int>* surrounding;
    surrounding->reserve(8);
    // TODO really dude?
    surrounding->push_back(i - this->sizeX - 1);
    surrounding->push_back(i - this->sizeX);
    surrounding->push_back(i - this->sizeX + 1);
    surrounding->push_back(i - 1);
    surrounding->push_back(i + 1);
    surrounding->push_back(i + this->sizeX - 1);
    surrounding->push_back(i + this->sizeX);
    surrounding->push_back(i + this->sizeX + 1);

    std::vector<int>::iterator s;
    for(s = surrounding->begin(); s != surrounding->end(); ++s) {
        if(!isValidSpace(*s))
            surrounding->erase(s);
    }
    return surrounding;
}

GameState* newGame(int sizeX, int sizeY, int nMines) {
    GameState* state = new GameState();
    state->sizeX = sizeX;
    state->sizeY = sizeY;
    state->nMines = nMines;

    return state;
}

void endGame(GameState* state) {
    delete state->board;
    delete state;
}

bool Board::isValidSpace(int i) {
    int l = i / this->sizeX;
    int r = l + this->sizeX;
    int u = this->nMines;
    int d = 0;
    return i >= d
        && i < u
        && i >= l
        && i < r;
}
