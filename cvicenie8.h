#pragma once

//#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "ui_cvicenie8.h"
#include <stdlib.h>

class cvicenie8 : public QMainWindow
{
    Q_OBJECT

public:
    cvicenie8(QWidget *parent = Q_NULLPTR);

private:
    Ui::cvicenie8Class ui;
    std::vector<int> a;
    int poradie = 0;
    bool zoliky[3] = { true,true,true };
    QString* QuestionsSet;
    QString* AnswersSet;
    int* CorrectASet;
    int randvalue=0;
    float body=0.0;

private slots:
    void on_NovaHra_clicked();
    void on_KoniecHry_clicked();
    void on_Meno_editingFinished();
    void on_Zolik1_clicked();
    void on_Zolik2_clicked();
    void on_Zolik3_clicked();
    void on_pushButton_Potvrdit_clicked();
    void on_pushButton_Preskocit_clicked();
    void on_Button_Answ1_clicked();
    void on_Button_Answ2_clicked();
    void on_Button_Answ3_clicked();
    void on_Button_Answ4_clicked();
};
