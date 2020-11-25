#pragma once

//#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include "ui_cvicenie8.h"
#include <stdlib.h>

class Question {
private:
    QString Question;
    QString Answer[4];
    int CorrectA=NULL;
public:
    void setQuestion(QString s) { Question = s; };
    void setAnswer(int i, QString s) { Answer[i] = s; };
    void setCorrectA(int n) { CorrectA = n; };

    QString getQuestion() { return Question; };
    QString getAnswer(int i) { return Answer[i]; };
    int getCorrectA() { return CorrectA; };
};

class Player {
private:
    QString meno = NULL;
    float body = 0.0;
    bool zoliky[3] = { true,true,true };
    int poradie = 0;
public:
    void setMeno(QString s) { meno = s; };
    void setBody(int v) { body = v; };
    void addBody(float a) { body = body + a; };
    float getBody() { return body; };

    void setZolik(int i, bool v) { zoliky[i] = v; };
    bool getZolik(int i) {
        if (zoliky[i] == true) return true;
        else return false;
    }
    int getPoradie() { return poradie; };
    void setPoradie(int v) { poradie = v; };
    void addPoradie() { poradie++; };
};

class cvicenie8 : public QMainWindow
{
    Q_OBJECT

public:
    cvicenie8(QWidget *parent = Q_NULLPTR);
    ~cvicenie8() { delete[] otazky; };

private:
    Ui::cvicenie8Class ui;
    std::vector<int> a;
    Player hrac;
    Question *otazky;
    //int poradie = 0;
    //bool zoliky[3] = { true,true,true };
    //QString* QuestionsSet;
    //QString* AnswersSet;
    //int* CorrectASet;
    int randvalue=0;
    //float body=0.0;

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
