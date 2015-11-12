#ifndef SAMPLE_H
#define SAMPLE_H

#include <QMainWindow>

namespace Ui {
class Sample;
}

class Sample : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sample(QWidget *parent = 0);
    ~Sample();

private slots:
    void serialReceived();
    void serialSend();
    void Write();
    void on_lineEdit_returnPressed();
    void on_pushButton_2_clicked();

private:
    Ui::Sample *ui;
};

#endif // SAMPLE_H
