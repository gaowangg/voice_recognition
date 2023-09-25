#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton->setText("按住说话");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_pressed()
{
    ui->pushButton->setText("松开识别");

    //开始录音
    myaudio = new Audio;
    myaudio->startAudio("C:\\Users\\Administrator\\Desktop\\demo.pcm");

}

void Widget::on_pushButton_released()
{
    //停止录音
    myaudio->stopAudio();

    ui->pushButton->setText("开始识别");
    //开始识别
    myspeech = new Speech;
    QString retText = myspeech->speechReconition("C:\\Users\\Administrator\\Desktop\\demo.pcm");
    ui->textEdit->setText(retText);
    ui->pushButton->setText("按住说话");
}

void Widget::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
}
