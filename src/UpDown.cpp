#include <GlobalParams.h>
#include <UpDown.h>

Graph::Graph()
{
    std::vector<std::vector<int>> topologyMap= readFileMap();
    int length = size;
    int i = 0, j = 0, temp = 0, index = 0;
    for (auto k : topologyMap)
    {
        j = 0;
        for (int a : k)
        {
            if (a == 0)
            {
                j++;
                continue;
            }
            index = i * length + j;
            // std::cout << index << " ";
            nodes[index] = new Node(i, j, length);
            j++;
        }
        // std::cout << std::endl;
        i++;
    }

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            index = i * length + j;
            temp = topologyMap[i][j];
            if (temp == 0)
            {
                continue;
            }
            else if (temp == 1)
            {
                if ((j != 0) && (topologyMap[i][j - 1] != 0) && (topologyMap[i][j - 1] != 2))
                {
                    nodes[index]->neighbors[DIRECTION_WEST] = nodes[i * length + j - 1];
                    // std::cout << "What's wrong: " << index << std::endl;
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_WEST] = nullptr;
                }

                if ((j != (length - 1)) && (topologyMap[i][j + 1] != 0) && (topologyMap[i][j + 1] != 2))
                {
                    nodes[index]->neighbors[DIRECTION_EAST] = nodes[i * length + j + 1];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_EAST] = nullptr;
                }

                if ((i != 0) && (topologyMap[i - 1][j] != 0) && (topologyMap[i - 1][j] != 3))
                {
                    nodes[index]->neighbors[DIRECTION_NORTH] = nodes[(i - 1) * length + j];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_NORTH] = nullptr;
                }

                if ((i != (length - 1)) && (topologyMap[i + 1][j] != 0) && (topologyMap[i + 1][j] != 3))
                {
                    nodes[index]->neighbors[DIRECTION_SOUTH] = nodes[(i + 1) * length + j];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_SOUTH] = nullptr;
                }
            }
            else if (temp == 2)
            {
                // north/south only
                nodes[index]->neighbors[DIRECTION_WEST] = nullptr;
                nodes[index]->neighbors[DIRECTION_EAST] = nullptr;

                if ((i != 0) && (topologyMap[i - 1][j] != 0) && (topologyMap[i - 1][j] != 3))
                {
                    nodes[index]->neighbors[DIRECTION_NORTH] = nodes[(i - 1) * length + j];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_NORTH] = nullptr;
                }

                if ((i != (length - 1)) && (topologyMap[i + 1][j] != 0) && (topologyMap[i + 1][j] != 3))
                {
                    nodes[index]->neighbors[DIRECTION_SOUTH] = nodes[(i + 1) * length + j];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_SOUTH] = nullptr;
                }
            }
            else if (temp == 3)
            {
                // west/east only
                nodes[index]->neighbors[DIRECTION_NORTH] = nullptr;
                nodes[index]->neighbors[DIRECTION_SOUTH] = nullptr;

                if ((j != 0) && (topologyMap[i][j - 1] != 0) && (topologyMap[i][j - 1] != 2))
                {
                    nodes[index]->neighbors[DIRECTION_WEST] = nodes[i * length + j - 1];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_WEST] = nullptr;
                }

                if ((j != (length - 1)) && (topologyMap[i][j + 1] != 0) && (topologyMap[i][j + 1] != 2))
                {
                    nodes[index]->neighbors[DIRECTION_EAST] = nodes[i * length + j + 1];
                }
                else
                {
                    nodes[index]->neighbors[DIRECTION_EAST] = nullptr;
                }
            }
        }
    }
}

std::vector<std::vector<int>> Graph::readFileMap()
{
    std::ifstream infile("irregular.topo");
    std::vector<std::vector<int>> topo;
    int i = 0, j = 0;
    if (infile.is_open())
    {
        std::string line;
        std::string firstTwo;
        while (std::getline(infile, line))
        {
            if (line.size() == 0)
            {
                break;
            }

            firstTwo = line.substr(0, 2);
            if (firstTwo == std::string("//"))
                continue;

            std::istringstream iss(line);
            if (line.substr(0, 5) == std::string("size:"))
            {
                iss >> firstTwo;
                iss >> size;
                continue;
            }

            int number;
            topo.push_back(std::vector<int>(size));
            j = 0;
            while (iss >> number)
            {
                topo[i][j] = number;
                j += 1;
            }
            i += 1;
        }
    }
    infile.close();
    return topo;
}

bool Graph::downContain(int currentIndex, int findIndex)
{
    if (currentIndex == findIndex)
    {
        // tempPath.push_back(currentIndex);
        return true;
    }

    Node *currentNode = nodes[currentIndex];
    int downsize = currentNode->down.size();
    bool found = false;
    if ((downsize == 0))
        return false;

    for (int i = 0; i < downsize; i++)
    {
        if (downContain((currentNode->down[i])->id, findIndex))
        {
            // tempPath.push_back(currentIndex);
            found = true;
            break;
        }
    }
    return found;
}

DOWNUP Graph::findPath(int currentIndex, int findIndex, int comingIndex)
{
    tempPath.clear();
    if (currentIndex == findIndex)
    {
        tempPath.push_back(currentIndex);
        return DOWN;
    }
    DOWNUP dir = UP;
    Node *currentNode = nodes[currentIndex];
    int downsize = currentNode->down.size();
    int nextIndex = 0;
    for (int i = 0; i < downsize; i++)
    {
        nextIndex = (currentNode->down[i])->id;
        if (nextIndex == comingIndex)
        {
            continue;
        }
        if (downContain(nextIndex, findIndex))
        {
            dir = DOWN;
            tempPath.push_back(nextIndex);
            break;
        }
    }
    return dir;
}

void Graph::addEdge(int u, int v, int DIREC)
{
    nodes[u]->neighbors[DIREC] = nodes[v];
    int op_direc = ((DIREC >= 2) ? (DIREC - 2) : DIREC + 2);
    nodes[v]->neighbors[op_direc] = nodes[u];
}

void Graph::dfsSpanningTree(int startNodeId)
{
    std::stack<Node *> stack;
    Node *startNode = nodes[startNodeId];
    stack.push(startNode);

    while (!stack.empty())
    {
        Node *currentNode = stack.top();
        stack.pop();

        // if (!currentNode->visited) {
        currentNode->visited = true;
        // std::cout << "Node " << currentNode->id << " visited." << std::endl;
        Node *neighbor;
        for (int dir = 0; dir < DIRECTIONS; dir++)
        {
            neighbor = currentNode->neighbors[dir];
            if (neighbor == nullptr)
                continue;
            if (!neighbor->visited)
            {
                neighbor->visited = true;
                stack.push(neighbor);
                neighbor->up.push_back(currentNode);
                currentNode->down.push_back(neighbor);
            }
        }
        // }
    }
}

void Graph::bfsSpanningTree(int startNodeId)
{
    std::queue<Node *> myQueue;
    Node *startNode = nodes[startNodeId];
    myQueue.push(startNode);

    while (!myQueue.empty())
    {
        Node *currentNode = myQueue.front();
        myQueue.pop();
        currentNode->visited = true;
        Node *neighbor;
        for (int dir = 0; dir < DIRECTIONS; dir++)
        {
            neighbor = currentNode->neighbors[dir];
            if (neighbor == nullptr)
                continue;
            if (!neighbor->visited)
            {
                neighbor->visited = true;
                myQueue.push(neighbor);
                neighbor->up.push_back(currentNode);
                currentNode->down.push_back(neighbor);
            }
        }
    }
}

void Graph::build(int choice) {
    int length = size;
    int startIndex = 7*length+7;
    if (choice==0){
        dfsSpanningTree(startIndex);
    } else {
        bfsSpanningTree(startIndex);
    }
    // int randomNode = 155;
    // int randomEndNode = 244;
    // DOWNUP dir = UP;
    // int incomingIndex = NO_INCOMING_INDEX;
    // std::vector<int> path;
    // while(dir == UP){
    //     dir = graph.findPath(randomNode,randomEndNode,incomingIndex);
    //     if (dir == UP){
    //         incomingIndex = randomNode;
    //         path.push_back(randomNode);
    //         randomNode = graph.nodes[randomNode]->up[0]->id;
    //     }
    // }
    // for (auto it = graph.tempPath.rbegin(); it != graph.tempPath.rend(); ++it){
    //     path.push_back(*it);
    // }
}