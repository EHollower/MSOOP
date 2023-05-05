#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include <chrono>
#include <queue>

#include <SFML/Graphics.hpp>

class Cell { // a setter/getter handles the cell states
private:
    int nr_mines;
    bool FLAGGED, MINE, COVERED;
public:
    Cell(): nr_mines(0), FLAGGED(false), MINE(false), COVERED(true) {}
    ~Cell() {
        clearCell();
    };

    void flagCell() {
        FLAGGED = !FLAGGED;
    }

    void setMine() {
        MINE = true;
    }

    void setNrMines(const int& _nr) {
        nr_mines = _nr;
    }

    void uncoverCell() {
        COVERED = false;
    }

    [[nodiscard]] bool isCovered() const {
        return COVERED;
    }

    [[nodiscard]] bool isMine() const {
        return MINE;
    }

    [[nodiscard]] bool isFlag() const {
        return FLAGGED;
    }

    [[nodiscard]] int numberOfMines() const {
        return nr_mines;
    }

    Cell& operator = (const Cell& other) = default;
    bool operator == (const Cell& other) const = default;

    void clearCell() {
        FLAGGED = MINE = false;
        COVERED = true;
    }

    friend std::ostream& operator << (std::ostream& stream, const Cell& cell) {
        if (cell.isFlag()) {
            stream << "F";
            return stream;
        }

        if (cell.isCovered()) {
            stream << "#";
            return stream;
        }

        if (!cell.isMine()) {
            stream << ".";
            return stream;
        }

        stream << cell.nr_mines;
        return stream;
    }
};

class GameTextures { // DesignPattern used to configure the game sprites
private:
    GameTextures() { // Initialize the sprites configurations
        mines[0] = sf::IntRect(18, 56, 16, 16);
        mines[1] = sf::IntRect(1, 73, 16, 16);
        for (int i = 2; i <= 8; ++i) {
            mines[i] = mines[i - 1];
            mines[i].left += 17;
        }
    }

    ~GameTextures() = default;

    const std::string PATH = "assets/sprites.png";
    bool texture_loaded = false;
    sf::IntRect mines[9];
    sf::Texture texture;

    float x_start = 200.f; // starting x position
    float y_start = 100.f; // starting y position
    float sprite_width = 32.f; // width of each sprite
    float sprite_height = 32.f; // height of each sprite
    float padding = 10.f; // padding between sprites
    float scale_factor = 2.5f; // factor to scale each sprite by

public:
    GameTextures(const GameTextures&) = delete; // delete copy constructor
    GameTextures& operator=(const GameTextures&) = delete; // delete copy assignment
    GameTextures(GameTextures&&) = delete; // delete move constructor
    GameTextures& operator=(GameTextures&&) = delete; // delete move assignment

    static GameTextures* getInstance() {
        static GameTextures* instance = nullptr;
        if (!instance) {
            instance = new GameTextures();
        }
        return instance;
    }

    sf::Texture& getTexture() {
        if (!texture_loaded) {
            texture.loadFromFile(PATH);
            texture_loaded = true;
        }
        return texture;
    }

    static sf::IntRect& getSmiley() {
        static sf::IntRect pos(1, 28, 27, 28);
        return pos;
    }

    static sf::IntRect& getSmileyPressed() {
        static sf::IntRect pos(29, 28, 27, 28);
        return pos;
    }

    static sf::IntRect& getCovered() {
        static sf::IntRect pos(1, 56, 16, 16);
        return pos;
    }

    static sf::IntRect& getFlag() {
        static sf::IntRect pos(35, 56, 16, 16);
        return pos;
    }

    static sf::IntRect& getMine() {
        static sf::IntRect pos(86, 56, 16, 16);
        return pos;
    }

    sf::IntRect& getNeighbouringMines(const int& nr) {
        return mines[nr];
    }

    float getXStart() const {
        return x_start;
    }

    float getYStart() const {
        return y_start;
    }

    float getSpriteWidth() const {
        return sprite_width;
    }

    float getSpriteHeight() const {
        return sprite_height;
    }

    float getPadding() const {
        return padding;
    }

    float getScaleFactor() const {
        return scale_factor;
    }

};

class GameBoard { // The Game Board of MineSweeper
private:
    const int dir_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; // for checking neighbouring cells
    const int dir_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector <std::vector <Cell>> board;
    int rows, columns, nr_mines;
    int first_x, first_y;
    bool endgame;

    [[nodiscard]] std::pair <int, int> gen_mine(std::mt19937& game_seed) const { // generate random position on the board
        std::uniform_int_distribution <int> gen_row(0, rows - 1);
        std::uniform_int_distribution <int> gen_col(0, columns - 1);
        int x = gen_row(game_seed);
        int y = gen_col(game_seed);
        return std::make_pair(x, y);
    }

    [[nodiscard]] bool check_border(int x, int y) const { // check if the position (x, y) is inside the board
        return x >= 0 and x < rows and y >= 0 and y < columns;
    }

public:
    explicit GameBoard(int _h = 9, int _w = 9, int _nr = 10) :
    rows(_h), columns(_w), nr_mines(_nr), first_x(-1), first_y(-1), endgame(false) {
        board.resize(rows);
            for (int i = 0; i < rows; ++i)
                board[i].resize(columns);
    }

    ~GameBoard() {
        clearBoard();
    }

    void gen_game() {
        std::mt19937 game_seed(std::chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < nr_mines; ++i) {
            auto [row, col] = gen_mine(game_seed);
            if (board[row][col].isMine() or std::make_pair(row, col) == std::make_pair(first_x, first_y)) {
                // we already have a mine in this cell / the first cell the player touches is never a mine
                --i; continue;
            }
            board[row][col].setMine();
        }

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j) {
                if (board[i][j].isMine())
                    continue;

                int near_mines = 0;
                for (int d = 0; d < 8; ++d) {
                    if (check_border(i + dir_row[d], j + dir_col[d])) {
                        near_mines += (board[i + dir_row[d]][j + dir_col[d]].isMine());
                    }
                }

                if (near_mines != 0) {
                    board[i][j].setNrMines(near_mines);
                }
            }
    }

    void touch(const int& row, const int& col) { // function for interface use
        if (!check_border(row, col))
            return;

        if (std::make_pair(first_x, first_y) == std::make_pair(-1, -1)) {
            first_x = row, first_y = col;
            gen_game();
        }
        endgame |= !reveal_cell(row, col); // see if we hit a mine or not
    }

    bool reveal_cell(const int& row, const int& col) { // reveal cell/s
        if (board[row][col].isMine()) {
            return false;
        }
        bfs(row, col);
        return true;
    }

    void bfs(const int& row, const int& col) { // reveal cells till we find a mine / cell that have mines near them
        std::queue <std::pair <int, int>> q;
        q.emplace(row, col);

        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            if (board[x][y].isFlag() or !board[x][y].isCovered())
                continue;

            if (board[x][y].numberOfMines() != 0) {
                board[x][y].uncoverCell();
                continue;
            }

            if (!board[x][y].isMine())
                board[x][y].uncoverCell();

            for (int d = 0; d < 8; ++d) {
                int tmp_x = x + dir_row[d];
                int tmp_y = y + dir_col[d];
                if (check_border(tmp_x, tmp_y) and board[tmp_x][tmp_y].isCovered())
                    q.emplace(tmp_x, tmp_y);
            }
        }
    }

    void reveal() {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i][j].uncoverCell();
    }

    [[nodiscard]] Cell& getCell(const int& row, const int& col) {
        return board[row][col];
    }

    void putFlag(const int& row, const int& col) {
        if (check_border(row, col))
            board[row][col].flagCell();
    }

    [[nodiscard]] bool isRunning() const {
        return !endgame;
    }

    void clearBoard() {
        endgame = false;
        first_x = first_y = -1;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                board[i][j].clearCell();
    }

    friend std::ostream& operator << (std::ostream& stream, const GameBoard& MineSweeper) {
            for (int i = 0; i < MineSweeper.rows; ++i, stream << "\n")
                for (int j = 0; j < MineSweeper.columns; ++j)
                    stream << MineSweeper.board[i][j] << " ";
            return stream;
    }
};

class GameWindow {
private:
    sf::RenderWindow app{};
    void create_window() {
        app.create(sf::VideoMode({800, 600}), "Minesweeper?", sf::Style::Default);
        app.setFramerateLimit(120);
    }
    void close_window() {
        app.close();
    }
public:
    GameWindow() {
        create_window();
    }

    bool isRunning() const {
        return app.isOpen();
    }

    void clear_window() {
        app.clear(sf::Color::Blue);
    }

    std::pair <int, int> get_coord() { // get position of the clicked sprite
        sf::Vector2f mousePos = app.mapPixelToCoords(sf::Mouse::getPosition(app));
        int i = static_cast<int>((mousePos.x - GameTextures::getInstance()-> getXStart()) / (GameTextures::getInstance()->getSpriteWidth() + GameTextures::getInstance()->getPadding()));
        int j = static_cast<int>((mousePos.y - GameTextures::getInstance()-> getYStart()) / (GameTextures::getInstance()->getSpriteHeight() + GameTextures::getInstance()->getPadding()));
        return std::make_pair(i, j);
    }

    void update(sf::Sprite& smiley, GameBoard& board) {
        app.display();
        sf::Event event{};
        while (app.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    close_window();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        board.putFlag(get_coord().first, get_coord().second);
                    }
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (smiley.getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(app).x), static_cast<float>(sf::Mouse::getPosition(app).y))) {
                            smiley.setTextureRect(GameTextures::getSmileyPressed());
                            app.draw(smiley);
                            app.display();
                            sf::sleep(sf::milliseconds(100));
                            board.clearBoard();
                        }
                        board.touch(get_coord().first, get_coord().second);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void draw_obj(const sf::Sprite& sprite)  {
        app.draw(sprite);
    }

    friend std::ostream& operator << (std::ostream& stream, const GameWindow& window) {
        stream << window.app.getSize().x << " " << window.app.getSize().y << "\n";
        return stream;
    }

    ~GameWindow() {
        close_window();
    }
};

class Game {
private:
    int row, col;
    GameBoard board;
    GameWindow window;
    sf::Sprite smiley;
    std::vector <std::vector <sf::Sprite>> sprites;
public:
    explicit Game(int _h = 9, int _w = 9) {
        row = _h, col = _w;
        smiley.setTexture(GameTextures::getInstance()->getTexture());
        smiley.setPosition(350.f, 10.f);
        smiley.setScale(2.5f, 2.5f);
        sprites.resize(row);
        for (int i = 0; i < row; ++i) {
            sprites[i].resize(col);
            for (int j = 0; j < col; ++j) {
                float x_pos = GameTextures::getInstance()->getXStart() + static_cast<float>(i) * (GameTextures::getInstance()->getSpriteWidth() + GameTextures::getInstance()->getPadding());
                float y_pos = GameTextures::getInstance()->getYStart() + static_cast<float>(j) * (GameTextures::getInstance()->getSpriteHeight() + GameTextures::getInstance()->getPadding());
                sprites[i][j].setTexture(GameTextures::getInstance()->getTexture());
                sprites[i][j].setPosition(x_pos, y_pos);
                sprites[i][j].setScale(sf::Vector2(GameTextures::getInstance()->getScaleFactor(), GameTextures::getInstance()->getScaleFactor()));
            }
        }
    }

    void draw_smiley() {
        smiley.setTextureRect(GameTextures::getSmiley());
        window.draw_obj(smiley);
    };

    void draw_game() {
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {
                if (board.getCell(i, j).isCovered()) {
                    bool choice = !board.getCell(i, j).isFlag();
                    sprites[i][j].setTextureRect(choice? GameTextures::getCovered() : GameTextures::getFlag());
                    window.draw_obj(sprites[i][j]);
                    continue;
                }

                if (!board.getCell(i, j).isCovered() and !board.getCell(i, j).isMine()) {
                    sprites[i][j].setTextureRect(GameTextures::getInstance()->getNeighbouringMines(board.getCell(i, j).numberOfMines()));
                    window.draw_obj(sprites[i][j]);
                    continue;
                }

                sprites[i][j].setTextureRect(GameTextures::getMine());
                window.draw_obj(sprites[i][j]);
            }
    }

    void checkIfEnded() {
        if (!board.isRunning()) {
            board.reveal();
        }
    }

    void handle_input() {
        while (window.isRunning()) {
            checkIfEnded();
            window.clear_window();
            draw_smiley();
            draw_game();
            window.update(smiley, board);
            std::cout << window << "\n";
            std::cout << board << "\n";
        }
    }
};

int main() {
    Game minesweeper;
    minesweeper.handle_input();
    return 0;
}
