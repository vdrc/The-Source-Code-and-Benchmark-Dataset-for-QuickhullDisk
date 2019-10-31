#include "CircularDisk2D.h"

CircularDisk2D::CircularDisk2D()
{
    m_ID = -1;
}

CircularDisk2D::CircularDisk2D(const Point2D& center, const double& r, const int& id)
    :Circle2D(center, r)
{
    m_ID = id;
}

CircularDisk2D::CircularDisk2D(const double& pointX, const double& pointY, const double& r, const int& id)
    : Circle2D(pointX, pointY, r)
{
    m_ID = id;
}

CircularDisk2D::CircularDisk2D(const CircularDisk2D& circle, const int& id)
    : Circle2D(circle)
{
    m_ID = id;
}

CircularDisk2D::CircularDisk2D(const CircularDisk2D& disk)
    : Circle2D(disk.get_circle())
{
    m_ID = disk.get_ID();
}

CircularDisk2D::~CircularDisk2D()
{

}


bool CircularDisk2D::operator<(const CircularDisk2D& disk) const
{
    return get_radius() < disk.get_radius();
}


bool CircularDisk2D::operator>(const CircularDisk2D& disk) const
{
    return get_radius() > disk.get_radius();
}


bool CircularDisk2D::operator==(const CircularDisk2D& disk) const
{
    if (disk.m_ID == m_ID && Circle2D::operator==(disk))
    {
        return true;
    }
    else
    {
        return false;
    }
}

CircularDisk2D& CircularDisk2D::operator=(const CircularDisk2D& disk)
{
    if (this == &disk) 
    {
        return *this;
    }

    set_center_pt(disk.get_center_pt());
    set_radius(disk.get_radius());
    set_ID(disk.get_ID());

    return *this;
}

