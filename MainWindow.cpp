#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "BudgetWidget.h"
#include "BudgetDataModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Nance");

    m_pBudgetModel = new BudgetDataModel(this);
    m_pBudgetWidget = new BudgetWidget(this);
    m_pBudgetWidget->setModel(m_pBudgetModel);

    ui->tabWidget_mainSections->addTab(m_pBudgetWidget, "Budget");
    ui->tabWidget_mainSections->addTab(new QWidget(this), "Monthly");
    ui->tabWidget_mainSections->addTab(new QWidget(this), "Overall");
}

MainWindow::~MainWindow()
{
    delete ui;
}

