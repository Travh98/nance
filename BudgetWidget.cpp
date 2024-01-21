#include "BudgetWidget.h"
#include "ui_BudgetWidget.h"
#include "BudgetDataModel.h"

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

}

BudgetWidget::~BudgetWidget()
{
    delete ui;
}

void BudgetWidget::setModel(BudgetDataModel *model)
{
    ui->tableView_annual->setModel(model);

    connect(model, &BudgetDataModel::dataChanged,
            this, &BudgetWidget::slot_onBudgetModelUpdated);
}

void BudgetWidget::slot_onBudgetModelUpdated()
{

}
