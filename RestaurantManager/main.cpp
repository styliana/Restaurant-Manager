#include "RestaurantApp.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // Initialize the QApplication object

    // Create and show the main window
    RestaurantApp restaurantApp;
    restaurantApp.show();

    return app.exec(); // Start the event loop
}
