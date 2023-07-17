#include "Gird.hpp"

Grid::Grid()
{
	m_texture.loadFromFile("assets/Tetriminos.png");
	int gridOffsetX = GRID_OFFSET_X;
	int sandSize = SAND_SIZE;
	m_rectangle.setSize(sf::Vector2f(sandSize, sandSize));
	gridSize(40, 81);
	for (int Y = 0; Y < m_gridSize.y; Y++)
	{
		for (int X = 0; X < m_gridSize.x; X++)
		{
			m_grid[Y][X] = 0;
			if (X == 20 && Y == 20)
			{
					m_grid[Y][X] = 1;
			}
		}
	}
}

void Grid::run()
{
	gravity();
}

void Grid::gridSize(const int& sizeX,const int& sizeY)
{
	m_gridSize.y = sizeY - 1;
	m_gridSize.x = sizeX - 1;
	m_grid.resize(sizeY);
	for (int height = 0; height < sizeY; height++)
	{
		m_grid[height].resize(sizeX);
	}
}

void Grid::gravity()
{
	for (int Y = m_gridSize.y; Y > 0; Y--)
	{
		for (int X = 0; X < m_gridSize.x; X++)
		{
			swap(Y, X, 1, 0);
		}
	}



}

void Grid::drawGrid(sf::RenderWindow& window)
{
	for (float Y = 0; Y < m_gridSize.y; Y++)
	{
		for (float X = 0; X < m_gridSize.x; X++)
		{
			if (m_grid[Y][X] != 0)
			{
				if (m_grid[Y][X] == 1)
				{
					m_rectangle.setFillColor(sf::Color::Red);
					m_rectangle.setPosition(sf::Vector2f((X * 10)+200,Y * 10));
				}

				window.draw(m_rectangle);
			}
		}
	}
	window.draw(m_playerTetromino);
}

void Grid::spawnTetromino()
{
	m_playerTetromino.setTexture(m_texture);
	m_playerTetromino.setTextureRect(sf::IntRect(0, 0, 80, 80));
	m_playerTetromino.setPosition(sf::Vector2f(400, 790));
	m_playerTetromino.setOrigin(40, 40);
	m_playerTetromino.setColor(sf::Color::Blue);
	m_playerTetromino.setScale(0.5, 0.5);
}

void Grid::swap(int Y,int X,const int axisY, const int axisX)
{
	if (!(Y >= m_gridSize.y ||
		Y < 0 ||
		X >= m_gridSize.x ||
		X < 0))
	{
		int temp = m_grid[Y - axisY][X - axisX];
		if (m_grid[Y - axisY][X - axisX] != 0)
		{
			m_grid[Y - axisY][X - axisX] = m_grid[Y][X];
			m_grid[Y][X] = temp;

		}
	}
}