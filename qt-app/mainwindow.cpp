#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleReply);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::loadCars);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addCar);
    loadCars();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadCars() {
    QNetworkRequest request(QUrl(apiUrl));
    manager->get(request);
}

void MainWindow::addCar() {
    QString branch = ui->branchEdit->text();
    QString model = ui->modelEdit->text();

    QUrlQuery postData;
    postData.addQueryItem("branch", branch);
    postData.addQueryItem("model", model);

    QNetworkRequest request(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager->post(request, postData.toString(QUrl::FullyEncoded).toUtf8());
}

void MainWindow::handleReply(QNetworkReply *reply) {
    QByteArray response = reply->readAll();

    if (reply->operation() == QNetworkAccessManager::GetOperation) {
        ui->tableWidget->clearContents();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonArray array = doc.array();
        ui->tableWidget->setRowCount(array.size());

        for (int i = 0; i < array.size(); ++i) {
            QJsonObject obj = array[i].toObject();
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(obj["id"].toInt())));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(obj["branch"].toString()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(obj["model"].toString()));
        }
    } else if (reply->operation() == QNetworkAccessManager::PostOperation) {
        loadCars(); // päivitä taulukko lisäyksen jälkeen
    }

    reply->deleteLater();
}
