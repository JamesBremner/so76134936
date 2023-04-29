#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "cRunWatch.h"

std::vector<std::pair<int, int>> path(int sx, int sy, int dx, int dy)
{

    std::vector<std::pair<int, int>> ret;
    ret.push_back(std::make_pair(sx, sy));
    int deltax = dx - sx;
    int deltay = dy - sy;
    if (deltax)
    {
        int inc = 1;
        if (deltax < 0)
            inc = -1;
        int x = sx;
        do
        {
            x += inc;
            ret.push_back(std::make_pair(x, sy));
        } while (x != dx);
    }
    if (deltay)
    {
        int inc = 1;
        if (deltay < 0)
            inc = -1;
        int y = sy;
        do
        {
            y += inc;
            ret.push_back(std::make_pair(dx, y));
        } while (y != dy);
    }
    return ret;
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
        vpath = path(sx, sy, dx, dy);
    }
    	
    raven::set::cRunWatch::Report();

    for (auto &p : vpath)
        std::cout << p.first << " " << p.second << "\n";

    return 0;
}
