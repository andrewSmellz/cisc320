#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget w;
    auto *layout = new QVBoxLayout(&w);
    auto *label = new QLabel(QString("Qt %1 works").arg(qVersion()));
    auto *button = new QPushButton("Click me");

    int clicks = 0;
    QObject::connect(button, &QPushButton::clicked, [&] {
        label->setText(QString("Clicked %1 times").arg(++clicks));
    });

    layout->addWidget(label);
    layout->addWidget(button);
    w.setWindowTitle("Qt test");
    w.show();
    return app.exec();
}