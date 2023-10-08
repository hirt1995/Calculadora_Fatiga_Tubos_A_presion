#include "calfatiga.h"
#include "ui_calfatiga.h"
#include <math.h>

CalFatiga::CalFatiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalFatiga)
{
    ui->setupUi(this);
}

CalFatiga::~CalFatiga()
{
    delete ui;
}

void CalFatiga::on_pusButton_clicked()
{
    //capturamos variables de la interfaz
    QString Sultimo = ui->Sut->text();// captura el valor en qstring de la ventana de la interfaz.
    QString Syield = ui->Esfulti->text();// captura el valor en qstring de la ventana de la interfaz.
    QString LoadMax = ui->Cmax->text();
    QString LoadMin = ui->Cmin->text();
   // QString Elasticidad = ui->ModE->text();// captura el valor en qstring de la ventana de la interfaz.
    //QString Iner = ui->Inercia->text();// captura el valor en qstring de la ventana de la interfaz.
    QString dinter = ui->Diain->text();// captura el valor en qstring de la ventana de la interfaz.
    QString Dext = ui->Diaex->text();// captura el valor en qstring de la ventana de la interfaz.
    //QString Longi = ui->LonTub->text();// captura el valor en qstring de la ventana de la interfaz.
    QString Ciclos = ui->Ciclaje->text();// captura el valor en qstring de la ventana de la interfaz.
    QString kgeometrico = ui->Kgeome->text();// captura el valor en qstring de la ventana de la interfaz.
    QString kfluctuante = ui->Kfluc->text();// captura el valor en qstring de la ventana de la interfaz.
    QString Confiabilidad = ui->confia->text();//
    QString Seprim = ui->Sepri->text();//
    QString Radinteres = ui->Rinte->text();//
    QString Temp = ui->Tc->text();//
    //definimos variables operativas
    double Sulti = Sultimo.toDouble(); //contiene el valor ingresado del usuario
    double Syie = Syield.toDouble(); //contiene el valor ingresado del usuario
    double LoaMax = LoadMax.toDouble();
    double LoaMin = LoadMin.toDouble();
   // double Elastic = Elasticidad.toDouble(); //contiene el valor ingresado del usuario
    //double Miner = Iner.toDouble(); //contiene el valor ingresado del usuario
    double dinte = dinter.toDouble(); //contiene el valor ingresado del usuario
    double Dexte = Dext.toDouble(); //contiene el valor ingresado del usuario
    double Cicl = Ciclos.toDouble(); //contiene el valor ingresado del usuario
    double Conf = Confiabilidad.toDouble();
    double Seprima = Seprim.toDouble();
    double RadioInteres = Radinteres.toDouble();
    double T = Temp.toDouble();


    //variables complementarias
    double Pa =0;
    double Pm = 0;
    //sigmas maximos nominales
    double SigmaTmax=0;
    double SigmaRmax=0;
    double SigmaAxmax=0;
    //sigmas minimos nominales
    double SigmaTmin=0;
    double SigmaRmin=0;
    double SigmaAxmin=0;
    //alternantes nominales
    double SigmaTa=0;
    double SigmaRa=0;
    double SigmaAxa=0;
    //medios nominales
    double SigmaTm=0;
    double SigmaRm=0;
    double SigmaAxm=0;
    //maximos globales
    double SigmaTG=0;
    double SigmaRG=0;
    double SigmaAxG=0;
    //minimos globales
    double SigmaTGmin=0;
    double SigmaRGmin=0;
    double SigmaAxGmin=0;
    double SigmaG=0;
    double SigmaGmin=0;
    //sigma medio
    double SigmaM=0;
    //alternantes globaes
    double SigmaTaG=0;
    double SigmaRaG=0;
    double SigmaAxaG=0;
    //medios globales
    double SigmaTmG=0;
    double SigmaRmG=0;
    double SigmaAxmG=0;
    //Von misses alternate y medio
    double SigmaVa=0;
    double SigmaVm=0;
    //concentradores
    double kf= kfluctuante.toDouble();
    double kt = kgeometrico.toDouble();
    double kfm=0;
    //Factor de carga
    double Ccarga=0;
    //factor de tamaño
    double Ctama=0;
    //factor de superficie
    double A=0;
    double b=0;
    double Csuper=0;
    //factor de confiabilidad
    double Cconf=0;
    //factor de temperatura
    double Ctemp=0;
    //limite de resistencia a la fatiga corregido
    double Se=0;
    //factor de Seguridad
    double FSone=0;
    double FStwo=0;
    double FSthree=0;
    double SigMas=0;
    double SigAs=0;
    double ZS=0;
    double OZ=0;
    double FSfour=0;



// PARA ESFUERZOS MULTIAXIALES FLUCTUANTES

    if(ui->radioFluct->isChecked())
    {
        Pa= ((LoaMax - LoaMin)/2);
        Pm= ((LoaMax + LoaMin)/2);
         //sigmas máximos nominales
        SigmaTmax=((((((pow(dinte/2,2))*LoaMax)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1+((pow(Dexte/2,2))/(pow(RadioInteres,2))))))*(0.1));
        SigmaRmax=((((((pow(dinte/2,2))*LoaMax)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1-((pow(Dexte/2,2))/(pow(RadioInteres,2))))))*(0.1));
        SigmaAxmax=(((pow(dinte/2,2))*LoaMax)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(0.1);
        //sigmas mínimos nominales
        SigmaTmin=(((((pow(dinte/2,2))*LoaMin)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1+((pow(Dexte/2,2))/(pow(RadioInteres,2)))))*(0.1));
        SigmaRmin=(((((pow(dinte/2,2))*LoaMin)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1-((pow(Dexte/2,2))/(pow(RadioInteres,2)))))*(0.1));
        SigmaAxmin=((((pow(dinte/2,2))*LoaMin)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(0.1));
        //sigmas alternates
        SigmaTa=(((((pow(dinte/2,2))*Pa)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1+((pow(Dexte/2,2))/(pow(RadioInteres,2)))))*(0.1));
        SigmaRa=(((((pow(dinte/2,2))*Pa)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1-((pow(Dexte/2,2))/(pow(RadioInteres,2)))))*(0.1));
        SigmaAxa=((((pow(dinte/2,2))*Pa)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(0.1));
        //sigmas medios
        SigmaTm=(((((pow(dinte/2,2))*Pm)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1+((pow(Dexte/2,2))/(pow(RadioInteres,2)))))*(0.1));
        SigmaRm=(((((pow(dinte/2,2))*Pm)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1-((pow(Dexte/2,2))/(pow(RadioInteres,2)))))*(0.1));
        SigmaAxm=((((pow(dinte/2,2))*Pm)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(0.1));

        //vamos a cacular los sigma máximo global.
        SigmaTG= kf*SigmaTmax;
        SigmaRG= kf*SigmaRmax;
        SigmaAxG= kf*SigmaAxmax;
        SigmaG= sqrt(pow(SigmaTG,2)+pow(SigmaRG,2)+pow(SigmaAxG,2));
        //sigmas minimos globales
        SigmaTGmin= kf*SigmaTmin;
        SigmaRGmin= kf*SigmaRmin;
        SigmaAxGmin= kf*SigmaAxmin;
        SigmaGmin= sqrt(pow(SigmaTGmin,2)+pow(SigmaRGmin,2)+pow(SigmaAxGmin,2));
        //calculamos sigma medio
        SigmaM=sqrt(pow(SigmaTm,2)+pow(SigmaRm,2)+pow(SigmaAxm,2));

        if(SigmaG < Syie)
        {
            kfm=kf;
        }
        else {
            kfm= ((Syie-(kf*SigmaGmin))/SigmaM);
        }
        //calculamos los sigmas alternantes globales
        SigmaTaG= kfm*SigmaTa;
        SigmaRaG=kfm*SigmaRa;
        SigmaAxaG=kfm*SigmaAxa;
        //sigmas medios globales
        SigmaTmG= kfm*SigmaTm;
        SigmaRmG=kfm*SigmaRm;
        SigmaAxmG=kfm*SigmaAxm;
        //Von misses alternate y medio
        SigmaVa=sqrt((pow((SigmaAxaG-SigmaTaG),2)+pow((SigmaTaG-SigmaRaG),2)+pow((SigmaRaG-SigmaAxaG),2))/2);
        SigmaVm=sqrt((pow((SigmaAxmG-SigmaTmG),2)+pow((SigmaTmG-SigmaRmG),2)+pow((SigmaRmG-SigmaAxmG),2))/2);

        //Factor de carga
        if(ui->radioFlexion->isChecked())
        {
            Ccarga= 1;
        }else {
            if(ui->radioTraccion->isChecked())
            {
                Ccarga=0.7;
            }else {
                if(ui->radioTorcion->isChecked())
                {
                    Ccarga=0.577;
                }
            }
        }

        //Factor de tamaño con mm
        if(Dexte < 8)
        {
            Ctama= 1;
        }else {
            if(Dexte >8 && Dexte < 250)
            {
                Ctama=(1.189*pow(Dexte,(-0.097)));
            }else {
                if(Dexte > 250)
                {
                    Ctama=0.6;
                }
            }
        }

        //Factor de superficie
        if(ui->radioEsmer->isChecked())
        {
            A=1.58;
            b=(-0.085);
            Csuper= A*((pow(Sulti,b)));
        }else {
            if(ui->radiomaqui->isChecked())
            {
                A=4.51;
                b=(-0.265);
                Csuper= (A*(pow(Sulti,b)));
            }else {
                if(ui->radioRollCal->isChecked())
                {
                    A=57.7;
                    b=(-0.718);
                    Csuper= A*(pow(Sulti,b));
                }else {
                    if(ui->radioForja->isChecked())
                        {
                            A=272;
                            b=(-0.995);
                            Csuper= A*(pow(Sulti,b));
                        }
                   }
            }
        }

        //factor de confiabilidad
        if(Conf==50)
        {
            Cconf=1;
        }else if(Conf==90)
        {
            Cconf=0.897;
        }else if(Conf==95){
            Cconf=0.868;
        }else if(Conf==99){
            Cconf=0.814;
        }else if(Conf==99.9){
            Cconf=0.753;
        }
        //factor de temperatura
        if(T<=450)
        {
            Ctemp=1;
        }else if(T > 450 && T <= 550 )
        {
            Ctemp= 1-(0.0058*(T-450));
        }
        //limite de resistencia a la fatiga corregido
        Se=Cconf*Ctemp*Csuper*Ccarga*Ctama*Seprima;
        //Factores de seguridad
        FSone=((Syie)/(SigmaVm))*(1-((SigmaVa/Syie)));
        FStwo=(Se/SigmaVa)*(1-(SigmaVm/Sulti));
        FSthree=(((Se*Sulti))/((SigmaVa*Sulti)+(SigmaVm*Se)));
        SigMas=(Sulti*(pow(Se,2)-(Se*SigmaVa)+(Sulti*SigmaVm)))/(pow(Se,2)+pow(Sulti,2));
        SigAs=((-Se/Sulti)*SigMas)+Se;
        ZS=sqrt(pow((SigmaVm-SigMas),2)+pow((SigmaVa-SigAs),2));
        OZ=sqrt(pow(SigmaVa,2)+pow(SigmaVm,2));
        FSfour=(OZ+ZS)/OZ;

        //varibales iniciales
        ui->listWidget->addItem("VARIABLES INICIALES: ");
        ui->listWidget->addItem("Sut: "+QString::number(Sulti));
        ui->listWidget->addItem("Sy: "+QString::number(Syie));
        ui->listWidget->addItem("Carga Máxima: "+QString::number(LoaMax));
        ui->listWidget->addItem("Carga Mínima: "+QString::number(LoaMin));
        //ui->listWidget->addItem("Modulo Elástico: "+QString::number(Elastic));
        ui->listWidget->addItem("Diámetro interno: "+QString::number(dinte));
        ui->listWidget->addItem("Diámetro externo: "+QString::number(Dexte));
        ui->listWidget->addItem("Ciclaje: "+QString::number(Cicl));
        ui->listWidget->addItem("Confiabilidad: "+QString::number(Conf));
        ui->listWidget->addItem("Radio del punto: "+QString::number(RadioInteres)+"\n");
        //variables calculadas
        ui->listWidget->addItem(("VARIABLES CALCULADAS: "));
        ui->listWidget->addItem("Carga Alternante: "+QString::number(Pa));
        ui->listWidget->addItem("Carga Media: "+QString::number(Pm)+"\n");
        //esfuerzos maximos y minimos nominales
        ui->listWidget->addItem(("ESFUERZOS MAXIMOS Y MINIMOS NOMINALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial Máximo: "+QString::number(SigmaTmax));
        ui->listWidget->addItem("Esfuerzo Radial Máximo: "+QString::number(SigmaRmax));
        ui->listWidget->addItem("Esfuerzo Axial Máximo: "+QString::number(SigmaAxmax));
        ui->listWidget->addItem("Esfuerzo Tangencial Mínimo: "+QString::number(SigmaTmin));
        ui->listWidget->addItem("Esfuerzo Radial Mínimo: "+QString::number(SigmaRmin));
        ui->listWidget->addItem("Esfuerzo Axial Mínimo: "+QString::number(SigmaAxmin)+"\n");
        //esfuerzos alternantes nominales
        ui->listWidget->addItem(("ESFUERZOS ALTERNANTES NOMINALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial Alternante: "+QString::number(SigmaTa));
        ui->listWidget->addItem("Esfuerzo Radial Alternante: "+QString::number(SigmaRa));
        ui->listWidget->addItem("Esfuerzo Axial Alternante: "+QString::number(SigmaAxa)+"\n");
        //esfuerzos alternantes medios nominales
        ui->listWidget->addItem(("ESFUERZOS ALTERNANTES MEDIOS NOMINALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial medio: "+QString::number(SigmaTm));
        ui->listWidget->addItem("Esfuerzo Radial medio: "+QString::number(SigmaRm));
        ui->listWidget->addItem("Esfuerzo Axial medio: "+QString::number(SigmaAxm)+"\n");
        //maximos globales
        ui->listWidget->addItem(("MÁXIMOS GLOBALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial Global: "+QString::number(SigmaTG));
        ui->listWidget->addItem("Esfuerzo Radial Global: "+QString::number(SigmaRG));
        ui->listWidget->addItem("Esfuerzo Axial Global: "+QString::number(SigmaAxG)+"\n");
        //MINIMOS globales
        ui->listWidget->addItem(("MÍNIMOS GLOBALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial Global Min: "+QString::number(SigmaTGmin));
        ui->listWidget->addItem("Esfuerzo Radial Global Min: "+QString::number(SigmaRGmin));
        ui->listWidget->addItem("Esfuerzo Axial Global Min: "+QString::number(SigmaAxGmin));
        ui->listWidget->addItem("Esfuerzo Global: "+QString::number(SigmaG));
        ui->listWidget->addItem("Esfuerzo Global Min: "+QString::number(SigmaGmin)+"\n");
        //sigma medio
        ui->listWidget->addItem(("SIGMA MEDIO: "));
        ui->listWidget->addItem("Esfuerzo Global Medio: "+QString::number(SigmaM)+"\n");
        //alternantes globales
        ui->listWidget->addItem(("ALTERNANTES GLOBALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial AlGlobal : "+QString::number(SigmaTaG));
        ui->listWidget->addItem("Esfuerzo Radial AlGlobal: "+QString::number(SigmaRaG));
        ui->listWidget->addItem("Esfuerzo Axial AlGlobal: "+QString::number(SigmaAxaG)+"\n");
        //medio globales
        ui->listWidget->addItem(("MEDIOS GLOBALES: "));
        ui->listWidget->addItem("Esfuerzo Tangencial MEGlobal : "+QString::number(SigmaTmG));
        ui->listWidget->addItem("Esfuerzo Radial MEGlobal: "+QString::number(SigmaRmG));
        ui->listWidget->addItem("Esfuerzo Axial MEGlobal: "+QString::number(SigmaAxmG)+"\n");
        //Von misses alternante y medio
        ui->listWidget->addItem(("VON MISSES ALTERNANTE Y MEDIO: "));
        ui->listWidget->addItem("Von Misses Alternante: "+QString::number(SigmaVa));
        ui->listWidget->addItem("Von Misses Medio: "+QString::number(SigmaVm)+"\n");
        //concentradores de esfuerzo
        ui->listWidget->addItem(("CONCENTRADORES DE ESFUERZOS: "));
        ui->listWidget->addItem("Kf: "+QString::number(kf));
        ui->listWidget->addItem("Kfm: "+QString::number(kfm));
        ui->listWidget->addItem("Kt: "+QString::number(kt)+"\n");
        //Factores C111
        ui->listWidget->addItem(("FACTORES C: "));
        ui->listWidget->addItem("Factor de Carga: "+QString::number(Ccarga));
        ui->listWidget->addItem("Factor de Tamaño: "+QString::number(Ctama));
        ui->listWidget->addItem("Factor de Superficie: "+QString::number(Csuper));
        ui->listWidget->addItem("Factor de Confiabilidad: "+QString::number(Cconf));
        ui->listWidget->addItem("Factor de Temperatura: "+QString::number(Ctemp)+"\n");
        //limite de resistencia a la fatiga corregido.
        ui->listWidget->addItem(("LIMITE DE RESISTENCIA A LA FATIGA: "));
        ui->listWidget->addItem("Se Corregido: "+QString::number(Se)+"\n");
        //Variables para calcular FS
        ui->listWidget->addItem(("VARIABLES PARA CALCULAR FS: "));
        ui->listWidget->addItem("Sigma M@S: "+QString::number(SigMas));
        ui->listWidget->addItem("Sigma a@s: "+QString::number(SigAs));
        ui->listWidget->addItem("ZS: "+QString::number(ZS));
        ui->listWidget->addItem("OZ: "+QString::number(OZ)+"\n");
        //Se del material y Se corregido
        ui->listWidget->addItem(("Se DEL MATERIA & Se CORREGIDO: "));
        ui->listWidget->addItem("Se del material: "+QString::number(Seprima));
        ui->listWidget->addItem("Se Corregido: "+QString::number(Se)+"\n");
        //factores de seguridad
        ui->listWidget->addItem(("FACTORES DE SEGURIDAD: "));
        ui->listWidget->addItem("Factor de seguridad 1: "+QString::number(FSone));
        ui->listWidget->addItem("Factor de seguridad 2: "+QString::number(FStwo));
        ui->listWidget->addItem("Factor de seguridad 3: "+QString::number(FSthree));
        ui->listWidget->addItem("Factor de seguridad 4: "+QString::number(FSfour));

        ui->listWidget->addItem("-------------------------------------------""\n");

}
    // PARA ESFUERZOS MULTIAXIALES TOTALMENTE INVERTIDOS
    else
    {
        if(ui->radioInver->isChecked())
        {
            double Sigma1=0;
            double Sigma2=0;
            double Sigma3=0;
            double SigmaTmaxup=0;
            double SigmaRmaxup=0;
            double SigmaAxmaxup=0;

             //sigmas máximos nominales
            SigmaTmax=((((((pow(dinte/2,2))*LoaMax)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1+((pow(Dexte/2,2))/(pow(RadioInteres,2))))))*(0.1));
            SigmaRmax=((((((pow(dinte/2,2))*LoaMax)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(1-((pow(Dexte/2,2))/(pow(RadioInteres,2))))))*(0.1));
            SigmaAxmax=(((pow(dinte/2,2))*LoaMax)/(((pow((Dexte/2),2))-(pow((dinte/2),2)))))*(0.1);

            SigmaTmaxup=kf*SigmaTmax;
            SigmaRmaxup=kf*SigmaRmax;
            SigmaAxmaxup=kf*SigmaAxmax;

            if (SigmaTmaxup > SigmaRmaxup && SigmaTmaxup > SigmaAxmaxup)
            {
                Sigma1= SigmaTmaxup;
            }else if (SigmaRmaxup > SigmaAxmaxup){
                Sigma1= SigmaRmaxup;
            }else {
                Sigma1= SigmaAxmaxup;
            }

            if (SigmaTmaxup < SigmaRmaxup && SigmaTmaxup < SigmaAxmaxup){
                Sigma3= SigmaTmaxup;
            }else if (SigmaRmaxup < SigmaAxmaxup){
                Sigma3= SigmaRmaxup;
            }else {
                Sigma3= SigmaAxmaxup;
            }

            if (SigmaTmaxup > SigmaRmaxup && SigmaTmaxup < SigmaAxmaxup){
                Sigma2= SigmaTmax;
            }else if (SigmaRmaxup > SigmaTmaxup && SigmaRmaxup < SigmaAxmaxup){
                Sigma2= SigmaRmaxup;
            }else{
                Sigma2= SigmaAxmaxup;
            }




            //Von misses
            SigmaVa=sqrt(pow(Sigma1,2)+pow(Sigma2,2)+pow(Sigma3,2)-(Sigma1*Sigma2)-(Sigma2*Sigma3)-(Sigma3*Sigma1));


            //Factor de carga
            if(ui->radioFlexion->isChecked())
            {
                Ccarga= 1;
            }else {
                if(ui->radioTraccion->isChecked())
                {
                    Ccarga=0.7;
                }else {
                    if(ui->radioTorcion->isChecked())
                    {
                        Ccarga=0.577;
                    }
                }
            }

            //Factor de tamaño con mm
            if(Dexte < 8)
            {
                Ctama= 1;
            }else {
                if(Dexte >8 && Dexte < 250)
                {
                    Ctama=(1.189*pow(Dexte,(-0.097)));
                }else {
                    if(Dexte > 250)
                    {
                        Ctama=0.6;
                    }
                }
            }

            //Factor de superficie
            if(ui->radioEsmer->isChecked())
            {
                A=1.58;
                b=(-0.085);
                Csuper= A*((pow(Sulti,b)));
            }else {
                if(ui->radiomaqui->isChecked())
                {
                    A=4.51;
                    b=(-0.265);
                    Csuper= (A*(pow(Sulti,b)));
                }else {
                    if(ui->radioRollCal->isChecked())
                    {
                        A=57.7;
                        b=(-0.718);
                        Csuper= A*(pow(Sulti,b));
                    }else {
                        if(ui->radioForja->isChecked())
                            {
                                A=272;
                                b=(-0.995);
                                Csuper= A*(pow(Sulti,b));
                            }
                       }
                }
            }

            //factor de confiabilidad
            if(Conf==50)
            {
                Cconf=1;
            }else if(Conf==90)
            {
                Cconf=0.897;
            }else if(Conf==95){
                Cconf=0.868;
            }else if(Conf==99){
                Cconf=0.814;
            }else if(Conf==99.9){
                Cconf=0.753;
            }
            //factor de temperatura
            if(T<=450)
            {
                Ctemp=1;
            }else if(T > 450 && T <= 550 )
            {
                Ctemp= 1-(0.0058*(T-450));
            }

            //limite de resistencia a la fatiga corregido
            Se=Cconf*Ctemp*Csuper*Ccarga*Ctama*Seprima;
            //Factores de seguridad
            FSone=Se/SigmaVa;

            //varibales iniciales
            ui->listWidget->addItem("VARIABLES INICIALES: ");
            ui->listWidget->addItem("Sut: "+QString::number(Sulti));
            ui->listWidget->addItem("Sy: "+QString::number(Syie));
            ui->listWidget->addItem("Carga Máxima: "+QString::number(LoaMax));
            ui->listWidget->addItem("Carga Mínima: "+QString::number(LoaMin));
            //ui->listWidget->addItem("Modulo Elástico: "+QString::number(Elastic));
            ui->listWidget->addItem("Diámetro interno: "+QString::number(dinte));
            ui->listWidget->addItem("Diámetro externo: "+QString::number(Dexte));
            ui->listWidget->addItem("Ciclaje: "+QString::number(Cicl));
            ui->listWidget->addItem("Confiabilidad: "+QString::number(Conf));
            ui->listWidget->addItem("Radio del punto: "+QString::number(RadioInteres)+"\n");
            //variables calculadas

            //esfuerzos
            ui->listWidget->addItem(("ESFUERZOS NOMINALES: "));
            ui->listWidget->addItem("Esfuerzo Tangencial : "+QString::number(SigmaTmax));
            ui->listWidget->addItem("Esfuerzo Radial : "+QString::number(SigmaRmax));
            ui->listWidget->addItem("Esfuerzo Axial : "+QString::number(SigmaAxmax)+"\n");
            //Esfuerzos principales
            ui->listWidget->addItem("Esfuerzo principal1 : "+QString::number(Sigma1));
            ui->listWidget->addItem("Esfuerzo principal2 : "+QString::number(Sigma2));
            ui->listWidget->addItem("Esfuerzo principal3 : "+QString::number(Sigma3)+"\n");


            //Von misses alternante y medio
            ui->listWidget->addItem(("VON MISSES ALTERNANTE: "));
            ui->listWidget->addItem("Von Misses Alternante: "+QString::number(SigmaVa)+"\n");

            //concentradores de esfuerzo
            ui->listWidget->addItem(("CONCENTRADORES DE ESFUERZOS: "));
            ui->listWidget->addItem("Kf: "+QString::number(kf));
            ui->listWidget->addItem("Kt: "+QString::number(kt)+"\n");
            //Factores C
            ui->listWidget->addItem(("FACTORES C: "));
            ui->listWidget->addItem("Factor de Carga: "+QString::number(Ccarga));
            ui->listWidget->addItem("Factor de Tamaño: "+QString::number(Ctama));
            ui->listWidget->addItem("Factor de Superficie: "+QString::number(Csuper));
            ui->listWidget->addItem("Factor de Confiabilidad: "+QString::number(Cconf));
            ui->listWidget->addItem("Factor de Temperatura: "+QString::number(Ctemp)+"\n");
            //limite de resistencia a la fatiga corregido.
            ui->listWidget->addItem(("LIMITE DE RESISTENCIA A LA FATIGA: "));
            ui->listWidget->addItem("Se Corregido: "+QString::number(Se)+"\n");

            //Se del material y Se corregido
            ui->listWidget->addItem(("Se DEL MATERIA & Se CORREGIDO: "));
            ui->listWidget->addItem("Se del material: "+QString::number(Seprima));
            ui->listWidget->addItem("Se Corregido: "+QString::number(Se)+"\n");
            //factores de seguridad
            ui->listWidget->addItem(("FACTORES DE SEGURIDAD: "));
            ui->listWidget->addItem("Factor de seguridad 1: "+QString::number(FSone)+"\n");

            ui->listWidget->addItem("-------------------------------------------""\n");
        }
    }
}
