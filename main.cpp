#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>

using std::cout;
using std::endl;

struct Cell
{
  int positionI;
  int positionJ;
  int status;
};

void addNeighbours(std::vector<std::vector<Cell>> grid, std::vector<Cell> &walls, int chosenWallI, int chosenWallJ, int gridHeight, int gridWidth)
{
  if (chosenWallI >= 2)
  {
    if (grid[chosenWallI - 2][chosenWallJ].status == 0)
    {
      walls.push_back(grid[chosenWallI - 2][chosenWallJ]);
    }
  }
  if (chosenWallJ >= 2)
  {
    if (grid[chosenWallI][chosenWallJ - 2].status == 0)
    {
      walls.push_back(grid[chosenWallI][chosenWallJ - 2]);
    }
  }
  if (chosenWallI <= gridWidth - 2)
  {
    if (grid[chosenWallI + 2][chosenWallJ].status == 0)
    {
      walls.push_back(grid[chosenWallI + 2][chosenWallJ]);
    }
  }
  if (chosenWallJ <= gridHeight - 2)
  {
    if (grid[chosenWallI][chosenWallJ + 2].status == 0)
    {
      walls.push_back(grid[chosenWallI][chosenWallJ + 2]);
    }
  }
}

int main()
{
  srand(time(NULL));

  int windowH = 1050;
  int windowW = 1050;
  sf::RenderWindow window(sf::VideoMode(windowW, windowH), "Maze generation");
  window.setFramerateLimit(160);

  std::vector<std::vector<Cell>> grid;
  int gridWidth = 21;
  int gridHeight = 21;

  for (int i = 0; i < gridHeight; i++)
  {
    std::vector<Cell> inner;
    for (int j = 0; j < gridWidth; j++)
    {
      Cell cell;
      cell.positionI = i;
      cell.positionJ = j;
      cell.status = 0;
      inner.push_back(cell);
    }
    grid.push_back(inner);
  }

  grid[2][2].status = 1;
  std::vector<Cell> walls;
  addNeighbours(grid, walls, 2, 2, gridHeight, gridWidth);

  while (walls.size() > 0)
  {
    int randomNumber = rand() % walls.size();

    Cell chosenWall = walls[randomNumber];
    int chosenWallI = chosenWall.positionI;
    int chosenWallJ = chosenWall.positionJ;

    if (chosenWallI - 2 >= 0 && grid[chosenWallI - 2][chosenWallJ].status == 1)
    {
      grid[chosenWallI - 1][chosenWallJ].status = 1;
    }
    else if (chosenWallI + 2 <= gridWidth && grid[chosenWallI + 2][chosenWallJ].status == 1)
    {
      grid[chosenWallI + 1][chosenWallJ].status = 1;
    }
    else if (chosenWallJ - 2 >= 0 && grid[chosenWallI][chosenWallJ - 2].status == 1)
    {
      grid[chosenWallI][chosenWallJ - 1].status = 1;
    }
    else if (chosenWallJ + 2 <= gridHeight && grid[chosenWallI][chosenWallJ + 2].status == 1)
    {
      grid[chosenWallI][chosenWallJ + 1].status = 1;
    }

    grid[chosenWallI][chosenWallJ].status = 1;

    // add the neighbours of chosenWall to wall list
    addNeighbours(grid, walls, chosenWallI, chosenWallJ, gridHeight, gridWidth);

    // remove the chosenwall from wall list
    walls.erase(walls.begin() + randomNumber);
  }

  std::vector<std::vector<sf::RectangleShape>> squareGrid;
  float rectHeight = windowH / gridHeight;
  float rectWidth = windowW / gridWidth;

  for (int i = 0; i < gridWidth; i++)
  {
    std::vector<sf::RectangleShape> inner;
    for (int j = 0; j < gridHeight; j++)
    {
      Cell currentCell = grid[i][j];
      sf::RectangleShape rect;
      rect.setSize(sf::Vector2f(rectWidth, rectHeight));
      rect.setPosition(currentCell.positionJ * rectHeight, currentCell.positionI * rectWidth);
      if (currentCell.status == 1)
      {
        rect.setFillColor(sf::Color::White);
      }
      else
      {
        rect.setFillColor(sf::Color::Black);
      }
      inner.push_back(rect);
    }
    squareGrid.push_back(inner);
  }

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);
    for (int i = 0; i < gridHeight; i++)
    {
      for (int j = 0; j < gridWidth; j++)
      {
        window.draw(squareGrid[i][j]);
      }
    }

    window.display();
  }

  return 0;
}