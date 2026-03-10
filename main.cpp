#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Simple Chess Board and Pieces Representation
class ChessPiece {
public:
    sf::Sprite sprite;
    std::string type; // e.g., "pawn", "rook", etc.
    bool isWhite;
    ChessPiece(const sf::Texture& texture, bool white, const std::string& t) : isWhite(white), type(t) {
        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f); // Adjust scale as needed
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Chess Game");
    sf::Texture pieceTexture;
    if (!pieceTexture.loadFromFile("pieces.png")) { // Assume a sprite sheet for pieces
        return -1;
    }

    // Initialize board (8x8 grid)
    std::vector<std::vector<ChessPiece*>> board(8, std::vector<ChessPiece*>(8, nullptr));

    // Place initial pieces (simplified, only pawns for brevity)
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new ChessPiece(pieceTexture, false, "pawn");
        board[6][i] = new ChessPiece(pieceTexture, true, "pawn");
    }
    // Add more pieces as needed...

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Draw board
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                sf::RectangleShape square(sf::Vector2f(50, 50));
                square.setPosition(i * 50, j * 50);
                square.setFillColor((i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black);
                window.draw(square);

                if (board[i][j]) {
                    board[i][j]->sprite.setPosition(i * 50, j * 50);
                    window.draw(board[i][j]->sprite);
                }
            }
        }

        window.display();
    }

    // Clean up
    for (auto& row : board) {
        for (auto& piece : row) {
            delete piece;
        }
    }

    return 0;
}