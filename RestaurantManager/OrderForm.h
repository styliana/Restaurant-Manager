#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Restaurant.h"

class OrderForm : public QWidget {
    Q_OBJECT

public:
    explicit OrderForm(QWidget* parent = nullptr);

signals:
    void orderSubmitted();
    void orderAdded(const QString& orderDetailsString);
    void backButtonClicked();

private slots:
    void populateMenu();
    void addDishToOrder();
    void submitOrder();

private:
    QLabel* nameLabel;
    QLabel* quantityLabel;
    QComboBox* dishComboBox;
    QLineEdit* quantityText;
    QPushButton* addButton;
    QPushButton* submitButton;
    QPushButton* backButton;
    QTableWidget* previewTable;
    QHBoxLayout* buttonLayout;
    QLabel* totalLabel;
    std::vector<std::pair<QString, int>> orderDetails;
    Restaurant restaurant;

    double calculateTotalPrice();
};

#endif // ORDERFORM_H
