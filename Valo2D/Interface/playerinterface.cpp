#include "playerinterface.h"

int PlayerInterface::getId() const
{
    return id;
}

void PlayerInterface::setId(int newId)
{
    id = newId;
}

QString PlayerInterface::getName() const
{
    return name;
}

void PlayerInterface::setName(const QString &newName)
{
    name = newName;
}

QString PlayerInterface::getUsername() const
{
    return username;
}

void PlayerInterface::setUsername(const QString &newUsername)
{
    username = newUsername;
}

QString PlayerInterface::getPassword() const
{
    return password;
}

void PlayerInterface::setPassword(const QString &newPassword)
{
    password = newPassword;
}

int PlayerInterface::getRankXp() const
{
    return rankXp;
}

void PlayerInterface::setRankXp(int newRankXp)
{
    rankXp = newRankXp;
}

PlayerInterface::~PlayerInterface()
{

}


