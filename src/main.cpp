// ------------------------------------------------------------
// Modules
// ------------------------------------------------------------

#include <raylib.h>
#include <string>

// ------------------------------------------------------------
// Global Storage
// ------------------------------------------------------------

constexpr float SCREEN_WIDTH = 1280;
constexpr float SCREEN_HEIGHT = 720;
constexpr float TARGET_FPS = 60;

// ------------------------------------------------------------
// Class Definitions
// ------------------------------------------------------------

class Ball
{
public:
    bool is_hitting_boundary()
    {
        return (x <= radius || x >= (SCREEN_WIDTH - radius) || y <= radius || y >= (SCREEN_HEIGHT - radius));
    }

    float x, y;
    float radius;
    float speedX, speedY;
    Color color;

    Ball(float posX, float posY, float radius, float speedX, float speedY, Color color)
    {
        x = posX;
        y = posY;
        this->radius = radius;
        this->speedX = speedX;
        this->speedY = speedY;
        this->color = color;
    }

    Vector2 get_position()
    {
        Vector2 pos = {x, y};
        return pos;
    }

    void draw()
    {
        DrawCircle((int)x, (int)y, radius, color);
    }

    void update()
    {
        x += GetFrameTime() * speedX;
        y += GetFrameTime() * speedY;

        if (is_hitting_boundary())
        {
            if (x <= radius || x >= (SCREEN_WIDTH - radius))
                speedX *= -1;
            if (y <= radius || y >= (SCREEN_HEIGHT - radius))
                speedY *= -1;
        }
    }
};

class Paddle
{
public:
    float x, y;
    float width, height;
    float speed;
    Color color;

    void bound_self()
    {
        if (y <= 0 || y >= (SCREEN_HEIGHT - height))
        {
            if (y <= 0)
                y = 0;
            if (y >= (SCREEN_HEIGHT - height))
                y = SCREEN_HEIGHT - height;
        }
    }

    Paddle(float posX, float posY, float width, float height, float speed, Color color)
    {
        x = posX;
        y = posY;
        this->width = width;
        this->height = height;
        this->speed = speed;
        this->color = color;
    }

    Rectangle get_paddle_rect()
    {
        Rectangle rec = {x, y, width, height};
        return rec;
    }

    void draw()
    {
        Rectangle rec = {x, y, width, height};
        DrawRectangleRec(rec, color);
    }

    void update()
    {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            y -= GetFrameTime() * speed;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            y += GetFrameTime() * speed;

        bound_self();
    }
};

class MultiplayerPaddle : public Paddle
{
public:
    using Paddle::Paddle;

    void update(float ballY)
    {
        if (ballY > (y + (height / 2)))
            y += GetFrameTime() * speed;
        if (ballY < (y + (height / 2)))
            y -= GetFrameTime() * speed;

        bound_self();
    }
};

class Score
{
private:
    unsigned int playerScore, compScore;

public:
    Score()
    {
        playerScore = 0;
        compScore = 0;
    }

    int get_comp_score()
    {
        return compScore;
    }

    int get_player_score()
    {
        return playerScore;
    }

    void draw()
    {
        // Draw Player Score
        DrawText(std::to_string(playerScore).c_str(), (SCREEN_WIDTH / 2) - 50, 20, 32, WHITE);
        // Draw Comp Score
        DrawText(std::to_string(compScore).c_str(), (SCREEN_WIDTH / 2) + 50, 20, 32, WHITE);
    }

    void update(int key)
    {
        // 0 -> Player Score, 1 -> Comp Score
        if (key == 0)
            playerScore++;
        else if (key == 1)
            compScore++;
    }
};

// ------------------------------------------------------------
// Helper Functions
// ------------------------------------------------------------

void draw_boundary_line();

int main()
{
    // ------------------------------------------------------------
    // Initialization
    // ------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dong");
    SetTargetFPS(TARGET_FPS);
    Score gameScore;
    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 300, 300, WHITE);
    Paddle playerPaddle(0, 0, 20, 120, 300, WHITE);
    MultiplayerPaddle comPaddle(SCREEN_WIDTH - 20, 0, 20, 120, 300, WHITE);

    while (!WindowShouldClose())
    {

        // ------------------------------------------------------------
        // Check & Update
        // ------------------------------------------------------------

        if (CheckCollisionCircleRec(ball.get_position(), ball.radius, playerPaddle.get_paddle_rect()) || CheckCollisionCircleRec(ball.get_position(), ball.radius, comPaddle.get_paddle_rect()))
        {
            ball.speedX *= -1;

            if (ball.speedX > 0)
                ball.speedX += 20;
            else
                ball.speedX -= 20;

            if (ball.speedY > 0)
                ball.speedY += 20;
            else
                ball.speedY -= 20;

            if ((int)ball.speedX % 100 == 0)
            {
                if (gameScore.get_player_score() > gameScore.get_comp_score())
                {
                    comPaddle.speed += GetRandomValue(40, 100 + (gameScore.get_player_score() - gameScore.get_comp_score()) * 10);
                }
                else
                {
                    comPaddle.speed += GetRandomValue(30, 100);
                }
                playerPaddle.speed += 20;
            }
        }

        if ((ball.x - ball.radius) <= 0 || (ball.x + ball.radius) >= SCREEN_WIDTH)
        {
            if ((ball.x - ball.radius) <= 0)
                gameScore.update(1);
            else if ((ball.x + ball.radius) >= SCREEN_WIDTH)
                gameScore.update(0);

            ball.x = SCREEN_WIDTH / 2;
            ball.y = SCREEN_HEIGHT / 2;
            ball.speedX = 300;
            ball.speedY = 300;
            comPaddle.speed = 300;
            playerPaddle.speed = 300;
        }

        ball.update();
        playerPaddle.update();
        comPaddle.update(ball.y);

        // ------------------------------------------------------------
        // Draw
        // ------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);
        draw_boundary_line();
        gameScore.draw();
        ball.draw();
        playerPaddle.draw();
        comPaddle.draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

// ------------------------------------------------------------
// Helper Functions Definitions
// ------------------------------------------------------------

void draw_boundary_line()
{
    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
}