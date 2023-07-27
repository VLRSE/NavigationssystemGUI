#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qlineedit.h"
#include <iostream>
#include <QString>
#include "ort.h"
#include "poi.h"
#include "adresse.h"
#include <QPlainTextEdit>
#include <QFormLayout>
#include <QRegularExpressionValidator>
#include <squareqpushbutton.h>
#include <QtWidgets/QFileDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <fstream>
#include <QMessageBox>


QPushButton* BTN_Adresse = nullptr;
QPushButton* BTN_POI = nullptr;
QWidget* widgetOrtAnlegen = nullptr;
QWidget* widgetKarteAnzeigen = nullptr;
QWidget* widgetEntfernungBerechnen = nullptr;
QWidget* widgetBinaerImpExp = nullptr;
QWidget* widgetErgebnisEntfernungBerechnen = nullptr;
QWidget* widgetCSVImpExp = nullptr;
QWidget* widgetNeuAdresse = nullptr;
QWidget* widgetNeuPoi = nullptr;
QPushButton* BTN_ImportBinaer = nullptr;
QPushButton* BTN_ExportBinaer = nullptr;
QPushButton* BTN_adresseSpeichern = nullptr;
QPushButton* BTN_neuPoiSpeichern = nullptr;
QPushButton* BTN_ImportCSV = nullptr;
QPushButton* BTN_CSVImpExp = nullptr;
QPushButton* BTN_ExportCSV = nullptr;
QLabel* StartZielLabel = nullptr;
QLineEdit* lineEditStart = nullptr;
QLineEdit* lineEditZiel = nullptr;
QLineEdit* nameAdresse  = nullptr;
QLineEdit* strasse = nullptr;
QLineEdit* hausNummer = nullptr;
QLineEdit* plz =  nullptr;
QLineEdit* stadt =  nullptr;
QLineEdit* namePoi  = nullptr;
QLineEdit* kategorie  = nullptr;
QLineEdit* bemerkung = nullptr;
QLineEdit* breitengradAdresse = nullptr;
QLineEdit* laengengradAdresse = nullptr;
QLineEdit* breitengradPoi = nullptr;
QLineEdit* laengengradPoi = nullptr;
QPushButton* BTN_SaveStart = nullptr;
QPushButton* BTN_SaveZiel = nullptr;
QPlainTextEdit* plaintText = nullptr;
QLabel* errorLabelAdresse = nullptr;
QLabel* errorLabelPoi = nullptr;
QLabel* nameAdresseLabel = nullptr;
QLabel* StartZielErrorLabel = nullptr;
QLabel* exportingStatusMessageLabel= nullptr;
QTableWidget* tableWidget = nullptr;
QRegularExpression  rx("[A-z]+");
QRegularExpressionValidator*     stringValidator = new QRegularExpressionValidator(rx,0);
QRegularExpression  rxNum("[A-z]+");
QRegularExpressionValidator* stringNumValidator = new QRegularExpressionValidator(rxNum,0);
QDoubleValidator* doubleValidator = new QDoubleValidator(1.00,9999.00,2);
QIntValidator* intValidator = new QIntValidator();
int startID, ZielID;
int currentIndex = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

    //button connections
    QObject::connect(ui->BTN_OrtAnlegen, &QPushButton::clicked, this, &MainWindow::addOrtAnlegenView);
    QObject::connect(BTN_Adresse, &QPushButton::clicked, this, &MainWindow::on_click_BTN_Adresse);
    QObject::connect(BTN_adresseSpeichern, &QPushButton::clicked, this, &MainWindow::on_click_BTN_adresseSpeichern);
    QObject::connect(BTN_POI, &QPushButton::clicked, this, &MainWindow::on_click_BTN_Poi);
    QObject::connect(BTN_neuPoiSpeichern, &QPushButton::clicked, this, &MainWindow::on_click_BTN_poiSpeichern);
    QObject::connect(ui->BTN_KarteAnzeigen, &QPushButton::clicked, this, &MainWindow::karteAnzeigen);
    QObject::connect(ui->BTN_EntfernungBerechnen, &QPushButton::clicked, this, &MainWindow::entfernungBerechnen);
    QObject::connect(BTN_SaveStart, &QPushButton::clicked, this, &MainWindow::on_click_BTN_SaveStart);
    QObject::connect(BTN_SaveZiel, &QPushButton::clicked, this, &MainWindow::on_click_BTN_ZielSpeichern);
    QObject::connect(ui->BTN_BinaerImpExp, &QPushButton::clicked, this, &MainWindow::on_click_BTN_BinaerImpExp);
    QObject::connect(BTN_ImportBinaer, &QPushButton::clicked, this, &MainWindow::on_click_BTN_ImportBinaer);
    QObject::connect(BTN_ExportBinaer, &QPushButton::clicked, this, &MainWindow::on_click_BTN_ExportBinaer);
    QObject::connect(ui->BTN_CSVImpExp, &QPushButton::clicked, this, &MainWindow::on_click_BTN_CSVImpExp);
    QObject::connect(BTN_ImportCSV, &QPushButton::clicked, this, &MainWindow::on_click_BTN_ImportCSV);
    QObject::connect(BTN_ExportCSV, &QPushButton::clicked, this, &MainWindow::on_click_BTN_ExportCSV);
    QObject::connect(ui->BTN_Exit, &QPushButton::clicked, this, &MainWindow::on_click_BTN_Exit);

}

void MainWindow::init(){
    Orte.push_back(new Adresse(53.072823, 8.80958, "Schnoor", " 11", 218195, "Bremen D", "Maike Meier"));
    Orte.push_back(new PoI(49.86682, 8.639912, "Hochschule", " Bildungseinrichtung", "h-da"));
    Orte.push_back(new Adresse(51.0315428, 13.7317817, "Hochschulstraße", "7", 0106 , "Dresden D", "Paul Baumann"));
    Orte.push_back(new PoI(49.4833652, 8.4960972, "Luisenpark Mannheim", " Bundesgartenschau", "BUGA 23"));
    Orte.push_back(new PoI(51.7544943, 14.3443348, "Raumflugplanetarium", " Juri Gagrin", "Planetarium"));

    //Instantiate QWidget Objects
    qWidgetErstellen();
    qButtonsErstellen();
    addOrtMenu();
    //create Form view for Neu Adresse
    createNeuAdresseForm();
    //create Form view for Neu PoI
    createNeuPoiForm();
    createWidgetVieKarteAnzeigen();
    createWindowBinaerImpExp();
    createWindowCSVImpExp();
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetOrtAnlegen);
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetNeuAdresse);
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetKarteAnzeigen);
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetEntfernungBerechnen);
    ui->horizontalLayout_mainView_OrtAnlegen->addWidget(widgetErgebnisEntfernungBerechnen);
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetBinaerImpExp);
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetCSVImpExp);


}
void MainWindow::qWidgetErstellen(){
    widgetOrtAnlegen = new QWidget();
    widgetNeuAdresse = new QWidget();
    widgetNeuPoi = new QWidget();
    widgetEntfernungBerechnen = new QWidget();
    widgetKarteAnzeigen = new QWidget();
    widgetBinaerImpExp = new QWidget();
    widgetErgebnisEntfernungBerechnen = new QWidget();
    widgetCSVImpExp = new QWidget();
}

void MainWindow::qButtonsErstellen(){
    ui->BTN_OrtAnlegen->setFixedSize(150,150);
    ui->BTN_KarteAnzeigen->setFixedSize(150,150);
    ui->BTN_BinaerImpExp->setFixedSize(150,150);
    ui->BTN_EntfernungBerechnen->setFixedSize(150,150);
    ui->BTN_OrtAnlegen->setFixedSize(150,150);
    ui->BTN_CSVImpExp->setFixedSize(150,150);


}
void MainWindow::addOrtMenu(){

    QHBoxLayout* layout = new QHBoxLayout();
    widgetOrtAnlegen->setLayout(layout);
    widgetOrtAnlegen->setVisible(true);
    BTN_Adresse = new SquareQPushButton("Neu Adresse");
    BTN_Adresse->setVisible(true);
    BTN_POI = new SquareQPushButton("Neu POI");
    BTN_POI->setVisible(true);

    layout->addWidget(BTN_Adresse);
    layout->addWidget(BTN_Adresse);
    layout->addWidget(BTN_POI);
    //add current Widget view

    // QString sizeString = QString("1%, 2%").arg(s.height(), s.width());
    //convert QString to STD String
    //std::string stringS = sizeString.toUtf8().constData();
    //   QString buttonText = QString("Button:#%1").arg(layout->count());//Button text with incremental number


}
void MainWindow::addOrtAnlegenView(){
    //capture button
    // QPushButton* BTN_Adresse = qobject_cast<QPushButton*>(sender());
    //delete BTN_Adresse;

    widgetKarteAnzeigen->setVisible(false);
    widgetEntfernungBerechnen->setVisible(false);
    widgetErgebnisEntfernungBerechnen->setVisible(false);
    widgetBinaerImpExp->setVisible(false);
    widgetCSVImpExp->setVisible(false);
    widgetNeuAdresse->setVisible(false);
    widgetNeuPoi->setVisible(false);
    widgetOrtAnlegen->setVisible(true);


}

void MainWindow::createNeuAdresseForm(){
    QFormLayout* layout = new QFormLayout();
    layout->setFormAlignment(Qt::AlignLeft);
    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    layout->setContentsMargins(50,20,50, 0 );
    layout->setSpacing(30);
    layout->setLabelAlignment(Qt::AlignLeft);
    widgetNeuAdresse->setLayout(layout);

    errorLabelAdresse = new QLabel("Invalid Input");
    errorLabelAdresse->setVisible(false);
    layout->insertRow(1,errorLabelAdresse);
    layout->setLabelAlignment(Qt::AlignBottom);

    //validator erstellen, um Inputs zu kontrollieren und begrenzen

    int pos = 0;

    nameAdresse = new QLineEdit();  //name->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    nameAdresse->setMinimumWidth(350);
    nameAdresse->setMinimumHeight(40);
    nameAdresse->setValidator(stringValidator);
    nameAdresse->setPlaceholderText("Name ohne besondere Zeichen");

    strasse =  new QLineEdit();
    strasse->setMinimumWidth(250);
    strasse->setMinimumHeight(30);
    strasse->setValidator(stringValidator);
    strasse->setPlaceholderText("Name ohne besondere Zeichen");


    stadt =  new QLineEdit();
    stadt->setMinimumWidth(250);
    stadt->setMinimumHeight(30);
    stadt->setValidator(stringValidator);
    stadt->setPlaceholderText("Strasse bitte ohne besondere Zeichen eingeben");
    stadt->setPlaceholderText("Mainz");

    //Regular expression für diese Input midifizieren
    rx.setPattern("[A-z0-9]+");
    hausNummer =  new QLineEdit();
    hausNummer->setMinimumWidth(250);
    hausNummer->setMinimumHeight(30);
    hausNummer->setValidator(new QRegularExpressionValidator(rx,0));
    hausNummer->setPlaceholderText("Name ohne besondere Zeichen");
    hausNummer->setPlaceholderText("11 oder 5A");
    // integers 1 to 99999
    rx.setPattern("[1-9]\\d{0,4}");
    //   validator.setRegularExpression(&rx);

    plz =  new QLineEdit();
    plz->setMinimumWidth(250);
    plz->setMinimumHeight(30);
    plz->setValidator(intValidator);
    plz->setPlaceholderText("12345");



    doubleValidator->setLocale(QLocale::German);
    QLocale::setDefault(QLocale::German);  // default-constructed German locale
    QLocale german;

    breitengradAdresse =  new QLineEdit();
    breitengradAdresse->setMinimumWidth(250);
    breitengradAdresse->setMinimumHeight(30);
    breitengradAdresse->setValidator(doubleValidator);
    breitengradAdresse->setPlaceholderText("49,77");

    laengengradAdresse =  new QLineEdit();
    laengengradAdresse->setMinimumWidth(250);
    laengengradAdresse->setMinimumHeight(30);
    laengengradAdresse->setValidator(doubleValidator);
    laengengradAdresse->setPlaceholderText("8,77");
    BTN_adresseSpeichern =  new QPushButton("Speichern");
    BTN_adresseSpeichern->setFixedSize(120,50);


    layout->addRow(tr("Name:"), nameAdresse);
    layout->addRow(tr("Strasse:"),strasse);
    layout->addRow(tr("Hausnummer:"),hausNummer);
    layout->addRow(tr("PLZ:"),plz);
    layout->addRow(tr("Stadt:"),stadt);
    layout->addRow(tr("Breitengrad:"),breitengradAdresse);
    layout->addRow(tr("Laengengrad:"),laengengradAdresse);
    layout->addRow(BTN_adresseSpeichern);
    //TODO:set alignment to right
    widgetNeuAdresse->setVisible(false);
}
void MainWindow::on_click_BTN_Adresse(){
    clearLineEditsAdresse();
    resetErrorActions(1, errorLabelAdresse);
    widgetOrtAnlegen->setVisible(false);
    widgetKarteAnzeigen->setVisible(false);
    widgetEntfernungBerechnen->setVisible(false);
    widgetErgebnisEntfernungBerechnen->setVisible(false);
    widgetBinaerImpExp->setVisible(false);
    widgetCSVImpExp->setVisible(false);
    widgetNeuPoi->setVisible(false);
    widgetNeuAdresse->setVisible(true);

}

void MainWindow::on_click_BTN_adresseSpeichern(){
    resetErrorActions(1, errorLabelAdresse);
    int pos = 0;
    std::string nameInputString,hausNummerInputString,strasseInputString, plzInputString, stadtInputString;
    int plzInputInt;
    double laengengradInput,breitengradInput;
    QDoubleValidator* doubleValidator = new QDoubleValidator(1,99999,2);
    doubleValidator->setLocale(QLocale::German);
    QLocale::setDefault(QLocale::German);  // default-constructed German locale
    QLocale german;
    breitengradAdresse->setValidator(doubleValidator);
    laengengradAdresse->setValidator(doubleValidator);
    errorLabelAdresse->setVisible(false);
    //if all input acceptable and not empty
    if(nameAdresse->hasAcceptableInput() && strasse->hasAcceptableInput() && stadt->hasAcceptableInput() && hausNummer->hasAcceptableInput()
            && plz->hasAcceptableInput() && breitengradAdresse->hasAcceptableInput() && (!breitengradAdresse->text().isEmpty())
            && laengengradAdresse->hasAcceptableInput() && (!laengengradAdresse->text().isEmpty())){

        QString nameInput = nameAdresse->text();
        nameInputString = nameInput.toStdString();
        QString strasseInput = strasse->text();
        strasseInputString = strasseInput.toStdString();
        QString stadtInput = stadt->text();
        stadtInputString = stadtInput.toStdString();
        QString hausNummerInput = hausNummer->text();
        hausNummerInputString = hausNummerInput.toStdString();
        QString plzInput = plz->text();
        plzInputInt = plzInput.toInt();
        laengengradInput = german.toDouble(laengengradAdresse->text());  // ok == true,  d == 1234.56
        breitengradInput = german.toDouble(breitengradAdresse->text()) ;// uses ',' as a decimal point

        errorLabelAdresse->setText("neu Adresse wurde gespeichert");
        errorLabelAdresse->setVisible(true);
        errorLabelAdresse->setStyleSheet("QLineEdit { border: 1px solid green; }");
        Orte.push_back(new Adresse(laengengradInput,breitengradInput, strasseInputString
                                   ,hausNummerInputString,plzInputInt,stadtInputString,nameInputString));
        cout << Orte.size() << endl;

    }else{

        if(!nameAdresse->hasAcceptableInput())
            handleInvalidInput(nameAdresse, errorLabelAdresse);
        if(!strasse->hasAcceptableInput())
            handleInvalidInput(strasse, errorLabelAdresse);
        if(!stadt->hasAcceptableInput())
            handleInvalidInput(stadt, errorLabelAdresse);
        if(!hausNummer->hasAcceptableInput())
            handleInvalidInput(hausNummer, errorLabelAdresse);
        if(!plz->hasAcceptableInput())
            handleInvalidInput(plz, errorLabelAdresse);
        if(!breitengradAdresse->hasAcceptableInput() ||  (breitengradAdresse->text().isEmpty()))
            handleInvalidInput(breitengradAdresse, errorLabelAdresse);
        if(!laengengradAdresse->hasAcceptableInput() || laengengradAdresse->text().isEmpty())
            handleInvalidInput(laengengradAdresse, errorLabelAdresse);

    }
}


void MainWindow::createNeuPoiForm(){
    widgetNeuPoi->setVisible(false);

    QFormLayout* layout = new QFormLayout();
    layout->setFormAlignment(Qt::AlignLeft);
    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    layout->setContentsMargins(50,20,50, 0 );
    layout->setSpacing(30);
    layout->setLabelAlignment(Qt::AlignLeft);
    widgetNeuPoi->setLayout(layout);

    //qobject_cast<QFormLayout* >(widgetNeuAdresse->layout());
    errorLabelPoi = new QLabel("Invalid Input");
    errorLabelPoi->setVisible(false);

    //QRegularExpressionValidator* validator = new QRegularExpressionValidator(rx,0);
    namePoi = new QLineEdit();
    namePoi->setMinimumWidth(250);
    namePoi->setMinimumHeight(30);
    namePoi->setValidator(stringValidator);

    kategorie =  new QLineEdit();
    kategorie->setMinimumWidth(250);
    kategorie->setMinimumHeight(30);
    kategorie->setValidator(stringValidator);
    kategorie->setPlaceholderText("E.g. Restaurant");

    bemerkung =  new QLineEdit();
    bemerkung->setMinimumWidth(250);
    bemerkung->setMinimumHeight(30);
    bemerkung->setValidator(stringValidator);

    laengengradPoi = new QLineEdit();
    laengengradPoi->setMinimumWidth(250);
    laengengradPoi->setMinimumHeight(30);
    laengengradPoi->setValidator(doubleValidator);
    laengengradPoi->setPlaceholderText("49,77");

    breitengradPoi = new QLineEdit();
    breitengradPoi->setMinimumWidth(250);
    breitengradPoi->setMinimumHeight(30);
    breitengradPoi->setValidator(doubleValidator);
    laengengradPoi->setPlaceholderText("8,77");

    BTN_neuPoiSpeichern =  new QPushButton("Speichern");
    BTN_neuPoiSpeichern->setFixedSize(120,50);

    layout->addRow(errorLabelPoi);
    layout->addRow(tr("Name:"), namePoi);
    layout->addRow(tr("Kategorie:"),kategorie);
    layout->addRow(tr("Bemerkung:"),bemerkung);
    layout->addRow(tr("laengengrad"), laengengradPoi);
    layout->addRow(tr("breitengrad"), breitengradPoi);
    layout->addRow(BTN_neuPoiSpeichern);



}
void MainWindow::on_click_BTN_Poi(){
    // clearLineEditsPoi();
    //Hide other widgets

    // resetErrorActions(2, errorLabelAdresse);
    clearLineEditsPoi();
    widgetOrtAnlegen->setVisible(false);
    widgetKarteAnzeigen->setVisible(false);
    widgetEntfernungBerechnen->setVisible(false);
    widgetErgebnisEntfernungBerechnen->setVisible(false);
    widgetBinaerImpExp->setVisible(false);
    widgetCSVImpExp->setVisible(false);
    widgetNeuAdresse->setVisible(false);
    widgetNeuPoi->setVisible(true);
    ui-> horizontalLayout_mainView_OrtAnlegen->addWidget(widgetNeuPoi);

}
void MainWindow::on_click_BTN_poiSpeichern()
{
    resetErrorActions(2, errorLabelPoi);
    //reset Qwidgets color and remove invalid input error message from previous session if any

    std::string namePoiString, kategorieString, bemerkungString;
    double laengengradPoiDouble, breitengradPoiDouble;

    int pos = 0;

    /**namePoi->setValidator(validator);
    kategorie->setValidator(validator);
    bemerkung->setValidator(validator);*/
    QDoubleValidator* doubleValidator = new QDoubleValidator(1.00,99999.00,2, laengengradPoi);
    doubleValidator->setLocale(QLocale::German);
    QLocale::setDefault(QLocale::German); // uses ',' as a decimal point
    QLocale german;
    doubleValidator->setRange(1.00,99999.00);
    // default-constructed German locale

    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    laengengradPoi->setValidator(doubleValidator);
    breitengradPoi->setValidator(doubleValidator);

    //wenn alle Inputs richtig sind, show saved message

    if(namePoi->hasAcceptableInput() && kategorie->hasAcceptableInput() && bemerkung->hasAcceptableInput() && laengengradPoi->hasAcceptableInput()
            && breitengradPoi->hasAcceptableInput() && (!laengengradPoi->text().isEmpty()) && (!breitengradPoi->text().isEmpty())  ){

        namePoiString = namePoi->text().toStdString();
        kategorieString = kategorie->text().toStdString();
        bemerkungString = bemerkung->text().toStdString();
        laengengradPoiDouble = german.toDouble(laengengradPoi->text());  // ok == true,  d == 1234.56
        breitengradPoiDouble = german.toDouble(breitengradPoi->text()) ;

        Orte.push_back(new PoI(laengengradPoiDouble, breitengradPoiDouble,
                               kategorieString, bemerkungString, namePoiString));
        cout << "Neu poui saved. new Orte size is: "<< Orte.size() << endl;
        errorLabelPoi->setStyleSheet("QLineEdit { border: 1px solid green; }");
        errorLabelPoi->setText("neu Adresse wurde gespeichert");
        errorLabelPoi->setVisible(true);

    }else{
        errorLabelPoi->setText("Invalid input");
        if(!namePoi->hasAcceptableInput())
            handleInvalidInput(namePoi, errorLabelPoi);
        if(!kategorie->hasAcceptableInput())
            handleInvalidInput(kategorie, errorLabelPoi);
        if(!bemerkung->hasAcceptableInput())
            handleInvalidInput(bemerkung, errorLabelPoi);
        if(!laengengradPoi->hasAcceptableInput() ||  (laengengradPoi->text().isEmpty()))
            handleInvalidInput(laengengradPoi, errorLabelPoi);
        if(!breitengradPoi->hasAcceptableInput() || breitengradPoi->text().isEmpty())
            handleInvalidInput(breitengradPoi, errorLabelPoi);
    }
}
void MainWindow::createWidgetVieKarteAnzeigen()
{
    //QWidgets for karteAnzeigen button
    QFormLayout* layout = new QFormLayout();
    layout->setFormAlignment(Qt::AlignLeft);
    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    layout->setContentsMargins(0,20,50, 0 );
    layout->setSpacing(10);
    layout->setLabelAlignment(Qt::AlignLeft);
    widgetKarteAnzeigen->setLayout(layout);
    widgetKarteAnzeigen->setVisible(false);

    QFont fontPlaintext;
    fontPlaintext.setPointSize(14);
    StartZielErrorLabel = new QLabel("Invalid Input");
    layout->addWidget( StartZielErrorLabel);
    StartZielErrorLabel->setVisible(false);
    StartZielErrorLabel->setFont(fontPlaintext);

    StartZielLabel = new QLabel("Start Auswahl: ");
    StartZielLabel->setFont(fontPlaintext);
    layout->addWidget( StartZielLabel);
    StartZielLabel->setVisible(false);

    tableWidget = new QTableWidget(Orte.size(), 6,this);
    tableWidget->setFont(fontPlaintext);
    modifyQTableWidget(tableWidget);
    layout->addWidget( tableWidget);
    tableWidget->setVisible(true);

    lineEditStart = new QLineEdit();
    BTN_SaveStart = new QPushButton("Speichern");
    BTN_SaveStart->setFont(fontPlaintext);
    lineEditZiel= new QLineEdit();
    lineEditZiel->setFont(fontPlaintext);
    lineEditZiel->setVisible(false);
    layout->addWidget(lineEditStart );
    //layout->addWidget(lineEditZiel );
    layout->addWidget(BTN_SaveStart);
    lineEditStart->setVisible(false);
    lineEditStart->setFont(fontPlaintext);
    BTN_SaveStart->setVisible(false);
    BTN_SaveStart->setFont(fontPlaintext);
    layout->addWidget(lineEditZiel );
    BTN_SaveZiel = new QPushButton("Entfernung berechnen");
    layout->addWidget(lineEditZiel );
}

void MainWindow::karteAnzeigen(){

    StartZielErrorLabel->setText("Invalid Input");
    StartZielLabel->setText("Start Auswahl: ");
    //remove all Widget for Entfernung berechnung and show only the tableWidget
    StartZielErrorLabel->setVisible(false);
    StartZielLabel->setVisible(false);
    BTN_SaveStart->setVisible(false);
    lineEditStart->setVisible(false);
    BTN_SaveZiel->setVisible(false);
    lineEditZiel->setVisible(false);


    widgetOrtAnlegen->setVisible(false);
    widgetEntfernungBerechnen->setVisible(false);
    widgetErgebnisEntfernungBerechnen->setVisible(false);
    widgetBinaerImpExp->setVisible(false);
    widgetCSVImpExp->setVisible(false);
    widgetNeuAdresse->setVisible(false);
    widgetNeuPoi->setVisible(false);

    QTableWidgetItem* ort = nullptr;
    cout << "Orte size here: " << Orte.size() << endl;
    tableWidget->setRowCount(Orte.size());
    for (size_t i = 0; i < Orte.size(); i++) {

        //plaintText->appendPlainText(QString::fromStdString(Orte.at(i)->attributeAlsString(';')));
        ort = new QTableWidgetItem(QString::fromStdString(to_string(Orte.at(i)->getID())));
        tableWidget->setItem(i, 0, ort);
        ort = new QTableWidgetItem(QString::fromStdString(Orte.at(i)->getTypeAsString()));
        tableWidget->setItem(i, 1, ort);
        ort = new QTableWidgetItem(QString::fromStdString(Orte.at(i)->getName()));
        tableWidget->setItem(i, 2, ort);
        ort = new QTableWidgetItem(QString::fromStdString(to_string(Orte.at(i)->getLg())));
        tableWidget->setItem(i, 3, ort);
        ort = new QTableWidgetItem(QString::fromStdString(to_string(Orte.at(i)->getBg())));
        tableWidget->setItem(i, 4, ort);
        ort = new QTableWidgetItem(QString::fromStdString(Orte.at(i)->getParameters()));
        tableWidget->setItem(i, 5, ort);
    }
    tableWidget->setVisible(true);

    widgetKarteAnzeigen->setVisible(true);

}
void MainWindow::modifyQTableWidget(QTableWidget* tableWidget){
    QFont fontPlaintext;
    fontPlaintext.setPointSize(16);
    tableWidget->setShowGrid(false);
    // Hide the vertical header (row numbers)
    tableWidget->verticalHeader()->setVisible(false);
    QStringList columnNames;
    QTableWidgetItem* headerItem;

    tableWidget->setFont(fontPlaintext);
    columnNames << "ID" << "Typ" << "Name" << "Breitengrad" << "Laengengrad" << "Parameters";
    headerItem = new QTableWidgetItem(columnNames[0]);
    tableWidget->setHorizontalHeaderItem(0, headerItem);
    headerItem = new QTableWidgetItem(columnNames[1]);
    tableWidget->setHorizontalHeaderItem(1, headerItem);
    headerItem = new QTableWidgetItem(columnNames[2]);
    tableWidget->setHorizontalHeaderItem(2, headerItem);
    headerItem = new QTableWidgetItem(columnNames[3]);
    tableWidget->setHorizontalHeaderItem(3, headerItem);
    headerItem = new QTableWidgetItem(columnNames[4]);
    tableWidget->setHorizontalHeaderItem(4, headerItem);
    headerItem = new QTableWidgetItem(columnNames[5]);
    tableWidget->setHorizontalHeaderItem(5, headerItem);
    // Set the resize mode for the first column to ResizeToContents
    // Set the resize mode for the first column to ResizeToContents
    QHeaderView* header = tableWidget->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);

}



void MainWindow::on_click_BTN_SaveStart(){
    lineEditStart->setStyleSheet("QLabel { border: 2px solid black; }");
    lineEditStart->setVisible(true);
    lineEditStart->setValidator(intValidator);
    widgetKarteAnzeigen->setVisible(true);
    StartZielErrorLabel->setStyleSheet("QLineEdit { border: 1px solid black; }");
    StartZielErrorLabel->setVisible(false);
    QFormLayout* layout = dynamic_cast<QFormLayout*>(widgetKarteAnzeigen->layout());
    if(lineEditStart->hasAcceptableInput() &&   !lineEditStart->text().isEmpty() && getIndexOfOrt(lineEditStart->text().toInt())  != -1 ){
        startID = lineEditStart->text().toInt();
        std::size_t indexStart =  getIndexOfOrt(startID);
        //checks if the chosen Ort Id is present in the array of Orte
        BTN_SaveStart->setVisible(false);
        QTableWidgetItem* ort = nullptr;

        //remove start Ort from the Ziel choices
        tableWidget->removeRow(indexStart);

        StartZielLabel->setText("Ziel Auswahl: ");
        StartZielLabel->setVisible(true);
        lineEditStart->clear();

        widgetKarteAnzeigen-> layout()->removeWidget(BTN_SaveStart);
        widgetKarteAnzeigen->layout()->addWidget(BTN_SaveZiel);
        BTN_SaveZiel->setVisible(true);
        //find the index of the chosen id in the vector

        cout << indexStart << endl;
        //show the chosen Ort as Start
        QFont fontPlaintext;
        fontPlaintext.setPointSize(14);
        QString startText = QString::fromStdString(Orte.at(indexStart)->getName()) + ", "+ QString::fromStdString(Orte.at(indexStart)->getParameters())  ;
        StartZielLabel->setText("Von: ");
        lineEditStart->setFont(fontPlaintext);
        layout->insertRow(2, lineEditStart);
        lineEditStart->setText(startText);
        lineEditStart->setReadOnly(true);
        lineEditZiel->setFont(fontPlaintext);
        lineEditStart->setVisible(true);
        lineEditZiel->setVisible(true);


    }else{
        handleInvalidInput(lineEditStart,StartZielErrorLabel );
    }
}
void MainWindow::on_click_BTN_ZielSpeichern(){

    //QWidgets for karteAnzeigen button
    QFormLayout* layout = new QFormLayout();
    layout->setFormAlignment(Qt::AlignLeft);
    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    layout->setContentsMargins(0,20,50, 0 );
    layout->setSpacing(10);
    layout->setLabelAlignment(Qt::AlignLeft);


    if(lineEditZiel->hasAcceptableInput() &&   !lineEditZiel->text().isEmpty() && getIndexOfOrt(lineEditZiel->text().toInt())  != -1){

        ZielID =  lineEditZiel->text().toInt();

        std::size_t indexZiel =  getIndexOfOrt(ZielID);
        std::size_t indexStart =  getIndexOfOrt(startID);
           QString startText = QString::fromStdString(Orte.at(indexStart)->getName()) + ", "+ QString::fromStdString(Orte.at(indexStart)->getParameters())  ;
        QString zielText = QString::fromStdString(Orte.at(indexZiel)->getName())
                + ", " + QString::fromStdString(Orte.at(indexZiel)->getParameters());

        double entfernungErgebnis = Orte.at(indexStart)->berechneEntfernung(Orte.at(indexZiel));
        QString ergebnisString = "Die Entfernung von: " + startText+ "  nach: "+ zielText+ " betraegt: "
                + QString::number(entfernungErgebnis) + " KM";
        lineEditZiel->setText(zielText);
         QMessageBox::information(this,"Message", ergebnisString );


    }else{
        handleInvalidInput(lineEditZiel-1,StartZielErrorLabel );
    }

    delete layout;
}
void MainWindow::exporTierenImportierenCSV(){

}

QFormLayout* MainWindow::setFormLayoutSettings(){
    QFormLayout* layout = new QFormLayout();
    layout->setFormAlignment(Qt::AlignLeft);
    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    layout->setContentsMargins(50,20,50, 0 );
    layout->setSpacing(30);
    layout->setLabelAlignment(Qt::AlignLeft);

    return layout;

}
void MainWindow::createWindowBinaerImpExp()
{


    QHBoxLayout* layout = new QHBoxLayout();
    widgetBinaerImpExp->setLayout(layout);
    exportingStatusMessageLabel = new QLabel("Exporting data...");
    layout->addWidget(exportingStatusMessageLabel);
    exportingStatusMessageLabel->setVisible(false);

    BTN_ImportBinaer = new SquareQPushButton("Import");
    layout->addWidget(BTN_ImportBinaer);
    BTN_ImportBinaer->setVisible(true);


    BTN_ExportBinaer = new SquareQPushButton("Export");
    layout->addWidget(BTN_ExportBinaer);
    // QObject::connect(ui->BTN_OrtAnlegen, &QPushButton::clicked, this, &MainWindow::neuAdresse);
    BTN_ExportBinaer->setVisible(true);

    widgetBinaerImpExp->setVisible(false);
}
void MainWindow::on_click_BTN_BinaerImpExp()
{
    BTN_ImportBinaer->setVisible(true);
    BTN_ExportBinaer->setVisible(true);
    //Hide other widgets
    widgetKarteAnzeigen->setVisible(false);
    widgetEntfernungBerechnen->setVisible(false);
    widgetCSVImpExp->setVisible(false);
    widgetNeuAdresse->setVisible(false);
    widgetNeuPoi->setVisible(false);
    widgetOrtAnlegen->setVisible(false);
    widgetErgebnisEntfernungBerechnen->setVisible(false);

    widgetBinaerImpExp->setVisible(true);
    exportingStatusMessageLabel->setVisible(false);
    exportingStatusMessageLabel->setText("");
}
int MainWindow::getIndexOfOrt(int input){
    auto it = std::find_if(Orte.begin(), Orte.end(),[input](const Ort* ort){
        if(input == ort->getID()){
            return true;
        }
        else{
            return false;
        }
    });

    if(it != Orte.end()){//if yes
        //get the index where the id got the match
        return std::distance(Orte.begin(), it);

    }else{
        return -1;
    }

}

void MainWindow::on_click_BTN_ExportBinaer()
{
    BTN_ImportBinaer->setVisible(false);
    BTN_ExportBinaer->setVisible(false);

    int auswahl, vSize/*, id{0}*/;

    int tmp_id;
    int tmp_typ;
    double tmp_Lg;
    double tmp_Bg;
    string tmp_strasse;
    string tmp_hausNr;
    int tmp_plz;
    string tmp_stadt;
    string tmp_name;
    string tmp_kategorie;
    string tmp_bemerkung;
    size_t stringSize = tmp_strasse.size();
    char terminator = '\0';

    fstream outFile;
    Adresse* adresse = nullptr;
    PoI* poi = nullptr;

    ///how file save dialogbox
    QString filename = QFileDialog::getSaveFileName(this,"Save File", "",
                                                    "Binary Files (*.bin)");

    //QFile file(filename);

    if (Orte.empty ()){
        cout << "Es wurden bisher keine Orte hinzugefügt" << endl;
        return;
    }

    outFile.open(filename.toStdString().c_str(), ios::out | ios::binary);
    if (!outFile){
        QMessageBox::information(this,"Message"," kann nicht geoeffnet werden!\n");
        exit(-1);
    }
    vSize = Orte.size ();
    outFile.write ((char*)(&vSize), sizeof(vSize));

    if(outFile.is_open()){
        for(int i = 0; i < vSize; i++){

            //id
            tmp_id = Orte.at(i)->getID();
            outFile.write((char*)(&tmp_id), sizeof(tmp_id));
            //type
            tmp_typ = Orte.at(i)->getType();
            outFile.write((char*)(&tmp_typ), sizeof(tmp_typ));
            //name
            tmp_name=Orte.at(i)->getName();
            stringSize=tmp_name.length()+1;
            outFile.write((char*)(&stringSize),sizeof(stringSize));
            outFile.write(tmp_name.c_str(),stringSize);
            //Lg
            tmp_Lg = Orte.at(i)->getLg();
            outFile.write((char*)(&tmp_Lg), sizeof(tmp_Lg));
            //Bg
            tmp_Bg = Orte.at(i)->getBg();
            outFile.write((char*)(&tmp_Bg), sizeof(tmp_Bg));

            if (Orte[i]->getType() == 1){

                adresse = dynamic_cast<Adresse*>(Orte[i]);

                //Straße
                tmp_strasse=adresse->getStrasse();
                stringSize=tmp_strasse.length()+1;
                outFile.write((char*)(&stringSize),sizeof(stringSize));
                outFile.write(tmp_strasse.c_str(),stringSize);
                //Hausnr.
                tmp_hausNr=adresse->getHausnummer();
                stringSize=tmp_hausNr.length()+1;
                outFile.write((char*)(&stringSize),sizeof(stringSize));
                outFile.write(tmp_hausNr.c_str(),stringSize);
                //PLZ
                tmp_plz = adresse->getPlz();
                outFile.write((char*)(&tmp_plz), sizeof(tmp_plz));
                //Stadt
                tmp_stadt=adresse->getStadt();
                stringSize=tmp_stadt.length()+1;
                outFile.write((char*)(&stringSize),sizeof(stringSize));
                outFile.write(tmp_stadt.c_str(),stringSize);

                outFile.write (&terminator, 1);
            }
            else if(Orte[i]->getType() == 2){

                poi = dynamic_cast<PoI*>(Orte[i]);

                //Kategorie
                tmp_kategorie=poi->getKategorie();
                stringSize=tmp_kategorie.length()+1;
                outFile.write((char*)(&stringSize),sizeof(stringSize));
                outFile.write(tmp_kategorie.c_str(),stringSize);
                //Bemerkung
                tmp_bemerkung=poi->getBemerkung();
                stringSize=tmp_bemerkung.length()+1;
                outFile.write((char*)(&stringSize),sizeof(stringSize));
                outFile.write(tmp_bemerkung.c_str(),stringSize);

                outFile.write (&terminator, 1);
            }
        }
        outFile.close();
        QMessageBox::information(this,"Message"," Daten wurden erfolgreich exportiert\n");
        Orte.clear();
        exportingStatusMessageLabel->setText("Daten wurden erfolgreich exportiert");
        exportingStatusMessageLabel->setVisible(true);
        BTN_ImportBinaer->setVisible(false);
        BTN_ExportBinaer->setVisible(false);
    }




}
void MainWindow::on_click_BTN_ImportBinaer()
{
    int id=0, type=0, vSize=0, plz=0;
    size_t stringSize = 0;
    double Lg= 0.00, Bg =0.00;
    char terminator = '\0';
    char in_name[160]{};
    char in_strasse[160]{};
    char in_hausnummer[160]{};
    char in_stadt[160]{};
    char in_kategorie[160]{};
    char in_bemerkung[160]{};
    string inputFileName, outputFileName;
    fstream outputFileStream;
    Adresse* adresse = nullptr;
    PoI* poi = nullptr;


    int tmp_id;
    int tmp_typ;
    double tmp_Lg;
    double tmp_Bg;
    string tmp_strasse;
    string tmp_hausNr;
    int tmp_plz;
    string tmp_stadt;
    string tmp_name;
    string tmp_kategorie;
    string tmp_bemerkung;


    ifstream inFile;
    BTN_ImportBinaer->setVisible(false);
    BTN_ExportBinaer->setVisible(false);
    exportingStatusMessageLabel->setVisible(false);
    //Open  file dialog box to let user find the file to read
    QString filePath = QFileDialog::getOpenFileName(widgetBinaerImpExp, "Open File", "", "Binary Files (*.bin)");
    inFile.open(filePath.toStdString().c_str(), ios::in | ios::binary);

    if (!inFile) {
        cerr << filePath.toStdString() << " kann nicht geoeffnet werden!\n";
        exit(-1);
    }
    if(inFile.is_open())
        Orte.clear();
    cout << "Bereit zum Lesen der Daten..." << endl;
    inFile.read((char*)(&vSize),sizeof(vSize));
    cout << "Anzahl der zu importierenden Elemente: " << vSize << endl;

    for (int i = 0; i < vSize; i++) {
        //id
        inFile.read((char*)(&tmp_id),sizeof(tmp_id));
        //Typ
        inFile.read((char*)(&tmp_typ),sizeof(tmp_typ));
        cout << "Typ: " << tmp_typ << endl;
        //straße
        inFile.read((char*)(&stringSize),sizeof(stringSize));
        tmp_name.resize(stringSize);
        inFile.read((char*)in_name,stringSize);
        cout << "Importierter Name: " << in_name << endl;
        //Lg
        inFile.read((char*)(&tmp_Lg),sizeof(tmp_Lg));
        cout << "Importierter Lg: " << tmp_Lg << endl;
        //Bg
        inFile.read((char*)(&tmp_Bg),sizeof(tmp_Bg));
        cout << "Importierter Bg: " << tmp_Bg << endl;

        if (tmp_typ == 1) {
            //straße
            inFile.read((char*)(&stringSize),sizeof(stringSize));
            tmp_strasse.resize(stringSize);
            inFile.read((char*)in_strasse,stringSize);
            //hausnr.
            inFile.read((char*)(&stringSize),sizeof(stringSize));
            tmp_hausNr.resize(stringSize);
            inFile.read((char*)in_hausnummer,stringSize);
            //plz
            inFile.read((char*)(&tmp_plz),sizeof(tmp_plz));
            //stadt
            inFile.read((char*)(&stringSize),sizeof(stringSize));
            tmp_stadt.resize(stringSize);
            inFile.read((char*)in_stadt,stringSize);

            inFile.read((char*)&terminator,1);
            Orte.push_back(new Adresse(tmp_id, tmp_Lg, tmp_Bg, in_strasse, in_hausnummer, tmp_plz, in_stadt, in_name));
        }
        else if (tmp_typ == 2){
            //Kategorie
            inFile.read((char*)(&stringSize),sizeof(stringSize));
            tmp_kategorie.resize(stringSize);
            inFile.read((char*)in_kategorie,stringSize);
            //Bemerkung
            inFile.read((char*)(&stringSize),sizeof(stringSize));
            tmp_bemerkung.resize(stringSize);
            inFile.read((char*)in_bemerkung,stringSize);

            inFile.read((char*)&terminator,1);
            Orte.push_back(new PoI(tmp_id, tmp_Lg, tmp_Bg, in_kategorie, in_bemerkung, in_name));
        }
    }
    karteAnzeigen();
}

void MainWindow::entfernungBerechnen(){
    QFont fontPlaintext;
    fontPlaintext.setPointSize(16);
    StartZielErrorLabel->setText("Invalid Input");
    StartZielLabel->setText("Start Auswahl: ");
    //remove all Widget for Entfernung berechnung and show only the tableWidget


    widgetOrtAnlegen->setVisible(false);
    widgetKarteAnzeigen->setVisible(true);
    widgetErgebnisEntfernungBerechnen->setVisible(false);
    widgetBinaerImpExp->setVisible(false);
    widgetCSVImpExp->setVisible(false);
    widgetNeuAdresse->setVisible(false);
    widgetOrtAnlegen->setVisible(false);

    StartZielErrorLabel->setFont(fontPlaintext);
    lineEditStart->setStyleSheet("QLineEdit { border: 1px solid black; }");
    lineEditStart->setFont(fontPlaintext);
    lineEditStart->clear();
    lineEditStart->setReadOnly(false);
    BTN_SaveStart->setFont(fontPlaintext);

    lineEditZiel->setVisible(false);
    lineEditZiel->setStyleSheet("QLineEdit { border: 1px solid black; }");
    lineEditZiel->setFont(fontPlaintext);

    karteAnzeigen();
    StartZielErrorLabel->setVisible(false);
    StartZielLabel->setVisible(true);
    BTN_SaveStart->setVisible(true);
    lineEditStart->setVisible(true);
    BTN_SaveZiel->setVisible(false);
    lineEditZiel->setVisible(false);
    StartZielLabel->setFont(fontPlaintext);

    //TODO:: If id choice exists, call showZielChoices and remove the chosen Start Ort fromt he choices
    //TODO::Maybe add a readOnly lineEdit to show the chosen start Ort.

}
void MainWindow::createWindowCSVImpExp()
{
    QHBoxLayout* layout = new QHBoxLayout();
    widgetCSVImpExp->setLayout(layout);


    BTN_ImportCSV = new SquareQPushButton("Import");
    layout->addWidget(BTN_ImportCSV);

    BTN_ExportCSV = new SquareQPushButton("Export");
    layout->addWidget(BTN_ExportCSV);
    // QObject::connect(ui->BTN_OrtAnlegen, &QPushButton::clicked, this, &MainWindow::neuAdresse);
    BTN_ExportBinaer->setVisible(true);

    widgetCSVImpExp->setVisible(false);
}
void MainWindow::on_click_BTN_CSVImpExp()
{

    BTN_ExportCSV->setVisible(true);
    BTN_ImportCSV->setVisible(true);
    //Hide other widgets
    widgetKarteAnzeigen->setVisible(false);
    widgetEntfernungBerechnen->setVisible(false);

    widgetNeuAdresse->setVisible(false);
    widgetNeuPoi->setVisible(false);
    widgetOrtAnlegen->setVisible(false);
    widgetErgebnisEntfernungBerechnen->setVisible(false);

    widgetBinaerImpExp->setVisible(false);
    widgetCSVImpExp->setVisible(true);

}
void MainWindow::handleInvalidInput(QLineEdit* widgetToCheck, QLabel* errorLabel){

    QPalette pal = errorLabel->palette();
    pal.setColor(QPalette::Text, Qt::red);
    errorLabel->setPalette(pal);

    widgetToCheck->displayText();
    if(widgetToCheck->text().isEmpty()){
        errorLabel->setText("ERROR: Input cannot be empty");
        errorLabel->setStyleSheet("QLabel { border: 2px solid red; }");
    }else{
        errorLabel->setText("Invalid Input! Please enter like this" + widgetToCheck->placeholderText());
    }
    widgetToCheck->setStyleSheet("QLineEdit { border: 1px solid red; }");
    errorLabel->setVisible(true);
}
void MainWindow::on_click_BTN_ImportCSV()
{

    BTN_ExportCSV->setVisible(false);
    BTN_ImportCSV->setVisible(false);

    int auswahl;
    bool inputFail;
    ifstream inFile;
    const char delimiter = ';';
    string dateiName;

    string strasse{}, stadt{}, temp_name{},kategorie{}, bemerkung{}, LgStr{}, BgStr{}, hausNummer{};
    int id, type, plz;
    double Lg{}, Bg{};

    QString filePath = QFileDialog::getOpenFileName(widgetBinaerImpExp, "Open File", ""
                                                    , "CSV Files (*.csv)");

    inFile.open(filePath.toStdString(), ios::in);

    if (!inFile.good()){
        cout << "Datei konnte nicht geoeffnet werden" << endl;
    }else{
        string line;
        int zeileAnz;

        getline(inFile, line);
        zeileAnz = stoi(line);

        for(int i=0; i < zeileAnz; i++){
            getline(inFile, line, ';');
            id = stoi(line);

            getline(inFile, line, ';');
            type = stoi(line);

            if(type == 1){

                getline(inFile, temp_name, ';');//name
                getline(inFile, strasse, ';');//straße
                getline(inFile, hausNummer, ';');//hausnummer
                getline(inFile, line, ';');//plz
                plz = stoi(line);
                getline(inFile, stadt, ';');//Stadt
                getline(inFile, LgStr, ';');//lg
                Lg = stod(LgStr);
                getline(inFile, BgStr);//bg
                Bg = stod(BgStr);

                this->Orte.push_back(new Adresse(id, Lg, Bg, strasse, hausNummer, plz, stadt, temp_name));

            }else if(type == 2){

                getline(inFile, temp_name, ';');//name
                getline(inFile, kategorie, ';');//Kategorie
                getline(inFile, bemerkung, ';');//Bemerkung
                getline(inFile, LgStr, ';');//lg
                Lg = stod(LgStr);
                getline(inFile, BgStr);//bg
                Bg = stod(BgStr);

                this->Orte.push_back(new PoI(id, Lg, Bg, kategorie, bemerkung, temp_name));
            }
        }
        karteAnzeigen();
    }
}

void MainWindow::on_click_BTN_ExportCSV()
{
    BTN_ExportCSV->setVisible(false);
    BTN_ImportCSV->setVisible(false);
    int auswahl;
    bool inputFail;
    ifstream inFile;
    const char delimiter = ';';
    string dateiName;

    ofstream outFile;


    string temp_OrtString= "";
    int zeileAnz{0};
    string zeileAnzString = "";
    ///how file save dialogbox
    QString filename = QFileDialog::getSaveFileName(this,"Save File", "",
                                                    "CSV Files (*.csv)");


    if(Orte.size()< 1){
        QMessageBox::information(this, "Message", "Es gibt noch keine Orte vorhanden. BItte zuerst Orte anlegen");
    }
    else{
        for(size_t i = 0; i < Orte.size(); i++){
            zeileAnz++;
        }

        outFile.open(filename.toStdString().c_str(), ios::out | ios::app);

        if(outFile.is_open()){
            QMessageBox::information(this, "Message", "File ist bereit auf CSV-Format zu schreiben");
            zeileAnzString = to_string(zeileAnz) + "\n";
            outFile << zeileAnzString;

            for(size_t i = 0; i < Orte.size(); i++){
                if(Orte[i]->getType() == 1){
                    temp_OrtString =  Orte[i]->attributeAlsString(';');
                }
                else{
                    temp_OrtString =   Orte[i]->attributeAlsString(';');
                }
                outFile << temp_OrtString;
            }
        }
        else{
            QMessageBox::information(this, "Message", "Failed to open file");
            exit(-1);
        }
        QMessageBox::information(this, "Message", "Daten wurden erfolgreich exportiert");
        Orte.clear();
    }
}


void MainWindow::clearLineEditsAdresse(){

    // lineEditStart->clear();
    nameAdresse->clear();
    strasse->clear();
    hausNummer->clear();
    plz->clear();
    stadt->clear();
    breitengradAdresse->clear();
    laengengradAdresse->clear();
    errorLabelAdresse->setVisible(false);
}
void MainWindow::clearLineEditsPoi(){
    namePoi->clear();
    kategorie->clear();
    bemerkung->clear();
    laengengradPoi->clear();
    breitengradPoi->clear();
    errorLabelPoi->clear();
    errorLabelPoi->setVisible(false);
    resetErrorActions(2,errorLabelPoi );

}

void MainWindow::resetErrorActions(int OrtTypeCode, QLabel* errorLabel){
    QPalette pal = errorLabel->palette();
    pal.setColor(QPalette::Text, Qt::black);
    errorLabel->setPalette(pal);
    errorLabel->setVisible(false);

    if(OrtTypeCode == 1){
        nameAdresse->setStyleSheet("QLineEdit { border: 1px solid black; }");
        strasse->setStyleSheet("QLineEdit { border: 1px solid black; }");
        stadt->setStyleSheet("QLineEdit { border: 1px solid black; }");
        hausNummer->setStyleSheet("QLineEdit { border: 1px solid black; }");
        plz->setStyleSheet("QLineEdit { border: 1px solid black; }");
        breitengradAdresse->setStyleSheet("QLineEdit { border: 1px solid black; }");
        laengengradAdresse->setStyleSheet("QLineEdit { border: 1px solid black; }");
        errorLabelAdresse->setStyleSheet("QLineEdit { border: 1px solid black; }");

    }else if (OrtTypeCode == 2){
        namePoi->setStyleSheet("QLineEdit { border: 1px solid black; }");
        kategorie->setStyleSheet("QLineEdit { border: 1px solid black; }");
        bemerkung->setStyleSheet("QLineEdit { border: 1px solid black; }");
        laengengradPoi->setStyleSheet("QLineEdit { border: 1px solid black; }");
        breitengradPoi->setStyleSheet("QLineEdit { border: 1px solid black; }");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    cout <<"Program ended" << endl;
}

void MainWindow::on_click_BTN_Exit()
{
    cout <<"Program ended" << endl;
    for(auto ort : Orte){
        delete ort;
    }

    Orte.clear();
    delete BTN_Adresse;
    delete BTN_POI;
    delete widgetOrtAnlegen ;
    delete widgetKarteAnzeigen ;
    delete widgetEntfernungBerechnen ;
    delete widgetBinaerImpExp  ;
    delete widgetCSVImpExp ;
    delete widgetNeuAdresse ;
    delete widgetNeuPoi ;
    delete BTN_adresseSpeichern ;
    delete BTN_neuPoiSpeichern ;
    delete StartZielLabel ;
    delete lineEditStart ;
    delete nameAdresse ;
    delete strasse ;
    delete hausNummer ;
    delete plz ;
    delete stadt ;
    delete namePoi  ;
    delete kategorie  ;
    delete bemerkung ;
    delete breitengradAdresse ;
    delete laengengradAdresse ;
    delete breitengradPoi ;
    delete laengengradPoi ;
    delete BTN_SaveStart ;
    delete BTN_SaveZiel ;
    delete plaintText ;
    delete errorLabelAdresse ;
    delete errorLabelPoi ;
    delete nameAdresseLabel;
    delete StartZielErrorLabel;
    delete     stringValidator;
    delete stringNumValidator;
    delete doubleValidator;
    delete ui;
}
