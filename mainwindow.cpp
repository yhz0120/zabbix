#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QMessageBox>
#include <QByteArray>
#include <QCloseEvent>
#include <QDialog>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDefaultText();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//The code from david!!!

void MainWindow::closeEvent(QCloseEvent *event) //系统自带退出确定程序
{
    int choose;
    choose= QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("确认退出程序?")),
                                   QMessageBox::Yes | QMessageBox::No);

    if (choose== QMessageBox::No)
     {
          event->ignore();  //忽略//程序继续运行
    }
    else if (choose== QMessageBox::Yes)
    {
          event->accept();  //介绍//程序退出
    }
}



//点击确认后保存用户输入
void MainWindow::on_save_clicked()
{

    QString input1=ui->textEdit->toPlainText();
    QString input2=ui->textEdit_2->toPlainText();
    QString input3=ui->textEdit_3->toPlainText();
    QString input4=ui->textEdit_4->toPlainText();


    if(!QString::compare(input1,"")||!QString::compare(input2,"")||
            !QString::compare(input3,"")||!QString::compare(input4,"")){
        QMessageBox::about(NULL, "友情提示", "有输入框为空，不可提交!");
        return;
    }
    char path[128]="/home/yhz/2.txt";
    strcpy(path,getenv("HOME"));
    strcat(path,"/.data");
    FILE* fp=fopen(path,"wb");
    if(fp==NULL){
        QMessageBox::about(NULL, "友情提示", "文件打开失败!");
        perror("fopen file");
        return;
    }
    int size1=input1.toLocal8Bit().length();
    int size2=input2.toLocal8Bit().length();
    int size3=input3.toLocal8Bit().length();
    int size4=input4.toLocal8Bit().length();

   /* int size1=input1.toLatin1().length();
    int size2=input2.toLatin1().length();
    int size3=input3.toLatin1().length();
    int size4=input4.toLatin1().length();
    */
    char write1[size1+2];
    char write2[size2+2];
    char write3[size3+2];
    char write4[size4+2];

    /*char write1[512];
    char write2[512];
    char write3[512];
    char write4[512];
    */
    strcpy(write1,input1.toLocal8Bit().data());//QString-->char*
    strcpy(write2,input2.toLocal8Bit().data());
    strcpy(write3,input3.toLocal8Bit().data());
    strcpy(write4,input4.toLocal8Bit().data());


    /*
    char write1[512];
    char write2[512];
    char write3[512];
    char write4[512];

    strcpy(write1,"三雕刻家菲卡的风俗佛岁的科技反对封建酷似大佛雕塑风格斯蒂芬教凯瑟琳复活节酷似大佛");
    strcpy(write2,"的风格广泛的给哦日图尔特哦厄瑞特他而哦itertoeirtuyhtrklhrh年旅客提供今天看来国家二级台儿");
    strcpy(write3,"热烈卡塔尔泰戈尔可提供尔根人们考古和二里头个如而土壤条件而聆听顾客urterltkerutertg");
    strcpy(write4,"论坛uerglrkeguergbnedvilgy例如对方杰克森的巨幅而铁路儿童而蒙特卡洛和儿童国画矿务局俄语范围日特太阳如果有人他");

    */

    char sedbuf[size1+size2+size3+size4+10];

    //char sedbuf[4096];
    memset(sedbuf,0,strlen(sedbuf));
    sprintf(sedbuf,"%s#%s#%s#%s",write1,write2,write3,write4);

    fwrite(sedbuf,4096,1,fp);

    char pp[128]="";
    //sprintf(pp,"   %d %d %d %d %d",input1.size(),input2.size(),input3.size(),input4.size(),sed_size);
    /*fwrite(write1,strlen(write1),1,fp);
    fwrite(write2,strlen(write2),1,fp);
    fwrite(write3,strlen(write3),1,fp);
    fwrite(write4,strlen(write4),1,fp);
    */
    //fputs(pp,fp);
    fclose(fp);
     QMessageBox::about(NULL, "友情提示", "点击完成!");
}


//设置默认窗口标题
void MainWindow::setDefaultText(){
    char path[128]="/home/yhz/2.txt";
    strcpy(path,getenv("HOME"));
    strcat(path,"/.data");
    FILE* fp=fopen(path,"rb");
    if(fp==NULL){
        perror("fopen file");
        return;
    }

    struct stat info;
    stat(path,&info);
    char* tmp=(char*)malloc(info.st_size+1);
    memset(tmp,0,info.st_size+1);

    fread(tmp,info.st_size,1,fp);

    FILE* fp2=fopen("/home/yhz/tt","wt");
    fputs(tmp,fp2);
    char pp[12]="";
    sprintf(pp,"  %d",info.st_size);
    fputs(pp,fp2);
    fclose(fp2);

    QString defau=(QString)((QByteArray)tmp);
    QStringList qsl=defau.split('#');
    if(qsl.size()<4){
        QMessageBox::information(NULL,"友情提示","文件中数据格式不满足要求，将无法为您显示上一次的输入信息!!!");
        return;
    }

    ui->textEdit->setPlainText(qsl.at(0));
    ui->textEdit_2->setPlainText(qsl.at(1));
    ui->textEdit_3->setPlainText(qsl.at(2));
    ui->textEdit_4->setPlainText(qsl.at(3));

    fclose(fp);
    free(tmp);
}

//点击按钮后清空所有输入框
void MainWindow::on_clean_clicked()
{
    ui->textEdit->setPlainText("");
    ui->textEdit_2->setPlainText("");
    ui->textEdit_3->setPlainText("");
    ui->textEdit_4->setPlainText("");
}
