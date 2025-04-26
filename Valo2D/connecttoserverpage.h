#ifndef CONNECTTOSERVERPAGE_H
#define CONNECTTOSERVERPAGE_H

#include <QWidget>

namespace Ui {
class ConnectToServerPage;
}

class ConnectToServerPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectToServerPage(QWidget *parent = nullptr);
    ~ConnectToServerPage();
    void setPlayerName(QString playerName);
    void setPlayerXP(int rankXp);

private slots:
    void on_playBtn_clicked();

    void on_playDominationBtn_clicked();

private:
    Ui::ConnectToServerPage *ui;
};

#endif // CONNECTTOSERVERPAGE_H
