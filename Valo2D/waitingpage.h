#ifndef WAITINGPAGE_H
#define WAITINGPAGE_H

#include <QWidget>

namespace Ui {
class WaitingPage;
}

class WaitingPage : public QWidget
{
    Q_OBJECT

public:
    explicit WaitingPage(QWidget *parent = nullptr);
    ~WaitingPage();

private:
    Ui::WaitingPage *ui;
};

#endif // WAITINGPAGE_H
