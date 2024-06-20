#include <raylib.h>
#include <iostream>
#include "simulation.h"

int main()
{
    Color GREY = { 29, 29, 29, 255 };
    const int WINDOW_WIDTH = 1280; //optimized for 1280x720
    const int WINDOW_HEIGHT = 720;
    const int CELL_SIZE = 10;      //optimized for 10x10
    const int TEXT_SIZE = 26;      //optimized for 26
    int FPS = 10;                  //optimized for 10-24
    int aliveCount = 0;
    int totalAliveCells = 0;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT+TEXT_SIZE, "Game of Life by Max Siryk");
    SetTargetFPS(FPS);
    Simulation simulation{ WINDOW_WIDTH, WINDOW_HEIGHT-TEXT_SIZE, CELL_SIZE };

    while (WindowShouldClose() == false)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y/ CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            simulation.ToggleCell(row, column);
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            simulation.Start();
            SetWindowTitle("Game of Life is running ...");
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            simulation.Stop();
            SetWindowTitle("Game of Life has stopped.");
        }
        else if (IsKeyPressed(KEY_F)) // more FPS (speed up)
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if (IsKeyPressed(KEY_S)) // less FPS (slow down)
        {
            if (FPS > 5)
            {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }
        else if (IsKeyPressed(KEY_R)) 
        {
            simulation.CreateRandomState();
        }
        else if (IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }
        simulation.Update();

        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();
       
        aliveCount = simulation.GetAliveCellCount();
        totalAliveCells = simulation.GetTotalAliveCellCount();
        //all text is optimized for 1280x720, if you want to change resolution, you need to change text position
        //i don't know how to make it dynamic, so i just hardcoded it...
        DrawRectangle(0, 0, WINDOW_WIDTH, TEXT_SIZE, GREY);
        DrawText(TextFormat("Alive: %i", aliveCount), 10, WINDOW_HEIGHT - TEXT_SIZE + 5, 20, LIGHTGRAY);
        DrawText("[ENTER] Start simulation", 160, WINDOW_HEIGHT - TEXT_SIZE + 5, 20, LIGHTGRAY);
        DrawText("[SPACE] Stop simulation", 160, WINDOW_HEIGHT - TEXT_SIZE + 25, 20, LIGHTGRAY);
        DrawText("[F] Speed up", 460, WINDOW_HEIGHT - TEXT_SIZE + 25, 20, LIGHTGRAY);
        DrawText("[S] Slow down", 460, WINDOW_HEIGHT - TEXT_SIZE + 5, 20, LIGHTGRAY);
        DrawText("[R] Create random state", 640, WINDOW_HEIGHT - TEXT_SIZE + 5, 20, LIGHTGRAY);
        DrawText("[C] Clear grid", 640, WINDOW_HEIGHT - TEXT_SIZE + 25, 20, LIGHTGRAY);
        DrawText(TextFormat("FPS: %i", FPS), 10, WINDOW_HEIGHT - TEXT_SIZE + 25, 20, LIGHTGRAY);
        DrawText(TextFormat("Total alive Cells: %i", totalAliveCells), 950, WINDOW_HEIGHT - TEXT_SIZE + 5, 20, LIGHTGRAY);
        DrawText("by Maksimilian55", 1110, WINDOW_HEIGHT - TEXT_SIZE + 25, 20, LIGHTGRAY);
        }

    CloseWindow();
}