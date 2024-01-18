#include "BudgetWidget.h"
#include "ui_BudgetWidget.h"
#include "BudgetDataModel.h"

BudgetWidget::BudgetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BudgetWidget)
{
    ui->setupUi(this);
}

BudgetWidget::~BudgetWidget()
{
    delete ui;
}

void BudgetWidget::setModel(BudgetDataModel *model)
{
    ui->tableView_annual->setModel(model);
}
