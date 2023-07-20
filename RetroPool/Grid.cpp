#include "Gird.hpp"

Grid::Grid()
{
	loadTetriminoTextures();
	int gridOffsetX = GRID_OFFSET_X;
	int sandSize = SAND_SIZE;
	m_playerGravity = 0;
	m_rectangle.setSize(sf::Vector2f(sandSize, sandSize));
	gridSize(40, 81);
	for (int Y = 0; Y < m_gridSize.y; Y++)
	{
		for (int X = 0; X < m_gridSize.x; X++)
		{
			m_grid[Y][X] = 0;
			if (X == 20 && Y >= 20)
			{
					m_grid[Y][X] = 1;
			}
		}
	}
}

void Grid::loadTetriminoTextures()
{
	
	if (!(m_tetrominoTex[0].loadFromFile("assets/Ltetromino.png")     &&
		  m_tetrominoTex[1].loadFromFile("assets/Skewtetromino.png")  &&
		  m_tetrominoTex[2].loadFromFile("assets/Squaretetromin.png") &&
		  m_tetrominoTex[3].loadFromFile("assets/Stetromino.png")     &&
		  m_tetrominoTex[4].loadFromFile("assets/Ttetromino.png")))
		{
		std::cout << "TetriminoTextures failed to load one or all";
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
			if (!(swap(Y, X, 1, 0)))
			{
				std::srand(static_cast<unsigned int>(std::time(0)));
				switch (std::rand() % 2)
				{
					//movment to the left
				case (0):
					{
					// if it cannot move to the left it will check the right
					if (swap(Y, X, 1, -1))
					{
						swap(Y, X, 1, 1);
					}

					break;
					}
					//movment to the right
				case (1):
					{
					// if it cannot move to the right it will check the left
					if (swap(Y, X, 1, 1))
					{
						swap(Y, X, 1, -1);
					}
					break;
					}
					
				}
			}
		}
	}
}

void Grid::playerGravity()
{
	if (m_playerGravity == 0)
	{
		m_playerGravity = m_playerTetromino.getPosition().y / 10;
	}
	m_playerTetromino.setPosition(m_playerTetromino.getPosition().x, m_playerGravity * 10);
	m_playerGravity++;
	if (m_playerGravity >= 80)
	{
		m_playerGravity = 1;
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
	m_playerTetromino.setTexture(m_tetrominoTex[2]);
	m_currentTex = 2;
	m_playerTetromino.setTextureRect(sf::IntRect(0, 0, 80, 80));
	m_playerTetromino.setPosition(sf::Vector2f(400, 30));
	m_playerTetromino.setOrigin(40, 40);
	m_playerTetromino.setColor(sf::Color::Blue);
	m_playerTetromino.setScale(0.5, 0.5);
	sf::Image a = m_tetrominoTex[m_currentTex].copyToImage();
	
	for (int Y = 0; Y < 4; Y++)
	{
		for (int X = 0; X < 4; X++)
		{
			sf::Color pixcolor = a.getPixel(20 * X,20 * Y);
			if (static_cast<int>(pixcolor.b) > 0)
			{
				m_copyMatrix[Y][X] = 1;
				continue;
			}
			m_copyMatrix[Y][X] = 0;
		}
		std::cout << std::endl;
	}

	for (int Y = 0; Y < 4; Y++)
	{
		for (int X = 0; X < 4; X++)
		{
			std::cout << m_copyMatrix[Y][X] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::rotationUpdate()
{

	TX++;
	m_playerTetromino.setRotation(90 * TX);
	tetriminoOrientationUpdate();
	if (TX == 4)
	{
		TX = 0;
	}
}

void Grid::tetriminoOrientationUpdate()
{
	for (int layer = 0; layer < TETROMINO_MATRIX_SIZE / 2;layer++)
	{
		
		int first = layer;
		int last = TETROMINO_MATRIX_SIZE - first - 1;
		for (int i = first; i < last; i++)
		{
			int offset = i - first;
			int top = m_copyMatrix[first][i];
			m_copyMatrix[first][i] = m_copyMatrix[last - offset][first];
			m_copyMatrix[last - offset][first] = m_copyMatrix[last][last - offset];
			m_copyMatrix[last][last - offset] = m_copyMatrix[i][last];
			m_copyMatrix[i][last] = top;
		}
	}
	/*
	for (int Y = 0; Y < 4; Y++)
	{
		for (int X = 0; X < 4; X++)
		{
			std::cout << m_copyMatrix[Y][X] << " ";
		}
		std::cout << std::endl;
	}
	*/
}

void Grid::tetminoCollisionUpdate()
{
































	/*
	sf::Vector2f savedOrigin(m_playerTetromino.getOrigin());
	m_playerTetromino.setOrigin(sf::Vector2f(0, 0));
	int Y = m_playerTetromino.getPosition().y / m_gridSize.y;
	int X = (m_playerTetromino.getPosition().x - GRID_OFFSET_X) / m_gridSize.x;
	float size =  m_playerTetromino.getScale().x * SAND_SIZE * 2;
	*/

	/*
	sf::Transform textureTransform = m_playerTetromino.getTransform().getInverse();
	sf::Vector2f texturecords = textureTransform.transformPoint(sf::Vector2f(0, 0));
	texturecords.x /= TEXTURE_SIZE;
	texturecords.y /= TEXTURE_SIZE;
	sf::Image a = m_tetrominoTex[m_currentTex].copyToImage();
	
	for (float Y = 0; Y < 4; Y++)
	{
		for (float X = 0; X < 4; X++)
		{
			sf::Color pixcolor = a.getPixel(texturecords.x + (20 * X), texturecords.y + (20 * Y));
			std::cout << static_cast<int>(pixcolor.b) << " ";
		}
		std::cout << std::endl;
	}
	*/
	//m_playerTetromino.setOrigin(savedOrigin);
}

bool Grid::swap(int Y,int X,const int axisY, const int axisX)
{
	if (!(Y >= m_gridSize.y ||
		Y < 0 ||
		X >= m_gridSize.x ||
		X < 0))
	{
		if (!(Y + axisY >= m_gridSize.y ||
			Y + axisY < 0 ||
			X - axisX >= m_gridSize.x ||
			X - axisX < 0))
		{
			
			if (m_grid[Y + axisY][X - axisX] == 0)
			{
				int temp = m_grid[Y + axisY][X - axisX];
				m_grid[Y + axisY][X - axisX] = m_grid[Y][X];
				m_grid[Y][X] = temp;
				return true;
			}
			return false;
		}
	}
	return false;
}