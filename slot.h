//
// Created by 黄智忠 on 19/6/2018.
//

#ifndef SIMPLE_SLOT_H
#define SIMPLE_SLOT_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QFileDialog>
#include <QMainWindow>

#include "mode_trans.h"
using namespace std;
using namespace cv;

void single_threshold_slot();
void ordered_dithering_slot();
void dithering_slot();
void proportion_slot();
void gray_slot();
void open_slot();

#endif //SIMPLE_SLOT_H
