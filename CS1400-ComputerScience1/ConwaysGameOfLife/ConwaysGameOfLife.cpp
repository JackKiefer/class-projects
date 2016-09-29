// Generates ASCII iterations of Conway's Game of Life in the command line using hard-coded rules and initial conditions

#include <iostream>
#include <vector>

namespace
{
	const auto WIDTH = 11;
	const auto HEIGHT = 11;
	const auto ITER = 20;
}

enum class Cell
{
	ALIVE, DEAD
};

Cell applyRules(std::vector < std::vector < Cell> > grid, int i, int j)
{

	int livingNeighbors = 0;

	//edge limits
	if (i == 0 || i == HEIGHT - 1) return Cell::DEAD;
	if (j == 0 || j == WIDTH - 1)  return Cell::DEAD;
	
	//counts the number of living neighbors
	if (grid[i - 1][j - 1] == Cell::ALIVE) ++livingNeighbors; // NW
	if (grid[i][j - 1]     == Cell::ALIVE) ++livingNeighbors; // N
	if (grid[i + 1][j - 1] == Cell::ALIVE) ++livingNeighbors; // NE
	if (grid[i - 1][j]     == Cell::ALIVE) ++livingNeighbors; // W
	if (grid[i + 1][j]     == Cell::ALIVE) ++livingNeighbors; // E
	if (grid[i - 1][j + 1] == Cell::ALIVE) ++livingNeighbors; // SW
	if (grid[i][j + 1]     == Cell::ALIVE) ++livingNeighbors; // S
	if (grid[i + 1][j + 1] == Cell::ALIVE) ++livingNeighbors; // SE

	//hard-coded rules
	//Any live cell with fewer than two live neighbours dies

	if (grid[i][j] == Cell::ALIVE && livingNeighbors < 2) return Cell::DEAD;

	//Any live cell with two or three live neighbours lives on

	else if (grid[i][j] == Cell::ALIVE && (livingNeighbors == 2 || livingNeighbors == 3)) return Cell::ALIVE;

	//Any live cell with more than three live neighbours dies

	else if (grid[i][j] == Cell::ALIVE && livingNeighbors > 3) return Cell::DEAD;

	//Any dead cell with exactly three live neighbours becomes a live cell

	else if (grid[i][j] == Cell::DEAD && livingNeighbors == 3) return Cell::ALIVE;

	else return Cell::DEAD;

}

std::vector < std::vector<Cell> > update(std::vector< std::vector<Cell> > const & grid)
{
	std::vector< std::vector<Cell> > tempGrid = grid;
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			tempGrid[i][j] = applyRules(grid, i, j);
		}
	}
	return tempGrid;
}

void display(Cell c)
{
	if (c == Cell::ALIVE)
	{
		std::cout << '@';
	}
	else
	{
		std::cout << ' ';
	}
}

void display(std::vector<std::vector<Cell>> const & grid)
{
	for (std::vector<Cell> row : grid)
	{
		for (Cell & c : row)
		{
			display(c);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//...........
//...........
//...........
//...###.#...
//...#.......
//......##...
//....##.#...
//...#.#.#...
//...........
//...........
//...........

std::vector < std::vector<Cell> > initialCells(std::vector < std::vector<Cell> > grid)
{
	grid[4][4] = Cell::ALIVE;
	grid[4][5] = Cell::ALIVE;
	grid[4][6] = Cell::ALIVE;
	grid[4][8] = Cell::ALIVE;
	grid[5][4] = Cell::ALIVE;
	grid[6][7] = Cell::ALIVE;
	grid[6][8] = Cell::ALIVE;
	grid[7][5] = Cell::ALIVE;
	grid[7][6] = Cell::ALIVE;
	grid[7][8] = Cell::ALIVE;
	grid[8][4] = Cell::ALIVE;
	grid[8][6] = Cell::ALIVE;
	grid[8][8] = Cell::ALIVE;
	return grid;
}

int main()
{
	std::vector< std::vector<Cell> > grid(HEIGHT);
	for (std::vector<Cell> & row : grid)
	{
		row.reserve(WIDTH);
		for (int j = 0; j < WIDTH; ++j)
		{
			row.push_back(Cell::DEAD);
		}
	}
	grid = initialCells(grid);
	for (int i = 0; i < ITER; ++i)
	{
		display(grid);
		grid = update(grid);
	}
	char dummy;
	std::cin >> dummy;
}
