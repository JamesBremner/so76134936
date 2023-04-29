#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "cRunWatch.h"

bool isBlocked(int x, int y)
{
    return false;
}

std::vector<std::pair<int, int>>
ManhattanX(int sx, int sy, int dx, int dy)
{
    std::vector<std::pair<int, int>> ret;
    ret.push_back(std::make_pair(sx, sy));
    int deltax = dx - sx;
    if (deltax)
    {
        int inc = 1;
        if (deltax < 0)
            inc = -1;
        int x = sx;
        do
        {
            x += inc;
            if (isBlocked(x, sy))
                throw std::runtime_error("blocked");
            ret.push_back(std::make_pair(x, sy));
        } while (x != dx);
    }
    return ret;
}

std::vector<std::pair<int, int>>
ManhattanY(int sx, int sy, int dx, int dy)
{
    std::vector<std::pair<int, int>> ret;
    ret.push_back(std::make_pair(sx, sy));
    int deltay = dy - sy;
    if (deltay)
    {
        int inc = 1;
        if (deltay < 0)
            inc = -1;
        int y = sy;
        do
        {
            y += inc;
            if (isBlocked(dx, y))
                throw std::runtime_error("blocked");
            ret.push_back(std::make_pair(dx, y));
        } while (y != dy);
    }
    return ret;
}

std::vector<std::pair<int, int>>
ManhattanXY(int sx, int sy, int dx, int dy)
{
    std::vector<std::pair<int, int>> ret;

    ret = ManhattanX(sx, sy, dx, dy);

    auto pathy = ManhattanY(dx, sy, dx, dy);

    ret.insert(
        ret.end(),
        pathy.begin() + 1,
        pathy.end());

    return ret;
}

std::vector<std::pair<int, int>>
ManhattanYX(int sx, int sy, int dx, int dy)
{
    std::vector<std::pair<int, int>> ret;

    ret = ManhattanY(sx, sy, dx, dy);

    auto pathx = ManhattanX(sx, dy, dx, dy);

    ret.insert(
        ret.end(),
        pathx.begin() + 1,
        pathx.end());

    return ret;
}

std::vector<std::pair<int, int>>
Manhattan(int sx, int sy, int dx, int dy)
{
    try {
        return ManhattanXY(sx, sy, dx, dy);
    }
    catch( std::exception& e )
    {
        try {
            return ManhattanYX(sx, sy, dx, dy);
        }
        catch(  std::exception& e )
        {
            ;
        }
    }
    std::cout << "Blocked both ways\n";
    exit(1);
}

main()
{
    std::cout << "Input source location (x  y ) and destination location, e.g:\n"
                 " 1 3 6 7\n";
    int sx, sy, dx, dy;
    std::cin >> sx >> sy >> dx >> dy;

    std::vector<std::pair<int, int>> vpath;
    raven::set::cRunWatch::Start();
    {
        raven::set::cRunWatch aWatcher("path calculation");
        vpath = Manhattan(sx, sy, dx, dy);
    }

    raven::set::cRunWatch::Report();

    for (auto &p : vpath)
        std::cout << p.first << " " << p.second << "\n";

    return 0;
}
