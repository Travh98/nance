#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class BudgetWidget;
class BudgetDataModel;
class UserExpensesModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // Budgeting
    BudgetWidget* m_pBudgetWidget;
    BudgetDataModel* m_pBudgetModel;
    UserExpensesModel* m_pNeedsModel;
    UserExpensesModel* m_pWantsModel;


};
#endif // MAINWINDOW_H
