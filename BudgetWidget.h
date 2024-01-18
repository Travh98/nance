#ifndef BUDGETWIDGET_H
#define BUDGETWIDGET_H

#include <QWidget>

namespace Ui {
class BudgetWidget;
}
class BudgetDataModel;

class BudgetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BudgetWidget(QWidget *parent = nullptr);
    ~BudgetWidget();

    void setModel(BudgetDataModel* model);

private:
    Ui::BudgetWidget *ui;
};

#endif // BUDGETWIDGET_H
