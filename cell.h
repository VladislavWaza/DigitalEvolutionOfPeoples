#ifndef CLAN_H
#define CLAN_H
#include <QPoint>
#include <QObject>
#include <QColor>
class Clan : public QObject
{
    Q_OBJECT
public:
    enum class GenomeInitType{Random};
    Clan(GenomeInitType genomeInitType = GenomeInitType::Random);
    Clan(const Clan& parent);
    ~Clan();

    QColor getColor();

    void getGenom(uint8_t *ptr) const;

    void setDirection(QPoint direction);
    QPoint getDirection();

    int getStrength();
    void setStrength(int strength);

    int getFood();
    void increaseFood(int food);

    bool isAlive();
    void kill();

    void survive();

    static const int _maxFood = 1000;
    static const int _percentMutation = 25;
    static const int _maxGene = 17;
    static const int _maxStrength = 4;
    static const int _size = 8; //должно делиться на 4
    static const QPoint _directions[];
signals:
    void signalKilled();
private:
    uint8_t* _genom;
    int _food;
    int _strength;
    QPoint _direction;
    bool _isAlive;
    QColor _color;
};

#endif // CLAN_H