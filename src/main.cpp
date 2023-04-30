#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "cRunWatch.h"

class cBlock
{
public:
    void read();
    bool isBlocked(int x, int y) const;

private:
    std::set<long long> myBlocks;
    long long index(int x, int y) const;
};

class cRegion
{
public:
    void Construct(const cBlock &blocks);
};

cBlock theBlocks;
cRegion theRegions;

bool cBlock::isBlocked(int x, int y) const
{
    return (myBlocks.find(index(x, y)) != myBlocks.end());
}
long long cBlock::index(int x, int y) const
{
    return 1000000 * (long long)x + y;
}
void cBlock::read()
{
    std::cout << "Path to block file\n";
    std::string fname;
    std::cin >> fname;
    std::ifstream ifs(fname);
    if (!ifs.is_open())
    {
        std::cout << "Cannot open\n";
        exit(2);
    }
    int x, y;
    while (1)
    {
        ifs >> x >> y;
        if (ifs.eof())
            break;
        myBlocks.insert(index(x, y));
    }
}

void cRegion::Construct(const cBlock &blocks)
{
    int xright, ybottom;
    bool fB = false;
    for (int y = 0; y < 1000000; y++)
        for (int x = 0; x < 1000000; x++)
        {
            if (blocks.isBlocked(x, y))
            {
                ybottom = y - 1;
                fB = true;
                break;
            }
        }
    if (!fB)
    {
        std::cout << "0 0 100000 100000\n";
        return;
    }
    std::cout << "0 0 100000 " << ybottom << "\n";
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
            if (theBlocks.isBlocked(x, sy))
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
            if (theBlocks.isBlocked(dx, y))
                throw std::runtime_error("blocked");
            ret.push_back(std::make_pair(dx, y));
        } while (y != dy);
    }
    return ret;
}

std::vector<std::pair<int, int>>
ManhattanD(int sx, int sy, int dx, int dy)
{
    std::vector<std::pair<int, int>> ret;
    ret.push_back(std::make_pair(sx, sy));
    int deltax = dx - sx;
    int deltay = dy - sy;
    int incx = 1;
    int incy = 1;
    if (deltax < 0)
        incx = -1;
    if (deltay < 0)
        incy = -1;
    int x = sx;
    int y = sy;
    while ((x != dx) || (y != dy))
    {
        if (x == dx)
            incx = 0;
        if (y == dy)
            incy = 0;
        x += incx;
        y += incy;
        if (theBlocks.isBlocked(x, y))
            throw std::runtime_error("blocked");
        ret.push_back(std::make_pair(dx, y));
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
    try
    {
        return ManhattanXY(sx, sy, dx, dy);
    }
    catch (std::exception &e)
    {
        ;
    }
    try
    {
        return ManhattanYX(sx, sy, dx, dy);
    }
    catch (std::exception &e)
    {
        ;
    }
    try
    {
        return ManhattanD(sx, sy, dx, dy);
    }
    catch (std::exception &e)
    {
        ;
    }
    std::cout << "Blocked three ways\n";
    exit(1);
}

main()
{
    theBlocks.read();
    theRegions.Construct(theBlocks);

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
