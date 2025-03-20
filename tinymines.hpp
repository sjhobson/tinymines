#include <cstdint>
#include <vector>

const uint8_t SURROUNDING_MASK = 0b00001111;
const uint8_t CHECKED = 0b10000000;
const uint8_t FLAGGED = 0b01000000;
const uint8_t UNSURE =  0b00100000;
const uint8_t IS_MINE = 0b00010000;

struct Board {
private:
    int nMines;
    int sizeX;
    int sizeY;
    uint8_t *board;

public:
    Board(int sizeX, int sizeY, int nMines);
    ~Board();
    uint8_t *getSpace(int x, int y);
    bool isMine(int x, int y);
    bool isMineAdjacent(int x, int y);
    void toggleFlagged(int x, int y);
    bool isFlagged(int x, int y);
    void toggleUnsure(int x, int y);
    bool isUnsure(int x, int y);
    void setChecked(int x, int y);
    bool isFlipped(int x, int y);

private:
    uint8_t *getSpace(int i);
    void setMine(int i);
    std::vector<int> *getSurrounding(int i);
    bool isValidSpace(int i);
    void increment(int i);
};

struct GameState {
    int sizeX;
    int sizeY;
    int nMines;
    Board* board;
};

GameState* newGame(int sizeX, int sizeY, int nMines);