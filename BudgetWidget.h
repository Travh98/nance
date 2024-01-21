#ifndef BUDGETWIDGET_H
#define BUDGETWIDGET_H

#include <QWidget>

namespace Ui {
class BudgetWidget;
}
class BudgetDataModel;
class UserExpensesModel;

class BudgetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BudgetWidget(QWidget *parent = nullptr);
    ~BudgetWidget();

    void setBudgetModel(BudgetDataModel* model);
    void setNeedsModel(UserExpensesModel* model);
    void setWantsModel(UserExpensesModel* model);

private slots:
    void slot_onBudgetModelUpdated();

private:
    Ui::BudgetWidget *ui;
};

#endif // BUDGETWIDGET_H
