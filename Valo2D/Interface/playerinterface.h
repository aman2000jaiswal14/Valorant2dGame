#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H
#include <QString>
class PlayerInterface
{
private:
    int id = 0;
    QString name;
    QString username;
    QString password;
    int rankXp;

public:
    PlayerInterface(){};
    int getId() const;
    void setId(int newId);
    QString getName() const;
    void setName(const QString &newName);
    QString getUsername() const;
    void setUsername(const QString &newUsername);
    QString getPassword() const;
    void setPassword(const QString &newPassword);
    int getRankXp() const;
    void setRankXp(int newRankXp);
    virtual void calculateRankXp() = 0;


    virtual ~PlayerInterface();

};

#endif // PLAYERINTERFACE_H
