
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadCars();
    void addCar();
    void handleReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    const QString apiUrl = "http://localhost:8000/cars"; // Adjust if needed
};

#endif // MAINWINDOW_H
