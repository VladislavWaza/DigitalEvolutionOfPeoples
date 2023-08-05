#include <QRandomGenerator>
#include "cell.h"

QPoint const Cell::_directions[] = {QPoint(-1, 0), QPoint(-1, -1), QPoint(0, -1),
                                QPoint(1, -1), QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1)};

Cell::Cell(GenomeInitType genomeInitType)
    :QObject()
{
    _genom = new uint8_t[_size];
    if (genomeInitType == GenomeInitType::Random)
    {
        for (int i = 0; i < _size/4; ++i)
            *reinterpret_cast<uint32_t*>(&_genom[4*i]) = QRandomGenerator::system()->generate();
    }
    for (int i = 0; i < _size; ++i)
        _genom[i] %= (_maxGene + 1);
    _food = 1;
    _strength = 1;
    _direction = Cell::_directions[0];
    _isAlive = true;
    _color = Qt::darkCyan;
}

Cell::Cell(const Cell &parent)
    :QObject()
{
    _genom = new uint8_t[_size];
    for (int i = 0; i < _size; ++i)
        _genom[i] = parent._genom[i];
    if (QRandomGenerator::system()->bounded(100) < Cell::_percentMutation)
       _genom[QRandomGenerator::system()->bounded(_size)] = QRandomGenerator::system()->bounded(_maxGene + 1);
    _food = 1;
    _strength = 1;
    _direction = Cell::_directions[0];
    _isAlive = true;
    _color = Qt::darkCyan;
}

Cell::~Cell()
{
}

QColor Cell::getColor()
{
    return _color;
}

void Cell::getGenom(uint8_t *ptr) const
{
    for (int i = 0; i < _size; ++i)
        ptr[i] = _genom[i];
}

void Cell::setDirection(QPoint direction)
{
    _direction = direction;
}

QPoint Cell::getDirection()
{
    return _direction;
}

int Cell::getStrength()
{
    return _strength;
}

void Cell::setStrength(int strength)
{
    if (strength >= 1 && strength <= _maxStrength)
        _strength = strength;
}

int Cell::getFood()
{
    return _food;
}

void Cell::increaseFood(int food)
{
    _food += food;
    if (_food > _maxFood)
        _food = _maxFood;
}

bool Cell::isAlive()
{
    return _isAlive;
}

void Cell::kill()
{
    _isAlive = false;
    emit signalKilled();
}

void Cell::survive()
{
    _food -= _strength;
    if (_food < 0)
        kill();
}
