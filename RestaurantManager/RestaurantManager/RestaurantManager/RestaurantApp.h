#ifndef RESTAURANTAPP_H
#define RESTAURANTAPP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "OrderForm.h"
#include "Restaurant.h"

class RestaurantApp : public QWidget {
    Q_OBJECT

public:
    RestaurantApp(QWidget* parent = nullptr);
    void backButtonClicked();

private slots:
    void addOrderClicked();
    void loadMenuFromFile(const std::string& filename);
    void loadOrdersFromFile(const std::string& filename);
    void deleteOrder(int row);
    void updateOrdersTable();

protected:
    void paintEvent(QPaintEvent* event);

private:
    QVBoxLayout* mainLayout;
    QTableWidget* menuTable;
    QTableWidget* ordersTable;
    QPushButton* addButton;
    OrderForm* orderForm;
    Restaurant restaurant;
};

#endif // RESTAURANTAPP_H
