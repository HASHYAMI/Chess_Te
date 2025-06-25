#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const int CELL_SIZE = 100;
const int GRID_SIZE = 6;
const int WINDOW_SIZE = CELL_SIZE * GRID_SIZE;

enum class Player {
    None,
    A,
    B
};

struct Unit {
    int x, y;
    Player owner;
};

int Winmain() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Turn-Based Grid");

    // �Ֆʏ��
    Player board[GRID_SIZE][GRID_SIZE] = {};
    Unit unitA = { 0, 0, Player::A };
    Unit unitB = { GRID_SIZE - 1, GRID_SIZE - 1, Player::B };
    board[unitA.y][unitA.x] = Player::A;
    board[unitB.y][unitB.x] = Player::B;

    Player currentTurn = Player::A;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // �}�E�X�N���b�N����
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                int cellX = event.mouseButton.x / CELL_SIZE;
                int cellY = event.mouseButton.y / CELL_SIZE;

                if (cellX >= 0 && cellX < GRID_SIZE && cellY >= 0 && cellY < GRID_SIZE) {
                    // ���݂̃v���C���[�̃��j�b�g��I�сA�ړI�}�X����Ȃ�ړ�
                    Unit& currentUnit = (currentTurn == Player::A) ? unitA : unitB;

                    // �אڃ}�X�ɂ݈̂ړ�����
                    if (abs(cellX - currentUnit.x) + abs(cellY - currentUnit.y) == 1 &&
                        board[cellY][cellX] == Player::None) {

                        // �Ֆʂ̍X�V
                        board[currentUnit.y][currentUnit.x] = Player::None;
                        currentUnit.x = cellX;
                        currentUnit.y = cellY;
                        board[cellY][cellX] = currentTurn;

                        // �^�[�����
                        currentTurn = (currentTurn == Player::A) ? Player::B : Player::A;
                    }
                }
            }
        }

        // �`��
        window.clear(sf::Color::White);

        // �O���b�h���ƃ}�X�`��
        for (int y = 0; y < GRID_SIZE; ++y) {
            for (int x = 0; x < GRID_SIZE; ++x) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
                cell.setPosition(x * CELL_SIZE + 1, y * CELL_SIZE + 1);
                cell.setFillColor(sf::Color(230, 230, 230));
                window.draw(cell);

                // �v���C���[�R�}�`��
                if (board[y][x] == Player::A || board[y][x] == Player::B) {
                    sf::CircleShape piece(CELL_SIZE / 2 - 10);
                    piece.setPosition(x * CELL_SIZE + 10, y * CELL_SIZE + 10);
                    piece.setFillColor(board[y][x] == Player::A ? sf::Color::Blue : sf::Color::Red);
                    window.draw(piece);
                }
            }
        }

        window.display();
    }

    return 0;
}
