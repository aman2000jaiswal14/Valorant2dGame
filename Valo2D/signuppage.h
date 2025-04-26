#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>

namespace Ui {
class SignupPage;
}

class SignupPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignupPage(QWidget *parent = nullptr);
    ~SignupPage();

private slots:
    void on_signupBtn_clicked();

    void on_backBtn_clicked();

private:
    Ui::SignupPage *ui;
};

#endif // SIGNUPPAGE_H
