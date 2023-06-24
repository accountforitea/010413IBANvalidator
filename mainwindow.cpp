#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text().trimmed(); //видалюємо пробіли з початку рядка, якщо присутні
    if (input.isEmpty()) {
        QMessageBox::information(this, "Empty", "Please enter IBAN.");
        return;
    }

    bool isValid = validateIban(input);
    if (isValid) {
        ui->res->setText("Valid");
    } else {
        ui->res->setText("Invalid");
    }

    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}

bool MainWindow::validateIban(const QString& input)
{
    QString nospaceinput = input;
    nospaceinput.remove(QRegularExpression("\\s+")); // Видаляємо пробіли

    if ( !nospaceinput.startsWith("UA")) {
        return false;
    }
    if(nospaceinput.length()<29){
        return false;
    }
    QRegularExpression regex("^[0-9]{27}$");
    QRegularExpressionMatch match = regex.match(nospaceinput.mid(2)); //перевірка чи всі сиволи вісля перших двух є цифрами у кількості 27
    return match.hasMatch();

}
