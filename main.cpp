#include <QApplication>
#include<loginwidget.h>
#include "welcomewidget.h"
#include "user.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setStyle("plastique");
    LoginWidget* loginWidget = new LoginWidget();
    loginWidget->show();
    return app.exec();
}
