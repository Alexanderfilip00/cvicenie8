#include "cvicenie8.h"



cvicenie8::cvicenie8(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    srand(time(NULL));
    QFile FileOtazky("questions.txt");
    if (!FileOtazky.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Chyba suboru s otazkami";
        FileOtazky.close();
        exit(1);
    }

    bool ok;
    int i,j;
    
    QTextStream instream(&FileOtazky);      //temporary premenna na citanie riadkov
    QString riadok = instream.readLine();
    int QuestionsAmmount = riadok.toInt(&ok);
    if (!ok) {
        qDebug() << "Chyba konverzie.";
        exit(1);
    }
    otazky = new Question[QuestionsAmmount];
    a.reserve(QuestionsAmmount);

    for (i = 0; i < QuestionsAmmount; i++) {
        a.push_back(i);

        otazky[i].setQuestion(instream.readLine());
        riadok = instream.readLine();
        otazky[i].setCorrectA(riadok.toInt(&ok));

        if (!ok) {
            qDebug() << "Chyba konverzie.";
            exit(1);
        }

        for (j = 0; j < 4; j++) {
            otazky[i].setAnswer(j, instream.readLine());
        }

    }
   
    ui.pushButton_Potvrdit->setEnabled(false);
    ui.pushButton_Preskocit->setEnabled(false);
    ui.Button_Answ1->setEnabled(false);
    ui.Button_Answ2->setEnabled(false);
    ui.Button_Answ3->setEnabled(false);
    ui.Button_Answ4->setEnabled(false);
}

void cvicenie8::on_NovaHra_clicked() {

    ui.ScoreBox->setValue(hrac.getBody());
    ui.pushButton_Preskocit->setEnabled(true);
    ui.Button_Answ1->setEnabled(true);
    ui.Button_Answ2->setEnabled(true);
    ui.Button_Answ3->setEnabled(true);
    ui.Button_Answ4->setEnabled(true);
    ui.Meno->setReadOnly(true);

    ui.Zolik1->setMaximumWidth(16777215);
    ui.Zolik2->setMaximumWidth(16777215);
    ui.Zolik3->setMaximumWidth(16777215);

    hrac.setMeno(ui.Meno->text());
    ui.Meno->setEnabled(false);
    ui.DiffBox->setEnabled(false);
    ui.checkBox_Random->setEnabled(false);
    ui.KoniecHry->setEnabled(true);
    ui.NovaHra->setEnabled(false);
    
    if (ui.DiffBox->currentIndex() == 0) {
        ui.Zolik1->setEnabled(true);
        ui.Zolik2->setEnabled(true);
        ui.Zolik3->setEnabled(true);
        //qDebug() << "uroven lahka";
    }

    else if (ui.DiffBox->currentIndex() == 1) {
        //qDebug() << "uroven stredna";
        ui.Zolik1->setEnabled(true);
        ui.Zolik2->setEnabled(true);
        ui.Zolik3->setMaximumWidth(0);
    }

    else if (ui.DiffBox->currentIndex() == 2) {
        //qDebug() << "uroven tazka";
        ui.Zolik1->setEnabled(true);
        ui.Zolik2->setMaximumWidth(0);
        ui.Zolik3->setMaximumWidth(0);
    }
   
    if (ui.checkBox_Random->isChecked() == true) {
        std::random_shuffle(std::begin(a), std::end(a));
    }
   
    ui.Otazka->setText(otazky[a[hrac.getPoradie()]].getQuestion());
    ui.Button_Answ1->setText(otazky[a[hrac.getPoradie()]].getAnswer(0));
    ui.Button_Answ2->setText(otazky[a[hrac.getPoradie()]].getAnswer(1));
    ui.Button_Answ3->setText(otazky[a[hrac.getPoradie()]].getAnswer(2));
    ui.Button_Answ4->setText(otazky[a[hrac.getPoradie()]].getAnswer(3));
}

void cvicenie8::on_KoniecHry_clicked()
{
    hrac.addBody((10 - (hrac.getPoradie())) * (-0.5));
    ui.ScoreBox->setValue(hrac.getBody());

    ui.Meno->setReadOnly(false);
    ui.Meno->setEnabled(true);
    ui.DiffBox->setEnabled(true);
    ui.checkBox_Random->setEnabled(true);
    ui.pushButton_Potvrdit->setEnabled(false);
    ui.pushButton_Preskocit->setEnabled(false);
    ui.Button_Answ1->setEnabled(false);
    ui.Button_Answ1->setText("");
    ui.Button_Answ2->setEnabled(false);
    ui.Button_Answ2->setText("");
    ui.Button_Answ3->setEnabled(false);
    ui.Button_Answ3->setText("");
    ui.Button_Answ4->setEnabled(false);
    ui.Button_Answ4->setText("");

    ui.Zolik1->setMaximumWidth(0);
    ui.Zolik2->setMaximumWidth(0);
    ui.Zolik3->setMaximumWidth(0);

    ui.Button_Answ1->setAutoExclusive(false);
    ui.Button_Answ1->setChecked(false);
    ui.Button_Answ1->setAutoExclusive(true);

    ui.Button_Answ2->setAutoExclusive(false);
    ui.Button_Answ2->setChecked(false);
    ui.Button_Answ2->setAutoExclusive(true);

    ui.Button_Answ3->setAutoExclusive(false);
    ui.Button_Answ3->setChecked(false);
    ui.Button_Answ3->setAutoExclusive(true);

    ui.Button_Answ4->setAutoExclusive(false);
    ui.Button_Answ4->setChecked(false);
    ui.Button_Answ4->setAutoExclusive(true);

    ui.NovaHra->setEnabled(true);
    ui.KoniecHry->setEnabled(false);


    ui.Otazka->setText("Hra ukoncena. Skontrolujte si pocet bodov. Pre zacatie novej hry kliknite na 'Nova hra'");
    int i;
    for (i = 0; i < 3; i++) {
        hrac.setZolik(i,true);
    }
    for (i = 0; i < 9; i++) {
        a[i] = i;
    }
    hrac.setPoradie(0);
    randvalue = 0;
    hrac.setBody(0);

    for (i = 0; i < 3; i++) {
        hrac.setZolik(i, true);
    }
}

void cvicenie8::on_Meno_editingFinished()
{
    hrac.setMeno(ui.Meno->text());
    ui.NovaHra->setEnabled(true);
}

void cvicenie8::on_Zolik1_clicked() {
    hrac.setZolik(0, false);
    ui.Zolik1->setEnabled(false);
    ui.Zolik2->setEnabled(false);
    ui.Zolik3->setEnabled(false);


    do { randvalue = rand() % 4 + 1; 
    } while (randvalue == otazky[a[hrac.getPoradie()]].getCorrectA());
  

    int i;
    for (i = 1; i <= 4; i++) {
        if (i != randvalue && i != otazky[a[hrac.getPoradie()]].getCorrectA()) {
            switch (i) {
                case 1:
                    ui.Button_Answ1->setEnabled(false);
                    break;
                case 2:
                    ui.Button_Answ2->setEnabled(false);
                    break;
                case 3:
                    ui.Button_Answ3->setEnabled(false);
                    break;
                default:
                    ui.Button_Answ4->setEnabled(false);
                    break;
            }
        }
    }


}

void cvicenie8::on_Zolik2_clicked() {
    hrac.setZolik(1, false);
    ui.Zolik1->setEnabled(false);
    ui.Zolik2->setEnabled(false);
    ui.Zolik3->setEnabled(false);

    do {
        randvalue = rand() % 4 + 1;
    } while (randvalue == otazky[a[hrac.getPoradie()]].getCorrectA());

    int i;
    for (i = 1; i <= 4; i++) {
        if (i != randvalue && i != otazky[a[hrac.getPoradie()]].getCorrectA()) {
            switch (i) {
            case 1:
                ui.Button_Answ1->setEnabled(false);
                break;
            case 2:
                ui.Button_Answ2->setEnabled(false);
                break;
            case 3:
                ui.Button_Answ3->setEnabled(false);
                break;
            default:
                ui.Button_Answ4->setEnabled(false);
                break;
            }
        }
    }

}

void cvicenie8::on_Zolik3_clicked() {
    hrac.setZolik(2, false);
    ui.Zolik1->setEnabled(false);
    ui.Zolik2->setEnabled(false);
    ui.Zolik3->setEnabled(false);


    do {
        randvalue = rand() % 4 + 1;
    } while (randvalue == otazky[a[hrac.getPoradie()]].getCorrectA());

    int i;
    for (i = 1; i <= 4; i++) {
        if (i != randvalue && i != otazky[a[hrac.getPoradie()]].getCorrectA()) {
            switch (i) {
            case 1:
                ui.Button_Answ1->setEnabled(false);
                break;
            case 2:
                ui.Button_Answ2->setEnabled(false);
                break;
            case 3:
                ui.Button_Answ3->setEnabled(false);
                break;
            default:
                ui.Button_Answ4->setEnabled(false);
                break;
            }
        }
    }

}

void cvicenie8::on_pushButton_Potvrdit_clicked()
{

    if (ui.Button_Answ1->isChecked() && otazky[a[hrac.getPoradie()]].getCorrectA() == 1) {
        //qDebug() << "spravne bolo oznacene cislo 1";
        hrac.addBody(1.0);
    }
    else if (ui.Button_Answ2->isChecked() && otazky[a[hrac.getPoradie()]].getCorrectA() == 2) {
        //qDebug() << "spravne bolo oznacene cislo 2";
        hrac.addBody(1.0);
    }
    else if (ui.Button_Answ3->isChecked() && otazky[a[hrac.getPoradie()]].getCorrectA() == 3) {
        //qDebug() << "spravne bolo oznacene cislo 3";
        hrac.addBody(1.0);
    }
    else if (ui.Button_Answ4->isChecked() && otazky[a[hrac.getPoradie()]].getCorrectA() == 4) {
        //qDebug() << "spravne bolo oznacene cislo 4";
        hrac.addBody(1.0);
    }
    else {
        //qDebug() << "nebola oznacena spravna moznost.";
        hrac.addBody(-1.0);
    }

    ui.ScoreBox->setValue(hrac.getBody());

    ui.pushButton_Potvrdit->setEnabled(false);
    ui.Button_Answ1->setEnabled(true);
    ui.Button_Answ2->setEnabled(true);
    ui.Button_Answ3->setEnabled(true);
    ui.Button_Answ4->setEnabled(true);

    ui.Button_Answ1->setAutoExclusive(false);
    ui.Button_Answ1->setChecked(false);
    ui.Button_Answ1->setAutoExclusive(true);

    ui.Button_Answ2->setAutoExclusive(false);
    ui.Button_Answ2->setChecked(false);
    ui.Button_Answ2->setAutoExclusive(true);

    ui.Button_Answ3->setAutoExclusive(false);
    ui.Button_Answ3->setChecked(false);
    ui.Button_Answ3->setAutoExclusive(true);

    ui.Button_Answ4->setAutoExclusive(false);
    ui.Button_Answ4->setChecked(false);
    ui.Button_Answ4->setAutoExclusive(true);


    if (hrac.getZolik(0) == true) ui.Zolik1->setEnabled(true);
    if (hrac.getZolik(1) == true) ui.Zolik2->setEnabled(true);
    if (hrac.getZolik(2) == true) ui.Zolik3->setEnabled(true);

    hrac.addPoradie();
    if (hrac.getPoradie() == 10) {
        ui.Button_Answ1->setEnabled(false);
        ui.Button_Answ1->setText("");
        ui.Button_Answ2->setEnabled(false);
        ui.Button_Answ2->setText("");
        ui.Button_Answ3->setEnabled(false);
        ui.Button_Answ3->setText("");
        ui.Button_Answ4->setEnabled(false);
        ui.Button_Answ4->setText("");

        ui.pushButton_Potvrdit->setEnabled(false);
        ui.pushButton_Preskocit->setEnabled(false);
        ui.Zolik1->setEnabled(false);
        ui.Zolik2->setEnabled(false);
        ui.Zolik3->setEnabled(false);
        ui.Otazka->setText("Koniec hry, kliknite na 'Ukoncit hru'");
    }
    else {

        ui.Otazka->setText(otazky[a[hrac.getPoradie()]].getQuestion());
        ui.Button_Answ1->setText(otazky[a[hrac.getPoradie()]].getAnswer(0));
        ui.Button_Answ2->setText(otazky[a[hrac.getPoradie()]].getAnswer(1));
        ui.Button_Answ3->setText(otazky[a[hrac.getPoradie()]].getAnswer(2));
        ui.Button_Answ4->setText(otazky[a[hrac.getPoradie()]].getAnswer(3));

    }
    
}

void cvicenie8::on_pushButton_Preskocit_clicked()
{
    ui.pushButton_Potvrdit->setEnabled(false);
    ui.Button_Answ1->setEnabled(true);
    ui.Button_Answ2->setEnabled(true);
    ui.Button_Answ3->setEnabled(true);
    ui.Button_Answ4->setEnabled(true);

    ui.Button_Answ1->setAutoExclusive(false);
    ui.Button_Answ1->setChecked(false);
    ui.Button_Answ1->setAutoExclusive(true);

    ui.Button_Answ2->setAutoExclusive(false);
    ui.Button_Answ2->setChecked(false);
    ui.Button_Answ2->setAutoExclusive(true);

    ui.Button_Answ3->setAutoExclusive(false);
    ui.Button_Answ3->setChecked(false);
    ui.Button_Answ3->setAutoExclusive(true);

    ui.Button_Answ4->setAutoExclusive(false);
    ui.Button_Answ4->setChecked(false);
    ui.Button_Answ4->setAutoExclusive(true);

    if (hrac.getZolik(0) == true) ui.Zolik1->setEnabled(true);
    if (hrac.getZolik(1) == true) ui.Zolik2->setEnabled(true);
    if (hrac.getZolik(2) == true) ui.Zolik3->setEnabled(true);

    hrac.addBody(-0.5);

    ui.ScoreBox->setValue(hrac.getBody());

    hrac.addPoradie();
    if (hrac.getPoradie() == 10) {
        ui.Button_Answ1->setEnabled(false);
        ui.Button_Answ1->setText("");
        ui.Button_Answ2->setEnabled(false);
        ui.Button_Answ2->setText("");
        ui.Button_Answ3->setEnabled(false);
        ui.Button_Answ3->setText("");
        ui.Button_Answ4->setEnabled(false);
        ui.Button_Answ4->setText("");

        ui.pushButton_Potvrdit->setEnabled(false);
        ui.pushButton_Preskocit->setEnabled(false);
        ui.Zolik1->setEnabled(false);
        ui.Zolik2->setEnabled(false);
        ui.Zolik3->setEnabled(false);
        ui.Otazka->setText("Koniec hry, kliknite na 'Ukoncit hru'");
    }
    else {
        ui.Otazka->setText(otazky[a[hrac.getPoradie()]].getQuestion());
        ui.Button_Answ1->setText(otazky[a[hrac.getPoradie()]].getAnswer(0));
        ui.Button_Answ2->setText(otazky[a[hrac.getPoradie()]].getAnswer(1));
        ui.Button_Answ3->setText(otazky[a[hrac.getPoradie()]].getAnswer(2));
        ui.Button_Answ4->setText(otazky[a[hrac.getPoradie()]].getAnswer(3));

    }

}

void cvicenie8::on_Button_Answ1_clicked()
{
    ui.pushButton_Potvrdit->setEnabled(true);
}

void cvicenie8::on_Button_Answ2_clicked()
{
    ui.pushButton_Potvrdit->setEnabled(true);
}

void cvicenie8::on_Button_Answ3_clicked()
{
    ui.pushButton_Potvrdit->setEnabled(true);
}

void cvicenie8::on_Button_Answ4_clicked()
{
    ui.pushButton_Potvrdit->setEnabled(true);
}
