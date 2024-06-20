#pragma once
#pragma once
#include "grid.h"

class Simulation
{
public:
    Simulation(int width, int height, int cellSize)
        : grid(width, height, cellSize),
        tempGrid(width, height, cellSize),
        run(false) {};
    void Draw();
    void SetCellValue(int row, int column, int value);
    int CountLiveNeighbors(int row, int column);
    void Update();
    bool IsRunning() { return run; }
    void Start() { run = true; }
    void Stop() { run = false; }
    void ClearGrid();
    void CreateRandomState();
    void ToggleCell(int row, int column);
    int GetAliveCellCount();
    int totalAliveCells = 0;
    int GetTotalAliveCellCount();
    int generation = 0;
private:
    Grid grid;
    Grid tempGrid;
    bool run;
};