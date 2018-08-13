#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::readTableForm()
{
    row = ui->tableWidget->rowCount();

    x.resize(row);
    y.resize(row);

    for(int i=0;i<row;i++)
    {
        x[i] = ui->tableWidget->item(i,0)->text().toInt();
        y[i] = ui->tableWidget->item(i,1)->text().toInt();
    }
}

void MainWindow::MiniMax()
{
    //// код
    // шаг1
    QVector<qreal> vector(row);
    for(int i=0;i<row;i++)
        vector[i] = qMin(x[i],y[i]);

    // шаг2
    qreal max = *std::max_element(vector.begin(),vector.end());
    int count = std::count(vector.begin(),vector.end(),max);
    QVector<int> answerIndexes;
    for(int i=0;i<row;i++)
        if(max==vector[i])
            answerIndexes.append(i);

    //// формирование отчета
    QString otchet;
    otchet.append("<style>h3{color:red;}</style>");
    // шаг1
    otchet.append("<h3>Шаг 1: Выбираем минимальное значение в каждой строке.</h3>");
    otchet.append("Полученный вектор:<br>");
    foreach(auto n,vector)
        otchet += QString("%1<br>").arg(n);

    // шаг2
    otchet.append("<h3>Шаг2: находим максимальный элемент в полученом векторе</h3>");
    otchet = otchet.append("Оптимальное решение:<b>%1</b><br>Количество оптимальных решений:<b>%2</b><br>").arg(max).arg(count);
    otchet.append("Индексы оптимальных решений:");
    foreach(auto index,answerIndexes)
        otchet += QString(" <b>E%1</b>").arg(index);

    // вывод отчета
    ui->textBrowser->setHtml(otchet);

    //// Геометрический метод расчета
    // очищаем график
    ui->customPlot->clearItems();
    // немного теории: угол 45 градусов - x[i] == y[i]
    qreal graphAnswer = 0;
    for(int i=0;i<row;i++)
        // 45 градусов?
        if( x[i] == y[i] )
            // max?
            if( graphAnswer < x[i] )
                graphAnswer = x[i]; // ( x[i] == y[i] )

    // отчет
    QString graphOtchet = QString("{%1,%1}").arg(graphAnswer);
    ui->lineEdit_2->setText( graphOtchet );

    //// рисуем график
    // находим максимальное число в массиве для определения размеров графика
    auto graphWidth   = *std::max_element(x.begin(),x.end()) + 1;
    auto graphHeight  = *std::max_element(y.begin(),y.end()) + 1;
    auto graphSize = qMax(graphWidth,graphHeight);

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,y);
    ui->customPlot->xAxis->setRange(0,graphSize); // +1 для видимости графика
    ui->customPlot->yAxis->setRange(0,graphSize);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    // рисование доттед линий
    QPen pen;
    pen.setStyle(Qt::DashLine);

    QCPItemLine *line1 = new QCPItemLine(ui->customPlot);
    line1->start->setCoords(0,graphAnswer);
    line1->end->setCoords(graphAnswer,graphAnswer);
    line1->setPen(pen);
    ui->customPlot->addItem(line1);

    QCPItemLine *line2 = new QCPItemLine(ui->customPlot);
    line2->start->setCoords(graphAnswer,0);
    line2->end->setCoords(graphAnswer,graphAnswer);
    line2->setPen(pen);
    ui->customPlot->addItem(line2);

    // рисование жирных линий
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);

    QCPItemLine *line3 = new QCPItemLine(ui->customPlot);
    line3->start->setCoords(graphAnswer,graphAnswer);
    line3->end->setCoords(9999,graphAnswer);
    line3->setPen(pen);
    ui->customPlot->addItem(line3);

    QCPItemLine *line4 = new QCPItemLine(ui->customPlot);
    line4->start->setCoords(graphAnswer,graphAnswer);
    line4->end->setCoords(graphAnswer,9999);
    line4->setPen(pen);
    ui->customPlot->addItem(line4);

    // линия под углом 45 градусов
    QCPItemStraightLine* line5 = new QCPItemStraightLine(ui->customPlot);
    line5->point1->setCoords(0,0);
    line5->point2->setCoords(1,1);
    ui->customPlot->addItem(line5);

    //ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot->replot();
}

void MainWindow::proizved()
{
    //// код
    // шаг1
    QVector<qreal> vector(row);
    for(int i=0;i<row;i++)
        vector[i]=x[i]*y[i];

    // шаг2
    qreal max = *std::max_element(vector.begin(),vector.end());
    int count=std::count(vector.begin(),vector.end(),max);
    QVector<int> answerIndexes;
    for(int i=0;i<row;i++)
        if(max==vector[i])
            answerIndexes.append(i);

    //// формирование отчета
    QString otchet;
    otchet.append("<style>h3{color:red;}</style>");

    // шаг1
    otchet.append("<h3>Шаг1: перемножаем эелементы столбцов</h3>");
    otchet.append("Полученный вектор:<br>");
    foreach(auto n,vector)
        otchet += QString("%1<br>").arg(n);

    // шаг2
    otchet.append("<h3>Шаг2: находим максимальный элемент в полученом векторе</h3>");
    otchet += QString("Оптимальное решение:<b>%1</b><br>Количество оптимальных решений:<b>%2</b><br>").arg(max).arg(count);
    otchet.append("Индексы оптимальных решений:");
    foreach(auto index,answerIndexes)
        otchet += QString(" <b>E%1</b>").arg(index);

    // вывод отчета
    ui->textBrowser_2->setHtml(otchet);

    //// Графический метод
    // Шаг1. находим радиус вектора исходя из того, что e1*e2 (max) это длина дуги(четверти круга)
    qreal rad = (max * 4) / ( 2 * M_PI );

    // находим максимальное число в массиве для определения крайней точки для поиска оптимального решения
    auto graphWidth   = *std::max_element(x.begin(),x.end());
    auto graphHeight  = *std::max_element(y.begin(),y.end());
    auto maxElement = qMax(graphWidth,graphHeight);

    // Шаг2. Методом перебора находим оптимальную точку (начинаем искать с конца 45 градусной дуги)
    QVector<qreal> optimalGraph(2); // x y
    qreal coordArc; ////!!!
    for(qreal n=(maxElement+rad);n>0;n-=0.01)
    {
        // последовательно находим длины отрезков от центра окружности до точек входящих в окружность и вычисляем максимальную точку
        qreal minLength=INFINITE;
        for(int i=0;i<row;i++)
        {
            // находим точку с минимальным расстоянием до центра круга
            qreal lengthBetween = sqrt(pow(n-x[i],2)+pow(n-y[i],2)); // длина отрезка между 2-мя точками
            if(lengthBetween<rad)
            {
                if(minLength>lengthBetween)
                {
                    minLength = lengthBetween;
                    optimalGraph[0] = x[i];
                    optimalGraph[1] = y[i];
                    coordArc = n; ////!!!
                }
            }
        }

        // если точки найдены, то заканчиваем цикл
        if ( optimalGraph[0] != 0 && optimalGraph[1] != 0 )
            break;
    }

    // отчет
    ui->lineEdit->setText( QString("{%1,%2}").arg(optimalGraph[0]).arg(optimalGraph[1]) );

    //// Рисуем график
    // очищаем график
    ui->customPlot_2->clearItems();
    // дуга оптимального решения (почти дуга)
    QCPItemEllipse* arc = new QCPItemEllipse(ui->customPlot_2);
    arc->topLeft->setCoords(coordArc-rad,coordArc+rad);
    arc->bottomRight->setCoords(coordArc+rad,coordArc-rad);
    ui->customPlot_2->addItem(arc);

    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(0)->setData(x,y);
    ui->customPlot_2->xAxis->setRange(0,maxElement+1); // +1 для видимости графика
    ui->customPlot_2->yAxis->setRange(0,maxElement+1);
    ui->customPlot_2->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));

    // рисование доттед линий
    QPen pen;
    pen.setStyle(Qt::DashLine);

    QCPItemLine *line1 = new QCPItemLine(ui->customPlot_2);
    line1->start->setCoords(0,optimalGraph[1]);
    line1->end->setCoords(optimalGraph[0],optimalGraph[1]);
    line1->setPen(pen);
    ui->customPlot_2->addItem(line1);

    QCPItemLine *line2 = new QCPItemLine(ui->customPlot_2);
    line2->start->setCoords(optimalGraph[0],0);
    line2->end->setCoords(optimalGraph[0],optimalGraph[1]);
    line2->setPen(pen);
    ui->customPlot_2->addItem(line2);

    // линия под углом 45 градусов
    QCPItemStraightLine* line5 = new QCPItemStraightLine(ui->customPlot_2);
    line5->point1->setCoords(0,0);
    line5->point2->setCoords(1,1);
    ui->customPlot_2->addItem(line5);

    //ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    ui->customPlot_2->replot();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButton_clicked()
{
    readTableForm();

    // последовательно вычисляем методы
    MiniMax();
    proizved();
}
