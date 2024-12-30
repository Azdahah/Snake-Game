#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace sf;
using namespace std;

unsigned int score = 0;
unsigned int t_h = 0;
unsigned int t_m = 0;
unsigned int t_s = 0;
unsigned int t_ms =0;
const unsigned int rows = 20, columns = 20;
const unsigned int window_width = 800;
const unsigned int window_height = 800;
const float cell_width = (float)window_width / columns;
const float cell_height = (float)window_height / rows; 
const unsigned int  window_x = (1920 - (window_width+300)) / 2;
const unsigned int  window_y = (1080 - (window_height)) / 2;

struct Snake {
    vector<RectangleShape> body;
    Vector2f direction = {cell_width, 0.f};

    void move() {
        for (int i = body.size() - 1; i > 0; --i) {
            body[i].setPosition(body[i - 1].getPosition());
        }
        body[0].move(direction);
    }

    void grow() {
        RectangleShape newPart(Vector2f(cell_width, cell_height));
        //newPart.setFillColor(Color::Transparent);
        newPart.setPosition(body.back().getPosition());
        body.push_back(newPart);
    }
};

void DrawGrid(float cell_width, float cell_height, RenderWindow &window, RectangleShape &cell) {
    for (unsigned int i = 0; i < columns; i++) {
        for (unsigned int j = 0; j < rows; j++) {
            cell.setPosition({cell_width * i, cell_height * j});
            window.draw(cell);
        }
    }
}

Vector2f getRandomFoodPosition() {
    int x = (rand() % columns) * cell_width;
    int y = (rand() % rows) * cell_height;
    return {float(x), float(y)};
}
 
void time(){
     t_ms++;
            if (t_ms == 20) {
                t_ms = 0;
                t_s++;  
                if (t_s == 60) {
                    t_s = 0;
                    t_m++; 
                    if (t_m == 24) {
                        t_m = 0;
                        t_h++;
                        }
                 }
             }

}             
        
int main() {
    srand(time(0));
    
    string Me[4] ={"Keep it up, Snake Master!","You're getting the hang of it!","Well done! Stay focused.","You're unstoppable, keep going!"};
    //window
    RenderWindow window(VideoMode({window_width+300, window_height}), "Snake Game", Style::Default);
    window.setPosition({window_x, window_y});
    window.setFramerateLimit(10);

    // background object
    RectangleShape cell(Vector2f(cell_width , cell_height ));
    cell.setFillColor(Color::Blue);

    // Snake
    Snake snake;
    RectangleShape head(Vector2f(cell_width-1, cell_height-1));
    head.setFillColor(Color(174, 196, 64));
    head.setPosition({cell_width * 5, cell_height * 10});
    snake.body.push_back(head);

    //food object
    RectangleShape food(Vector2f(cell_width - 1, cell_height - 1));
    food.setPosition(getRandomFoodPosition());
    //game text ,fonts and stuff
    Font game_font;
    if (!game_font.openFromFile("C:\\Studies\\1st Semester\\Programming Fundamentals\\project\\fonts\\Minecraft.ttf")) {
        cout<< "Error: Could not load font file!" << std::endl;
    }

    Text game_name(game_font);
    game_name.setString("Snake Game");
    game_name.setPosition({800+70, 80});

    Text game_score(game_font);
    game_score.setPosition({800+80, 200});

    Text game_time(game_font);
    game_time.setPosition({800+80, 600});

    Text game_over(game_font);
    game_over.setString("Game over");
    game_over.setScale({3,3});
    game_over.setPosition({150, 350});

    Text game_message(game_font);
    game_message.setPosition({800+30, 400});
    game_message.setScale({0.55,0.55});



    //game textures
    Texture game_texture;
    if (!game_texture.loadFromFile("C:\\Studies\\1st Semester\\Programming Fundamentals\\project\\textures\\Graphics\\apple.png", false, sf::IntRect({10, 10}, {32, 32})))
    {
        cout<< "Error: Could not load image file!" << std::endl;
    }
    food.setTexture(&game_texture);
   Texture snake_body;
    if (!snake_body.loadFromFile("C:\\Studies\\1st Semester\\Programming Fundamentals\\project\\textures\\Graphics\\snake_body.png", false, sf::IntRect({10, 10}, {32, 32})))
    {
        cout<< "Error: Could not load image file!" << std::endl;
    }
    Texture background;
    if (!background.loadFromFile("C:\\Studies\\1st Semester\\Programming Fundamentals\\project\\textures\\Graphics\\snake_body.png", false, sf::IntRect({10, 10}, {32, 32})))
    {
        cout<< "Error: Could not load image file!" << std::endl;
    }     
    cell.setTexture(&background);
    while (window.isOpen()) {
        while (optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Up) && snake.direction != Vector2f(0.f, cell_height)) {
                snake.direction = {0.f, -cell_height};
               
                for (int i = 1; i < snake.body.size(); i++) {
                    snake.body[i].setTexture(&snake_body);
                    }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Down) && snake.direction != Vector2f(0.f, -cell_height)) {
                snake.direction = {0.f, cell_height};
                 for (int i = 1; i < snake.body.size(); i++) {
                    snake.body[i].setTexture(&snake_body);
                    }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Left) && snake.direction != Vector2f(cell_width, 0.f)) {
                snake.direction = {-cell_width, 0.f};
                 for (int i = 1; i < snake.body.size(); i++) {
                    snake.body[i].setTexture(&snake_body);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Key::Right) && snake.direction != Vector2f(-cell_width, 0.f)) {
                snake.direction = {cell_width, 0.f};
                for (int i = 1; i < snake.body.size(); i++) {
                    snake.body[i].setTexture(&snake_body);
                }
            }
        }
      
        snake.move();
        //checks self collisions and food collision
        for (int i = 1; i < snake.body.size(); i++) {
        if (snake.body[0].getPosition() == snake.body[i].getPosition()) {
            window.draw(game_over);
            window.display();
            sleep(sf::seconds(5));
            window.close(); 
        }
        }
        if (snake.body[0].getPosition() == food.getPosition()) {
            snake.grow();
            food.setPosition(getRandomFoodPosition());
            score=score+1;
        }
        time();

        //teleporting 
        if (snake.body[0].getPosition().x >= window_width) {
            snake.body[0].setPosition({0.f, snake.body[0].getPosition().y});
        }
        if (snake.body[0].getPosition().x < 0) {
            snake.body[0].setPosition({window_width - cell_width, snake.body[0].getPosition().y});
        }
        if (snake.body[0].getPosition().y >= window_height) {
            snake.body[0].setPosition({snake.body[0].getPosition().x, 0.f});
        }
        if (snake.body[0].getPosition().y < 0) {
            snake.body[0].setPosition({snake.body[0].getPosition().x, window_height - cell_height});
        }

        game_score.setString("Score: " + to_string(score));
        game_time.setString("Time: " + to_string(t_h) +":"+ to_string(t_m) +":"+ to_string(t_s));
        if(score>5){
             game_message.setString(Me[0]);
        }
        else if(score>15&&score<35){
            game_message.setString(Me[1]);
        }
        else if(score>35&&score<55){
            game_message.setString(Me[2]);
        }
        else if(score>55){
            game_message.setString(Me[3]);
        }
        window.clear();
        DrawGrid(cell_width, cell_height, window, cell);
        for (const auto &part : snake.body) {
            window.draw(part);
        }
        window.draw(food);
        window.draw(game_name);
        window.draw(game_score);
        window.draw(game_time);
        window.draw(game_message);
       
        window.display();
    }

    return 0;
}
