#ifndef ITEMSTOREPAGE_H
#define ITEMSTOREPAGE_H

#include <QDialog>
#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "gun1.h"
#include "gun2.h"
#include "QKeyEvent"
#include "datastore.h"
#include "messages.h"
#include "communicationchannel.h"
#include "structures.h"
#include "middleware.h"
namespace Ui {
class ItemStorePage;
}

class ItemStorePage : public QDialog
{
    Q_OBJECT

public:
    explicit ItemStorePage(QWidget *parent = nullptr);
    ~ItemStorePage();
    void keyPressEvent(QKeyEvent *event) override;
    void gunSelectionOfPlayer(STRUCT_GUN_SELECTED data);

private:
    Ui::ItemStorePage *ui;
    QFrame *gunFrame;
    QGridLayout *gunFrameLayout;

    QFrame *gun1Frame;
    QGridLayout *gun1FrameLayout;
    QLabel *gun1Name;
    QLabel *gun1Desc;
    QPushButton *gun1Button;

    QFrame *gun2Frame;
    QGridLayout *gun2FrameLayout;
    QLabel *gun2Name;
    QLabel *gun2Desc;
    QPushButton *gun2Button;

    QFrame *redundantFrame[9];

public:
    QFrame *eAbilityFrame;
    QGridLayout *eAbilityFrameLayout;
    QLabel *eAbilityName;
    QLabel *eAbilityDesc;
    QPushButton *eAbilityButton;


signals:
    void buyEAbilitYFromStoreSignal();

private slots:
    void gun1ButtonClickedSlot();
    void gun2ButtonClickedSlot();
    void eAbilityButtonClickedSlot();

};

#endif // ITEMSTOREPAGE_H
