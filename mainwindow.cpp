#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QListView>
#include<QListWidget>
#include<QVBoxLayout>
#include<QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedHeight(600);
    setFixedWidth(800);
    scene = new QGraphicsScene(this);

//    Cool floating rectangle
//    setStyleSheet("background:transparent;");
//    setAttribute(Qt::WA_TranslucentBackground);
//    setWindowFlags(Qt::FramelessWindowHint);

    CircleInSquare *tool = new CircleInSquare(QRect(QPoint(0, 0), QPoint(210, 120)));

    scene->addItem(tool);
    tool->setPos(100, 100);

    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, width(), height());
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::white, Qt::SolidPattern));

//    Incomplete Docker

//    QPushButton *button = new QPushButton();
//    button->setFixedHeight(50);
//    button->setToolTip("Rectangle Tool");
//    button->setText("Rectangle");


//    QPushButton *ellipseButton = new QPushButton();
//    ellipseButton->setFixedHeight(50);
//    ellipseButton->setToolTip("Ellipse Tool");
//    ellipseButton->setText("Ellipse");

    ui->dockWidget->setFloating(true);
    ui->dockWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}




