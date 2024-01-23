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

    // Setup percent Needs combobox
    for(int i = 100; i >= 0; i = i - 5)
    {
        ui->comboBox_percentForNeeds->addItem(QString::number(i) + '%');
    }

    connect(ui->comboBox_percentForNeeds, &QComboBox::currentIndexChanged,
            this, &BudgetWidget::slot_onBudgetModelUpdated);

    ui->comboBox_percentForNeeds->setCurrentIndex(ui->comboBox_percentForNeeds->count() * 0.25f);


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

    m_pBudgetModel = model;
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
    slot_updateMonthlyWantsNeeds();
}

void BudgetWidget::slot_updateMonthlyWantsNeeds()
{
    if(m_pBudgetModel != nullptr)
    {
        float percentForWants = (100.0f - (ui->comboBox_percentForNeeds->currentText()).remove('%').toFloat()) / 100.0f;
        ui->lineEdit_percentForWants->setText(QString::number(percentForWants * 100.0f) + '%');
        ui->lineEdit_needsPerMonth->setText(QString::number(ui->comboBox_percentForNeeds->currentText().remove('%').toFloat() / 100.0f * m_pBudgetModel->getMonthlyTakeHome()));
        ui->lineEdit_wantsPerMonth->setText(QString::number(percentForWants * m_pBudgetModel->getMonthlyTakeHome()));
    }
}
