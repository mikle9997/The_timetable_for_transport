#include "dialogaboutaddingstationinroute.h"
#include "ui_dialogaboutaddingstationinroute.h"

DialogAboutAddingStationInRoute::DialogAboutAddingStationInRoute(CoreOfInfoAboutMetro *core,int *index_out_of,QString* name_of_adding_station,QMainWindow *m_window, QWidget *parent) :
    core(core),
    index_out_of(index_out_of),
    name_of_adding_station(name_of_adding_station),
    QDialog(parent),
    ui(new Ui::DialogAboutAddingStationInRoute)
{
    ui->setupUi(this);

    this->setFixedSize(300,200);

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


    this->setWindowTitle("Добавление станции в маршрут");
    QPalette pal;
    pal.setBrush(this->backgroundRole(), Qt::white);
    this->setPalette(pal);

    for(int i = 0; i < core->howManyRoutes(); i++)
    {
        std::stringstream print_int;
        print_int << i + 1;
        ui->comboBox->addItem((print_int.str()).c_str());
    }

    connect(this,SIGNAL(addStationSignal()),m_window,SLOT(addStation()));
}

DialogAboutAddingStationInRoute::~DialogAboutAddingStationInRoute()
{
    delete ui;
}

void DialogAboutAddingStationInRoute::on_comboBox_activated(int index)
{
    *index_out_of = index;
    ui->textEdit->setEnabled(true);
}

void DialogAboutAddingStationInRoute::on_pushButton_clicked()
{
    *name_of_adding_station = ui->textEdit->toPlainText();

    emit addStationSignal();
    close();
}

void DialogAboutAddingStationInRoute::on_textEdit_textChanged()
{
    ui->pushButton->setEnabled(true);
}
