#include "RestaurantApp.h"

RestaurantApp::RestaurantApp(QWidget* parent) : QWidget(parent), orderForm(nullptr) {
    setFixedSize(1400, 700);

    mainLayout = new QVBoxLayout(this);

    QHBoxLayout* contentLayout = new QHBoxLayout;

    QVBoxLayout* menuLayout = new QVBoxLayout;

    QLabel* menuHeader = new QLabel("MENU");
    menuHeader->setAlignment(Qt::AlignCenter);
    menuHeader->setFont(QFont("Arial", 30));
    menuLayout->addWidget(menuHeader);

    menuTable = new QTableWidget();
    menuTable->setColumnCount(3);
    menuTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Type" << "Price");
    menuTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    menuTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    menuLayout->addWidget(menuTable);

    contentLayout->addLayout(menuLayout);

    QVBoxLayout* ordersLayout = new QVBoxLayout;

    QLabel* ordersHeader = new QLabel("ORDERS");
    ordersHeader->setAlignment(Qt::AlignCenter);
    ordersHeader->setFont(QFont("Arial", 30));
    ordersLayout->addWidget(ordersHeader);

    ordersTable = new QTableWidget();
    ordersTable->setColumnCount(4); // Adjust to 4 columns
    ordersTable->setHorizontalHeaderLabels(QStringList() << "Order Number" << "Items" << "Total" << ""); // Empty label for buttons
    ordersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ordersTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ordersLayout->addWidget(ordersTable);

    contentLayout->addLayout(ordersLayout);

    mainLayout->addLayout(contentLayout);

    addButton = new QPushButton("Add Order", this);
    connect(addButton, &QPushButton::clicked, this, &RestaurantApp::addOrderClicked);
    mainLayout->addWidget(addButton);

    setLayout(mainLayout);

    loadMenuFromFile("menu.txt");
    loadOrdersFromFile("orders.txt");

    orderForm = new OrderForm();
    connect(orderForm, &OrderForm::orderSubmitted, this, &RestaurantApp::updateOrdersTable);

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
    QComboBox {
        background-color: #ffffff; /* Change dropdown background color */
        selection-background-color: #cce7ff; /* Change dropdown selection color */
        border: 1px solid #e0e0e0;
        padding: 5px;
        border-radius: 5px;
    }
    QComboBox::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: top right;
        width: 20px;
        border-left-width: 0px;
        border-left-color: transparent;
        border-top-right-radius: 3px;
        border-bottom-right-radius: 3px;
        border-left-style: solid;
    }
    QComboBox::down-arrow {
        image: url(:/images/down_arrow.png); /* Replace with your down arrow image */
    }
)";
    setStyleSheet(styleSheet);
}

void RestaurantApp::addOrderClicked() {
    qDebug() << "ADD ORDER button clicked!";
    if (orderForm) {
        delete orderForm;
    }
    orderForm = new OrderForm();
    connect(orderForm, &OrderForm::backButtonClicked, this, &RestaurantApp::backButtonClicked);
    connect(orderForm, &OrderForm::orderSubmitted, this, &RestaurantApp::updateOrdersTable);
    orderForm->show();
}


void RestaurantApp::backButtonClicked() {
    qDebug() << "BACK button clicked!";
    if (orderForm) {
        orderForm->hide();
        menuTable->show();
        ordersTable->show();
        addButton->show();
    }
}

void RestaurantApp::loadMenuFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        qDebug() << "Error opening file: " << filename.c_str();
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, type;
        double price;
        char comma;

        if (std::getline(iss, name, ',') && iss >> price) {
            if (iss >> std::ws && iss.peek() == ',') {
                iss >> comma;
            }
            std::getline(iss >> std::ws, type);

            menuTable->insertRow(row);

            QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(name));
            nameItem->setFont(QFont("Arial", 12));
            nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            menuTable->setItem(row, 0, nameItem);

            QTableWidgetItem* typeItem = new QTableWidgetItem(QString::fromStdString(type));
            typeItem->setFont(QFont("Arial", 12));
            typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            menuTable->setItem(row, 1, typeItem);

            QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(price));
            priceItem->setFont(QFont("Arial", 12));
            priceItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            menuTable->setItem(row, 2, priceItem);

            ++row;
        }
    }
    file.close();
}

void RestaurantApp::loadOrdersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        qDebug() << "Error opening file: " << QString::fromStdString(filename);
        return;
    }

    ordersTable->setRowCount(0);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string orderNumberStr, itemsString, totalStr;
        int orderNumber;
        double total;

        if (std::getline(iss, orderNumberStr, ',')) {
            std::stringstream orderNumberSS(orderNumberStr);
            orderNumberSS >> orderNumber;
        }
        else {
            qDebug() << "Error parsing order number!";
            continue;
        }

        std::vector<std::string> items;
        std::string item;
        iss.ignore();
        std::getline(iss, item, ',');
        items.push_back(item);

        while (std::getline(iss >> std::ws, item, ',')) {
            bool isNumber = std::all_of(item.begin(), item.end(), [](char c) { return std::isdigit(c) || c == '.'; });
            if (isNumber) {
                totalStr = item;
                break;
            }
            items.push_back(item);
        }

        itemsString = QString::fromStdString(std::accumulate(items.begin(), items.end(), std::string(), [](std::string a, std::string b) { return a.empty() ? b : a + ", " + b; })).toStdString();
        std::stringstream totalSS(totalStr);
        totalSS >> total;

        int row = ordersTable->rowCount();
        ordersTable->insertRow(row);

        QTableWidgetItem* orderNumberItem = new QTableWidgetItem(QString::number(orderNumber));
        ordersTable->setItem(row, 0, orderNumberItem);

        QTableWidgetItem* itemsItem = new QTableWidgetItem(QString::fromStdString(itemsString));
        ordersTable->setItem(row, 1, itemsItem);

        QTableWidgetItem* totalItem = new QTableWidgetItem(QString::number(total));
        ordersTable->setItem(row, 2, totalItem);

        QPushButton* deleteButton = new QPushButton("Delete");
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            QPushButton* button = qobject_cast<QPushButton*>(sender());
            if (button) {
                int rowToDelete = ordersTable->indexAt(button->pos()).row();
                deleteOrder(rowToDelete);
            }
            });
        ordersTable->setCellWidget(row, 3, deleteButton);

    }
    file.close();
}

void RestaurantApp::deleteOrder(int row) {
    int orderNumber = ordersTable->item(row, 0)->text().toInt();

    ordersTable->removeRow(row);

    std::ifstream infile("orders.txt");
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string orderNumberStr;
        std::getline(iss, orderNumberStr, ',');

        int currentOrderNumber = std::stoi(orderNumberStr);

        // If the order number doesn't match the one we want to delete, keep it
        if (currentOrderNumber != orderNumber) {
            lines.push_back(line);
        }
    }

    infile.close();

    // Rewrite the orders file with the updated data
    std::ofstream outfile("orders.txt");
    for (const auto& updatedLine : lines) {
        outfile << updatedLine << std::endl;
    }
    outfile.close();
}

void RestaurantApp::updateOrdersTable() {
    // Clear the existing contents of the orders table
    ordersTable->clearContents();
    // Reload orders from file
    loadOrdersFromFile("orders.txt");
}

void RestaurantApp::paintEvent(QPaintEvent* event) {
    // Empty implementation to satisfy linker
}
