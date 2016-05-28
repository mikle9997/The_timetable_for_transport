#include "dialogaboutaddinginfoaboutstation.h"
#include "ui_dialogaboutaddinginfoaboutstation.h"

DialogAboutAddingInfoAboutStation::DialogAboutAddingInfoAboutStation(CoreOfInfoAboutMetro *core, int *number_of_the_route, int *number_of_the_station, QString *information_about_station, QMainWindow *m_window, QWidget *parent) :
    core(core),
    number_of_the_route(number_of_the_route),
    number_of_the_station(number_of_the_station),
    information_about_station(information_about_station),
    QDialog(parent),
    ui(new Ui::DialogAboutAddingInfoAboutStation)
{
    ui->setupUi(this);

    ui->pushButton->setStyleSheet("QPushButton "
                                  "{"
                                  "background: #fde910;"
                                  "border: 1px solid 000000;"
                                  "border-radius: 9px;"
                                  "}"
                                  "QPushButton:hover "
                                  "{"
                                  "background: #ffd919;"
                                  "}"
                                  "QPushButton:pressed "
                                  "{"
                                  "background: #e6bf00;"
                                  "}");
    ui->comboBox->setStyleSheet("QComboBox "
                                "{"
                                "background: #fced3f;"
                                "border-radius: 1px;"
                                "}"
                                "QComboBox:editable"
                                "{"
                                "background: white;"
                                "}"
                                "QComboBox QAbstractItemView {"
                                "background: #fcf172;"
                                "selection-color: black;"
                                "selection-background-color: #fced3f;"
                                "}");
    ui->comboBox_2->setStyleSheet("QComboBox "
                                  "{"
                                  "background: #fced3f;"
                                  "border-radius: 1px;"
                                  "}"
                                  "QComboBox:editable"
                                  "{"
                                  "background: white;"
                                  "}"
                                  "QComboBox QAbstractItemView {"
                                  "background: #fcf172;"
                                  "selection-color: black;"
                                  "selection-background-color: #fced3f;"
                                  "}");

    this->setWindowTitle("Добавление информации о станции");
    QPalette pal;
    pal.setBrush(this->backgroundRole(), Qt::white);
    this->setPalette(pal);

    for(int i = 0; i < core->howManyRoutes(); i++)
    {
        std::stringstream print_int;
        print_int << i + 1;
        ui->comboBox->addItem((print_int.str()).c_str());
    }

    connect(this,SIGNAL(addInformationAboutStation()),m_window,SLOT(addInformationAboutStation()));
}

DialogAboutAddingInfoAboutStation::~DialogAboutAddingInfoAboutStation()
{
    delete ui;
}

void DialogAboutAddingInfoAboutStation::on_comboBox_activated(int index)
{
    *number_of_the_route = index;

    ui->comboBox_2->clear();
    ui->comboBox_2->setEnabled(true);
    std::vector<std::string> route = core->getRoute(index + 1);
    for(unsigned int i = 0; i < route.size(); i++)
    {
        ui->comboBox_2->addItem(route[i].c_str());
    }
}

void DialogAboutAddingInfoAboutStation::on_comboBox_2_activated(int index)
{
    *number_of_the_station = index;

    ui->textEdit->setEnabled(true);
}

void DialogAboutAddingInfoAboutStation::on_pushButton_clicked()
{
    *information_about_station = ui->textEdit->toPlainText();

    emit addInformationAboutStation();
    close();
}

void DialogAboutAddingInfoAboutStation::on_textEdit_textChanged()
{
    ui->pushButton->setEnabled(true);
}
