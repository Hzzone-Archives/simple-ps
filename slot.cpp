//
// Created by 黄智忠 on 19/6/2018.
//

#include "slot.h"
#include "file_process.h"

void single_threshold_slot()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString("Open Image"), "/Users/hzzone/Desktop/image", QString("Image Files (*.png *.jpg *.bmp)"));
    bool ok;
    double threshold = QInputDialog::getDouble(nullptr, QString("QInputDialog::getDouble()"),
                                               QString("Amount:"), 100.0, 0.0, 255.0, 10, &ok);
    if (ok)
    {
        QByteArray ba = fileName.toLatin1();
        char* file_name = ba.data();
        cout<<file_name<<endl;
        Mat mat = imread(file_name, 0);
        Mat mat1 = single_threshold(mat.clone(), threshold);
        fileName = QFileDialog::getSaveFileName(nullptr, QString("Save File"),
                                                        "/Users/hzzone/Desktop/image/untitled.png",
                                                        QString("Images (*.png *.xpm *.jpg)"));
        imwrite(fileName.toStdString().c_str(), mat1);

    }
}

void dithering_slot()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString("Open Image"), "/Users/hzzone/Desktop/image", QString("Image Files (*.png *.jpg *.bmp)"));
    QByteArray ba = fileName.toLatin1();
    char* file_name = ba.data();
    cout<<file_name<<endl;

    Mat mat = imread(file_name, 0);

    Mat D = Mat(2, 2, CV_8U, cv::Scalar::all(0));
    D.at<uchar>(0, 0) = 0;
    D.at<uchar>(0, 1) = 2;
    D.at<uchar>(1, 0) = 3;
    D.at<uchar>(0, 1) = 1;

    Mat mat2 = dithering(mat.clone(), D);
    fileName = QFileDialog::getSaveFileName(nullptr, QString("Save File"),
                                            "/Users/hzzone/Desktop/image/untitled.png",
                                            QString("Images (*.png *.xpm *.jpg)"));
    imwrite(fileName.toStdString().c_str(), mat2);

}

void ordered_dithering_slot()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString("Open Image"), "/Users/hzzone/Desktop/image", QString("Image Files (*.png *.jpg *.bmp)"));
    QByteArray ba = fileName.toLatin1();
    char* file_name = ba.data();
    cout<<file_name<<endl;
    Mat mat = imread(file_name, 0);

    Mat D = Mat(2, 2, CV_8U, cv::Scalar::all(0));
    D.at<uchar>(0, 0) = 0;
    D.at<uchar>(0, 1) = 2;
    D.at<uchar>(1, 0) = 3;
    D.at<uchar>(0, 1) = 1;

    Mat mat2 = ordered_dithering(mat.clone(), D);
    fileName = QFileDialog::getSaveFileName(nullptr, QString("Save File"),
                                            "/Users/hzzone/Desktop/image/untitled.png",
                                            QString("Images (*.png *.xpm *.jpg)"));
    imwrite(fileName.toStdString().c_str(), mat2);
}


void proportion_slot()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString("Open Image"), "/Users/hzzone/Desktop/image", QString("Image Files (*.png *.jpg *.bmp)"));
    QByteArray ba = fileName.toLatin1();
    char* file_name = ba.data();
    cout<<file_name<<endl;

    unsigned char *pBmpBuf;//读入图像的数据指针
    int bmpWidth;//图像的宽
    int bmpHeight;//图像的高
    RGBQUAD *pColorTable;//颜色表指针
    int biBitCount;//图像类型，每像素的位数

    //读入指定的bmp文件进内存
    readBmp(file_name, pBmpBuf, bmpWidth, bmpHeight, pColorTable, biBitCount);
    printf("width=%d,height=%d,biBitCount=%d",bmpWidth,bmpHeight,biBitCount);
    //将图像数据存盘
    proportion(pBmpBuf,bmpWidth,bmpHeight);
    //清除缓冲区
//    delete []pBmpBuf;
//    if(biBitCount==8)
//        delete []pColorTable;
    fileName = QFileDialog::getSaveFileName(nullptr, QString("Save File"),
                                            "/Users/hzzone/Desktop/image/untitled.png",
                                            QString("Images (*.png *.xpm *.jpg)"));
    ba = fileName.toLatin1();
    file_name = ba.data();
    saveBmp(file_name,pBmpBuf,bmpWidth,bmpHeight,biBitCount,pColorTable);
}

void gray_slot()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString("Open Image"), "/Users/hzzone/Desktop/image", QString("Image Files (*.png *.jpg *.bmp)"));
    QByteArray ba = fileName.toLatin1();
    char* file_name = ba.data();
    cout<<file_name<<endl;
    Mat mat = imread(file_name);


    Mat mat2 = gray(mat.clone());
    fileName = QFileDialog::getSaveFileName(nullptr, QString("Save File"),
                                            "/Users/hzzone/Desktop/image/untitled.png",
                                            QString("Images (*.png *.xpm *.jpg)"));
    imwrite(fileName.toStdString().c_str(), mat2);
}

void open_slot()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    QString("Open Image"), "/Users/hzzone/Desktop/image", QString("Image Files (*.png *.jpg *.bmp)"));
    QByteArray ba = fileName.toLatin1();
    char* file_name = ba.data();
    cout<<file_name<<endl;
    unsigned char *pBmpBuf;//读入图像的数据指针
    int bmpWidth;//图像的宽
    int bmpHeight;//图像的高
    RGBQUAD *pColorTable;//颜色表指针
    int biBitCount;//图像类型，每像素的位数

    //读入指定的bmp文件进内存
    readBmp(file_name, pBmpBuf, bmpWidth, bmpHeight, pColorTable, biBitCount);
    printf("width=%d,height=%d,biBitCount=%d",bmpWidth,bmpHeight,biBitCount);
    //将图像数据存盘
    //清除缓冲区
    fileName = QFileDialog::getSaveFileName(nullptr, QString("Save File"),
                                            "/Users/hzzone/Desktop/image/untitled.png",
                                            QString("Images (*.png *.xpm *.jpg)"));
    ba = fileName.toLatin1();
    file_name = ba.data();
    saveBmp(file_name,pBmpBuf,bmpWidth,bmpHeight,biBitCount,pColorTable);
}