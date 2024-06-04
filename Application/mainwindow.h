#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QIODevice>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_togglePushButton_released();

    void on_cVelocity_valueChanged(double arg1);

    void on_mVelocity_valueChanged(double arg1);

    void on_tVelocity_valueChanged(double arg1);

    void on_ru_clicked();

    void on_en_clicked();

    void on_de_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort* port;
    bool opened;
    QTranslator translator;
    QString lang;
    void timerEvent(QTimerEvent *e) override;

};

void checkForColours(Ui::MainWindow *ui);
#endif // MAINWINDOW_H
