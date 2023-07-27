#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qformlayout.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qlineedit.h"
#include "QtWidgets/qtablewidget.h"
#include "ort.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
    void addOrtMenu();
    void neuAdresse(QWidget* parent);
    void on_click_BTN_adresseSpeichern();
    void on_click_BTN_Adresse();
    void on_click_BTN_poiSpeichern();
    void on_click_BTN_Poi();
    void clearLineEditsPoi();
    void karteAnzeigen();
    void createWidgetVieKarteAnzeigen();
    void entfernungBerechnen();
    void createWindowBinaerImpExp();
    void exporTierenImportierenCSV();
    void addOrtAnlegenView();
    void exitProgramm();
    void createNeuAdresseForm();
    void createNeuPoiForm();
    void neuAdresseEingabe();
    void qWidgetErstellen();
    void qButtonsErstellen();
    QFormLayout*  setFormLayoutSettings();
    void handleInvalidInput(QLineEdit* widgetToCheck, QLabel* errorLabel);
    void resetErrorActions(int OrtTypeCode, QLabel* errorLabel);
    void handleLineEditTextChanged();
    void showZielChoices();
    void clearLineEditsAdresse();
    void on_click_BTN_SaveStart();
    void on_click_BTN_ZielSpeichern();
    void removeEntfernungErgebnisWidgets();
    void createEntfernungErgebnisWidgets();
    bool inputMatchesID(std::vector<Ort*>& orte, int idChoice);
    int getIndexOfOrt(int input);
    void on_click_BTN_BinaerImpExp();
    void on_click_BTN_ImportBinaer();
    void on_click_BTN_ExportBinaer();
    void modifyQTableWidget(QTableWidget* tableWidget);
    void createWindowCSVImpExp();
    void on_click_BTN_CSVImpExp();
    void on_click_BTN_ImportCSV();
    void on_click_BTN_ExportCSV();
    void on_click_BTN_Exit();

private:
    Ui::MainWindow *ui;
       std::vector<Ort*>Orte{};
};
#endif // MAINWINDOW_H
