#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include "mode_trans.h"
#include "slot.h"
#include "file_process.h"

using namespace std;
using namespace cv;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.setWindowTitle("simple ps");
    QPushButton* pushButton1 = new QPushButton("二值化", &window);
    QObject::connect(pushButton1, &QPushButton::clicked, &single_threshold_slot);

    QPushButton* pushButton2 = new QPushButton("dithering", &window);
    QObject::connect(pushButton2, &QPushButton::clicked, &dithering_slot);

    QPushButton* pushButton3 = new QPushButton("ordered_dithering", &window);
    QObject::connect(pushButton3, &QPushButton::clicked, &ordered_dithering_slot);

    QPushButton* pushButton4 = new QPushButton("直方图均衡化", &window);
    QObject::connect(pushButton4, &QPushButton::clicked, &proportion_slot);

    QPushButton* pushButton5 = new QPushButton("灰度", &window);
    QObject::connect(pushButton5, &QPushButton::clicked, &gray_slot);

    QPushButton* pushButton6 = new QPushButton("打开并保存", &window);
    QObject::connect(pushButton6, &QPushButton::clicked, &open_slot);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(pushButton1);
    layout->addWidget(pushButton2);
    layout->addWidget(pushButton3);
    layout->addWidget(pushButton4);
    layout->addWidget(pushButton5);
    layout->addWidget(pushButton6);

    window.setLayout(layout);

    window.show();
    return a.exec();




}
