#ifndef CALFATIGA_H
#define CALFATIGA_H

#include <QMainWindow>

namespace Ui {
class CalFatiga;
}

class CalFatiga : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalFatiga(QWidget *parent = nullptr);
    ~CalFatiga();

private slots:
    void on_pusButton_clicked();

private:
    Ui::CalFatiga *ui;
};

#endif // CALFATIGA_H
