#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QString"
#include "QGraphicsRectItem"
#include "QQueue"
#include "QVector"
#include "QTextStream"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     scene = new QGraphicsScene(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QVector<int> Hsize,startAdd,Hsize2,startAdd2, startAddAlloc,sizeAlloc,sizeDealloc,holenum,wait; QQueue<int> processes;
     int process,pAlloc=0 ,nH, nP;
      QBrush blueBrush(Qt::blue); QBrush yellowBrush(Qt::yellow) ; QPen blackPen(Qt::black);
    QString HolesNum,HolesSizes,StartingAdd,ProcessesNum,ProcessesSizes,Deallocateprocess;

    HolesNum=ui->lineEdit_HolesNum->text();
    HolesSizes=ui->lineEdit_HolesSizes->text();
    StartingAdd=ui->lineEdit_StartingAdd->text();
    ProcessesNum=ui->lineEdit_ProcessesNum->text();
    ProcessesSizes=ui->lineEdit_ProcessesSizes->text();
    Deallocateprocess=ui->lineEdit_dealloc->text();
    nH=HolesNum.split(" ")[0].toInt();
    nP=ProcessesNum.split(" ")[0].toInt();

    QTextStream stream(&HolesSizes);
    while (!stream.atEnd()) {
        int number;
        stream >> number;
        Hsize.append(number); Hsize2.append(number);
    }
    QTextStream stream1(&StartingAdd);
    while (!stream1.atEnd()) {
        int number;
        stream1 >> number;
        startAdd.append(number); startAdd2.append(number);
    }
    for(int i=0;i<nH;i++)
    {
        rect[i]=scene->addRect(0,startAdd[i]/2,220,Hsize[i]/2,blackPen,blueBrush);
    }

    QTextStream stream2(&ProcessesSizes);
    while (!stream2.atEnd()) {
        int number;
        stream2 >> number;
        processes.append(number);
    }
    QTextStream stream3(&Deallocateprocess);
    while (!stream3.atEnd()) {
        int number;
        stream3 >> number;
        sizeDealloc.append(number);
    }

           //allocation as per best fit
    if(ui->radioButton_bestfit->isChecked())
     { scene->clear(); wait.clear(); ui->listWidget->clear();
        for(int i=0;i<nH;i++)
        {
            rect[i]=scene->addRect(0,startAdd[i]/2,220,Hsize[i]/2,blackPen,blueBrush);
        }
        for (int i = 0; i < nP; i++)
            {
                process = processes.front();
               int smallest = -1, j;
                for ( j = 0; j < nH; j++)
                    if ( Hsize[j] >= process)
                    {
                        smallest = j;
                        break;
                    }
                for (; j < nH; j++)
                    if ( Hsize[j] >= process && Hsize[j] < Hsize[smallest])
                        smallest = j;
                if (smallest == -1)
                {
                    processes.push_back(processes.front());
                     wait.push_back(processes.front());
                    processes.pop_front();
                    startAddAlloc.push_back(0);
                    sizeAlloc.push_back(0);
                        holenum.push_back(0);
                        pAlloc += 1;

                }
                else
                {
                    startAddAlloc.push_back(startAdd[smallest]);
                    sizeAlloc.push_back(process);
                    processes.pop_front();
                    startAdd[smallest] = startAdd[smallest] + process;
                    Hsize[smallest] = Hsize[smallest] - process;
                    holenum.push_back(smallest);
                    pAlloc += 1;

                }
            }
        for(int i=0;i<sizeAlloc.size();i++)
        {
            if(sizeAlloc[i]!=0)
            {
                rect[i]=scene->addRect(0, startAddAlloc[i]/2,220,sizeAlloc[i]/2,blackPen,yellowBrush);

            }
        }

        for(int i=0;i<processes.size();i++)
        {
            ui->listWidget->addItem("P"+QString::number(processes[i])+" -> Waits\n");
        }

        for(int i=0;i<sizeDealloc.size();i++)
        {
            for(int j=0;j<sizeAlloc.size();j++)
              {  if(sizeDealloc[i]==sizeAlloc[j])
                {
                    for(int k=0;k<startAddAlloc.size();k++)
                     if(startAddAlloc[k]>startAddAlloc[j] && startAddAlloc[k]< startAdd2[holenum[j]]+Hsize2[holenum[j]])
                          {
                         startAddAlloc[k]-=sizeAlloc[j];
                         startAdd[holenum[j]]-=sizeAlloc[j];
                         Hsize[holenum[j]]+=sizeAlloc[j];
                     }
                    sizeAlloc[j]=0;scene->clear();
                    for(int k=0;k<nH;k++)
                    {
                        rect[k]=scene->addRect(0,startAdd2[k]/2,220,Hsize2[k]/2,blackPen,blueBrush);
                    }
                    for (int k = 0; k < processes.size(); k++)
                        {
                            process = processes.front();
                           int smallest = -1, n;
                            for ( n = 0; n < nH; n++)
                                if ( Hsize[n] >= process)
                                {
                                    smallest = n;
                                    break;
                                }
                            for (; n < nH; n++)
                                if ( Hsize[n] >= process && Hsize[n] < Hsize[smallest])
                                    smallest = n;
                           if(smallest!=-1)
                            {
                                startAddAlloc.push_back(startAdd[smallest]);
                                sizeAlloc.push_back(process);
                                processes.pop_front();
                                holenum.push_back(smallest);
                                pAlloc += 1;

                            }
                           else
                           {
                               processes.push_back(processes.front());
                               processes.pop_front();
                               startAdd[smallest] = startAdd[smallest] + process;
                               Hsize[smallest] = Hsize[smallest] - process;
                               holenum.push_back(smallest);
                               pAlloc += 1;
                           }
                        }
                    for(int k=0;k<sizeAlloc.size();k++)
                    {
                        if(sizeAlloc[k]!=0)
                        {
                            rect[k]=scene->addRect(0, startAddAlloc[k]/2,220,sizeAlloc[k]/2,blackPen,yellowBrush);

                        }
                    }
                    ui->listWidget->clear();
                    for(int k=0;k<processes.size();k++)
                    {
                        ui->listWidget->addItem("P"+QString::number(processes[k])+" -> Waits\n");
                    }
                }
            }
        }
}

    //allocation as per first fit
if(ui->radioButton_firstfit->isChecked())
  {
    scene->clear(); wait.clear(); ui->listWidget->clear();
            for(int i=0;i<nH;i++)
            {
                rect[i]=scene->addRect(0,startAdd[i]/2,220,Hsize[i]/2,blackPen,blueBrush);
            }
    for (int i = 0; i < nP; i++)
     {
         process = processes.front();
        int first=-1, j;
         for ( j = 0; j < nH; j++)
             if ( Hsize[j] >= process)
             {
                 first=j;
                 break;
             }
         if(first!=-1)
             {
                 startAddAlloc.push_back(startAdd[first]);
                 sizeAlloc.push_back(process);
                 processes.pop_front();
                 startAdd[first] = startAdd[first] + process;
                 Hsize[first] = Hsize[first] - process;
                 holenum.push_back(first);
                 pAlloc += 1;

             }

        else
         {
             processes.push_back(processes.front());
              wait.push_back(processes.front());
             processes.pop_front();
             startAddAlloc.push_back(0);
             sizeAlloc.push_back(0);
                 holenum.push_back(0);
                 pAlloc += 1;

         }

     }
 for(int i=0;i<sizeAlloc.size();i++)
 {
     if(sizeAlloc[i]!=0)
     {rect[i]=scene->addRect(0, startAddAlloc[i]/2,220,sizeAlloc[i]/2,blackPen,yellowBrush);}
 }
 for(int i=0;i<wait.size();i++)
 {
     ui->listWidget->addItem("P"+QString::number(wait[i])+" -> Waits\n");
 }
 for(int i=0;i<sizeDealloc.size();i++)
 {
     for(int j=0;j<sizeAlloc.size();j++)
       {  if(sizeDealloc[i]==sizeAlloc[j])
         {
             for(int k=0;k<startAddAlloc.size();k++)
              if(startAddAlloc[k]>startAddAlloc[j] && startAddAlloc[k]< startAdd2[holenum[j]]+Hsize2[holenum[j]])
                   {
                  startAddAlloc[k]-=sizeAlloc[j];
                  startAdd[holenum[j]]-=sizeAlloc[j];
                  Hsize[holenum[j]]+=sizeAlloc[j];
              }
             sizeAlloc[j]=0;scene->clear();
             for(int k=0;k<nH;k++)
             {
                 rect[k]=scene->addRect(0,startAdd2[k]/2,220,Hsize2[k]/2,blackPen,blueBrush);
             }
             for (int k = 0; k < processes.size(); k++)
                 {
                     process = processes.front();
                    int first = -1, n;
                     for ( n = 0; n < nH; n++)
                         if ( Hsize[n] >= process)
                         {
                             first = n;
                             break;
                         }

                    if(first!=-1)
                     {
                         startAddAlloc.push_back(startAdd[first]);
                         sizeAlloc.push_back(process);
                         processes.pop_front();
                         holenum.push_back(first);
                         pAlloc += 1;

                     }
                    else
                    {
                        processes.push_back(processes.front());
                        processes.pop_front();
                        startAdd[first] = startAdd[first] + process;
                        Hsize[first] = Hsize[first] - process;
                        holenum.push_back(first);
                        pAlloc += 1;
                    }
                 }
             for(int k=0;k<sizeAlloc.size();k++)
             {
                 if(sizeAlloc[k]!=0)
                 {
                     rect[k]=scene->addRect(0, startAddAlloc[k]/2,220,sizeAlloc[k]/2,blackPen,yellowBrush);

                 }
             }
             ui->listWidget->clear();
             for(int k=0;k<processes.size();k++)
             {
                 ui->listWidget->addItem("P"+QString::number(processes[k])+" -> Waits\n");
             }
         }
     }
 }
}
//allocation as per worst fit
if(ui->radioButton_worstfit->isChecked())
{
    scene->clear();  wait.clear(); ui->listWidget->clear();
            for(int i=0;i<nH;i++)
            {
                rect[i]=scene->addRect(0,startAdd[i]/2,220,Hsize[i]/2,blackPen,blueBrush);
            }
    for (int i = 0; i < nP; i++)
 {
     process = processes.front();
    int largest=-1, j;
     for ( j = 0; j < nH; j++)
         if ( Hsize[j] >= process)
         {
             largest=j;
             break;
         }
     for (; j < nH; j++)
         if ( Hsize[j] >= process && Hsize[j] > Hsize[largest])
             largest = j;
     if(largest!=-1)
         {
             startAddAlloc.push_back(startAdd[largest]);
             sizeAlloc.push_back(process);
             processes.pop_front();
             startAdd[largest] = startAdd[largest] + process;
             Hsize[largest] = Hsize[largest] - process;
             holenum.push_back(largest);
             pAlloc += 1;

         }

    else
     {
         processes.push_back(processes.front());
          wait.push_back(processes.front());
         processes.pop_front();
         startAddAlloc.push_back(0);
         sizeAlloc.push_back(0);
             holenum.push_back(0);
             pAlloc += 1;

     }

 }
for(int i=0;i<sizeAlloc.size();i++)
{
 if(sizeAlloc[i]!=0)
 {rect[i]=scene->addRect(0, startAddAlloc[i]/2,220,sizeAlloc[i]/2,blackPen,yellowBrush);}
}
for(int i=0;i<wait.size();i++)
{
    ui->listWidget->addItem("P"+QString::number(wait[i])+" -> Waits\n");
}
for(int i=0;i<sizeDealloc.size();i++)
{
    for(int j=0;j<sizeAlloc.size();j++)
      {  if(sizeDealloc[i]==sizeAlloc[j])
        {
            for(int k=0;k<startAddAlloc.size();k++)
             if(startAddAlloc[k]>startAddAlloc[j] && startAddAlloc[k]< startAdd2[holenum[j]]+Hsize2[holenum[j]])
                  {
                 startAddAlloc[k]-=sizeAlloc[j];
                 startAdd[holenum[j]]-=sizeAlloc[j];
                 Hsize[holenum[j]]+=sizeAlloc[j];
             }
            sizeAlloc[j]=0;scene->clear();
            for(int k=0;k<nH;k++)
            {
                rect[k]=scene->addRect(0,startAdd2[k]/2,220,Hsize2[k]/2,blackPen,blueBrush);
            }
           /* for (int k = 0; k < processes.size(); k++)
                {
                    process = processes.front();
                   int largest = -1, n;
                    for ( n = 0; n < nH; n++)
                        if ( Hsize[n] >= process)
                        {
                            largest = n;
                            break;
                        }
                    for (; n < nH; n++)
                        if (  Hsize[n] >= process && Hsize[n] > Hsize[largest])
                            largest = n;
                   if(largest!=-1)
                    {
                        startAddAlloc.push_back(startAdd[largest]);
                        sizeAlloc.push_back(process);
                        processes.pop_front();
                        holenum.push_back(largest);
                        pAlloc += 1;

                    }
                   else
                   {
                       processes.push_back(processes.front());
                       processes.pop_front();
                       startAdd[largest] = startAdd[largest] + process;
                       Hsize[largest] = Hsize[largest] - process;
                       holenum.push_back(largest);
                       pAlloc += 1;
                   }
                }*/
            for(int k=0;k<sizeAlloc.size();k++)
            {
                if(sizeAlloc[k]!=0)
                {
                    rect[k]=scene->addRect(0, startAddAlloc[k]/2,220,sizeAlloc[k]/2,blackPen,yellowBrush);

                }
            }
            ui->listWidget->clear();
            for(int k=0;k<processes.size();k++)
            {
                ui->listWidget->addItem("P"+QString::number(processes[k])+" -> Waits\n");
            }
        }
    }
}
}

 ui->graphicsView->setScene(scene);

}
