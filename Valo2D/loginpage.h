#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void on_loginBtn_clicked();

    void on_signupBtn_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
