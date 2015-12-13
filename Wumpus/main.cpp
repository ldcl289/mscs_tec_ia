
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
            maze[i].push_back(Space());
        }
    }
    maze[0][1].perceptions[BaseKnowledge::wind] = true;
    maze[0][2].perceptions[BaseKnowledge::pit] = true;
    maze[0][3].perceptions[BaseKnowledge::wind] = true;
    maze[1][0].perceptions[BaseKnowledge::stink] = true;
    maze[1][2].perceptions[BaseKnowledge::wind] = true;
    maze[2][0].perceptions[BaseKnowledge::wumpus] = true;
    maze[2][1].perceptions[BaseKnowledge::stink] = true;
    maze[2][1].perceptions[BaseKnowledge::gold] = true;
    maze[2][1].perceptions[BaseKnowledge::wind] = true;
    maze[2][2].perceptions[BaseKnowledge::pit] = true;
    maze[2][3].perceptions[BaseKnowledge::wind] = true;
    maze[3][0].perceptions[BaseKnowledge::stink] = true;
    maze[3][2].perceptions[BaseKnowledge::wind] = true;
    maze[3][3].perceptions[BaseKnowledge::pit] = true;
    return maze;
}


int main()
{
    Agent wumpusGame(4);
    bool finished = false;
    Action currentAction;
    std::vector<std::vector<Space>> maze = buildMaze();
    Coordinate currentLocation;
    currentLocation.x = 0;
    currentLocation.y = 0;
    while(!finished)
    {
        currentAction = wumpusGame.play(maze[currentLocation.x][currentLocation.y]);
        if(currentAction.isGameFinished())
        {
            finished = true;
        }
        currentLocation = currentAction.getLocation();
    }


    std::cin.ignore();
    return 0;
}