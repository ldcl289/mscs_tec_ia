
#include <iostream>
#include <vector>
#include "Agent.h"

const int size = 4;

void adjacentPerceptions(std::vector<std::vector<Space>>& maze, const std::string& perception, const std::string& consecuense)
{

}

std::vector<std::vector<Space>> buildMaze()
{
    std::vector<std::vector<Space>> maze;
    for(int i = 0; i < size ; ++i)
    {
        maze.push_back(std::vector<Space>());
        for(int j = 0; j < size; ++j)
        {
            maze[i].push_back(Space(i, j));
        }
    }
    maze[2][0].perceptions[BaseKnowledge::PIT] = true;
    maze[1][0].perceptions[BaseKnowledge::WIND] = true;
    maze[3][0].perceptions[BaseKnowledge::WIND] = true;
    maze[2][1].perceptions[BaseKnowledge::WIND] = true;

    maze[0][2].perceptions[BaseKnowledge::WUMPUS] = true;
    maze[0][1].perceptions[BaseKnowledge::STINK] = true;
    maze[1][2].perceptions[BaseKnowledge::STINK] = true;
    maze[0][3].perceptions[BaseKnowledge::STINK] = true;

    maze[2][2].perceptions[BaseKnowledge::PIT] = true;
    maze[2][1].perceptions[BaseKnowledge::WIND] = true;
    maze[2][3].perceptions[BaseKnowledge::WIND] = true;
    maze[1][2].perceptions[BaseKnowledge::WIND] = true;
    maze[3][2].perceptions[BaseKnowledge::WIND] = true;

    maze[3][3].perceptions[BaseKnowledge::PIT] = true;

    maze[1][2].perceptions[BaseKnowledge::GOLD] = true;

    for(int i = 0; i < size ; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(maze[i][j].perceptions[BaseKnowledge::PIT])
                adjacentPerceptions(maze, BaseKnowledge::PIT, BaseKnowledge::WIND);
            if(maze[i][j].perceptions[BaseKnowledge::WUMPUS])
                adjacentPerceptions(maze, BaseKnowledge::WUMPUS, BaseKnowledge::STINK);
        }
    }
    return maze;
}


int main()
{
    srand((unsigned int) time(NULL));
    Agent wumpusGame(size);
    bool finished = false;
    Action currentAction;
    std::vector<std::vector<Space>> maze = buildMaze();
    Coordinate* currentLocation = Coordinate::getCoordinate(0, 0);
    while(!finished)
    {
        std::cout << "===== [BEGIN] =====" << std::endl;
        std::cout << "Current location=" << currentLocation->to_string() << std::endl;
        currentAction = wumpusGame.play(maze[currentLocation->x][currentLocation->y]);
        if(currentAction.isGameFinished())
        {
            finished = true;
        }
        else
        {
            std::cout << "Current action=" << currentAction.to_string() << std::endl;
            currentLocation = currentAction.getLocation();
        }
        std::cout << "====== [END] ======" << std::endl;
    }

    std::cout << "Game Over in position=" << currentAction.getLocation()->to_string() << std::endl;
    std::cin.ignore();
    return 0;
}