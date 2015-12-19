
#include <iostream>
#include <vector>
#include "Agent.h"

std::vector<std::vector<Space>> buildMaze()
{
    std::vector<std::vector<Space>> maze;
    for(int i = 0; i < 4 ; ++i)
    {
        maze.push_back(std::vector<Space>());
        for(int j = 0; j < 4; ++j)
        {
            maze[i].push_back(Space(i, j));
        }
    }
    maze[1][0].perceptions[BaseKnowledge::wind] = true;
    maze[2][0].perceptions[BaseKnowledge::pit] = true;
    maze[3][0].perceptions[BaseKnowledge::wind] = true;
    maze[0][1].perceptions[BaseKnowledge::stink] = true;
    maze[2][1].perceptions[BaseKnowledge::wind] = true;
    maze[0][2].perceptions[BaseKnowledge::wumpus] = true;
    maze[1][2].perceptions[BaseKnowledge::stink] = true;
    maze[1][2].perceptions[BaseKnowledge::gold] = true;
    maze[1][2].perceptions[BaseKnowledge::wind] = true;
    maze[2][2].perceptions[BaseKnowledge::pit] = true;
    maze[3][2].perceptions[BaseKnowledge::wind] = true;
    maze[0][3].perceptions[BaseKnowledge::stink] = true;
    maze[2][3].perceptions[BaseKnowledge::wind] = true;
    maze[3][3].perceptions[BaseKnowledge::pit] = true;
    return maze;
}


int main()
{
    srand((unsigned int) time(NULL));
    Agent wumpusGame(4);
    bool finished = false;
    Action currentAction;
    std::vector<std::vector<Space>> maze = buildMaze();
    Coordinate* currentLocation = Coordinate::getCoordinate(0, 0);
    while(!finished)
    {
        std::cout << "===== [BEGIN] =====" << std::endl;
        std::cout << "Current location=" << currentLocation->to_string() << std::endl;
        currentAction = wumpusGame.play(maze[currentLocation->x][currentLocation->y]);
        std::cout << "Current action=" << currentAction.to_string() << std::endl;
        if(currentAction.isGameFinished())
        {
            finished = true;
        }
        currentLocation = currentAction.getLocation();
        std::cout << "====== [END] ======" << std::endl;
    }


    std::cin.ignore();
    return 0;
}