#include "OrderForm.h"
#include "RestaurantApp.h"

OrderForm::OrderForm(QWidget* parent)
    : QWidget(parent),
    nameLabel(new QLabel("Dish:", this)),
    quantityLabel(new QLabel("Quantity:", this)),
    dishComboBox(new QComboBox(this)),
    quantityText(new QLineEdit(this)),
    addButton(new QPushButton("Add Dish to Order", this)),
    submitButton(new QPushButton("Submit Order", this)),
    backButton(new QPushButton("Back", this)),
    previewTable(new QTableWidget(this)),
    buttonLayout(new QHBoxLayout()),
    totalLabel(new QLabel("Total Price: 0", this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel);
    layout->addWidget(dishComboBox);
    layout->addWidget(quantityLabel);
    layout->addWidget(quantityText);

    // Setup buttons layout
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(submitButton);
    buttonLayout->addWidget(backButton);
    layout->addLayout(buttonLayout);

    // Setup preview table
    previewTable->setColumnCount(2);
    previewTable->setHorizontalHeaderLabels(QStringList() << "Dish" << "Quantity");
    previewTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(previewTable);

    // Add total label to the layout
    layout->addWidget(totalLabel);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, &OrderForm::addDishToOrder);
    connect(submitButton, &QPushButton::clicked, this, &OrderForm::submitOrder);
    connect(backButton, &QPushButton::clicked, this, &OrderForm::close);

    // Populate the menu when OrderForm is created
    populateMenu();

    QString styleSheet = R"(
        QWidget {
            background-color: #fafafa;
            font-family: Arial, sans-serif;
            color: #333333;
        }
        QLabel {
            color: #005582;
            font-weight: bold;
        }
        QTableWidget {
            background-color: #ffffff;
            border: 1px solid #e0e0e0;
            gridline-color: #e0e0e0;
            selection-background-color: #cce7ff;
            selection-color: #333333;
            border-radius: 10px;
        }
        QTableWidget::item {
            padding: 10px;
            color: #333333;
        }
        QTableWidget::item:selected {
            background-color: #cce7ff;
            color: #333333;
        }
        QHeaderView::section {
            background-color: #005582;
            color: #ffffff;
            padding: 5px;
            border: 1px solid #e0e0e0;
            border-radius: 5px;
        }
        QPushButton {
            background-color: #00c2c7;
            color: #ffffff;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            transition: background-color 0.3s ease;
        }
        QPushButton:hover {
            background-color: #0086ad;
        }
        QPushButton:pressed {
            background-color: #005582;
        }
    )";
    setStyleSheet(styleSheet);
}

void OrderForm::populateMenu() {
    try {
        if (!restaurant.loadMenuFromFile("menu.txt")) {
            throw std::runtime_error("Failed to load menu.");
        }

        const std::vector<Dish>& menu = restaurant.getMenu();

        std::vector<Dish> sortedMenu = menu;
        std::sort(sortedMenu.begin(), sortedMenu.end(), [](const Dish& a, const Dish& b) {
            return a.getType() == b.getType() ? a.getName() < b.getName() : a.getType() < b.getType();
            });

        dishComboBox->clear();

        for (const auto& dish : sortedMenu) {
            QString dishName = QString::fromStdString(dish.getName()) + " (" + QString::fromStdString(dish.getType()) + ")";
            dishComboBox->addItem(dishName);
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void OrderForm::addDishToOrder() {
    QString selectedDish = dishComboBox->currentText().split(" (").first();
    QString quantityStr = quantityText->text();
    bool ok;
    int quantity = quantityStr.toInt(&ok);

    // Check if the quantity input is valid
    if (selectedDish.isEmpty() || !ok) {
        QMessageBox::warning(this, "Invalid Input", "Please select a valid dish and enter a valid quantity.");
        return;
    }

    // Check if the quantity exceeds the maximum limit (20)
    if (quantity > 20) {
        QMessageBox::warning(this, "Maximum Limit Exceeded", "Maximum number of the same item reached (20).");
        return;
    }

    // Rest of the code to add the dish to order
    orderDetails.push_back(std::make_pair(selectedDish, quantity));

    int row = previewTable->rowCount();
    previewTable->insertRow(row);
    previewTable->setItem(row, 0, new QTableWidgetItem(selectedDish));
    previewTable->setItem(row, 1, new QTableWidgetItem(quantityStr));

    dishComboBox->setCurrentIndex(0);
    quantityText->clear();

    calculateTotalPrice();
}


double OrderForm::calculateTotalPrice() {
    double totalPrice = 0.0;

    for (const auto& pair : orderDetails) {
        QString dish = pair.first;
        int quantity = pair.second;

        try {
            double dishPrice = restaurant.getDishPrice(dish.toStdString());

            if (dishPrice < 0) {
                throw std::runtime_error("Invalid price for dish: " + dish.toStdString());
            }

            double subtotal = dishPrice * quantity;
            totalPrice += subtotal;
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }

    totalLabel->setText(QString("Total Price: %1").arg(totalPrice));

    return totalPrice;
}

void OrderForm::submitOrder() {
    try {
        if (orderDetails.empty()) {
            throw std::runtime_error("This order is empty. Add the items.");
        }

        int orderNumber = QTime::currentTime().msec();

        QString orderDetailsString = QString::number(orderNumber) + ", ";
        double totalPrice = calculateTotalPrice();
        for (const auto& pair : orderDetails) {
            QString dish = pair.first;
            int quantity = pair.second;
            orderDetailsString += QString("%1 %2, ").arg(quantity).arg(dish);
        }
        orderDetailsString += QString::number(static_cast<int>(totalPrice));

        QFile file("orders.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            throw std::runtime_error("Failed to save order to file.");
        }

        QTextStream out(&file);
        out << orderDetailsString << "\n";
        file.close();

        emit orderSubmitted();
        emit orderAdded(orderDetailsString);

        previewTable->clearContents();
        previewTable->setRowCount(0);

        orderDetails.clear();
        totalLabel->setText("Total Price: 0");

    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
