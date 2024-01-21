#include "BudgetWidget.h"
#include "ui_BudgetWidget.h"

#include "BudgetDataModel.h"
#include "UserExpensesModel.h"

BudgetWidget::BudgetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BudgetWidget)
{
    ui->setupUi(this);

    // No selecting
    ui->tableView_annual->setSelectionBehavior(QAbstractItemView::SelectionBehavior());
    ui->tableView_annual->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->tableView_annual->resizeColumnsToContents();
    ui->tableView_annual->horizontalHeader()->hide();

    ui->tableView_needs->setCornerButtonEnabled(false);
    ui->tableView_needs->verticalHeader()->hide();
    ui->tableView_wants->setCornerButtonEnabled(false);
    ui->tableView_wants->verticalHeader()->hide();

}

BudgetWidget::~BudgetWidget()
{
    delete ui;
}

void BudgetWidget::setBudgetModel(BudgetDataModel *model)
{
    ui->tableView_annual->setModel(model);

    connect(model, &BudgetDataModel::dataChanged,
            this, &BudgetWidget::slot_onBudgetModelUpdated);
}

void BudgetWidget::setNeedsModel(UserExpensesModel *model)
{
    ui->tableView_needs->setModel(model);
}

void BudgetWidget::setWantsModel(UserExpensesModel *model)
{
    ui->tableView_wants->setModel(model);
}

void BudgetWidget::slot_onBudgetModelUpdated()
{

}
