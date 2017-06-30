#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define ABS(X) (X<0.0?-X:X)

// forward declaration of classes
class soilLayer;
class QTableWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void doAnalysis(void);

private slots:
    // soil parameter values entered/changed

    // program controls
    //void on_analyzeButton_clicked();

    // menu actions
    void on_actionExit_triggered();

    // check boxes
    void on_chkBox_assume_rigid_cap_clicked(bool checked);
    void on_chkBox_include_toe_resistance_clicked(bool checked);

    // geometry parameters entered/changed
    void on_displacementSlider_valueChanged(int value);
    void on_pileDiameter_valueChanged(double arg1);
    void on_embeddedLength_valueChanged(double arg1);
    void on_freeLength_valueChanged(double arg1);
    void on_Emodulus_valueChanged(double arg1);
    void on_groundWaterTable_valueChanged(double arg1);

    // material table slots
    void updateInfo(QTableWidgetItem *);
    void on_appliedForce_valueChanged(double arg1);
    void on_appliedForce_editingFinished();

private:
    Q_OBJECT
    Ui::MainWindow *ui;

    // get data
    double P;  // lateral force on pile
    double L1; // pile length above ground
    double L2; // embedded length of pile
    double pileDiameter;  // pile diameter
    double E;  // pile modulus of elasticity

    double gwtDepth;  // depth of ground water table below the surface

    // states
    bool assumeRigidPileHead = false;
    bool useToeResistance    = false;
    int  puSwitch;
    int  kSwitch;
    int  gwtSwitch;

    // load parameter
    double displacementRatio;

    // soil layers and related methods
    QVector<soilLayer> mSoilLayers;

    void setupLayers();
    void reDrawTable();

    // meshing parameters
    int minElementsPerLayer = 15;
    int maxElementsPerLayer = 40;
    int numElementsInAir    =  4;
    int numEle;

    // temporary variables
    double gamma;
    double gammaWet;
    double gammaSaturated;
    double phi;
    double gSoil;
    double totalStress;
    double effectiveStress;
    double porePressure;
    double overburdonStress;
    double groundWaterHead;

    double zCoord = 0.0;  // z-coordinate of point.  Negative if below the surface
    double eleSize;       // effective element length for p-y and t-z springs
    double sigV;          // effective stress at p-y and t-z springs
    double pult, y50;     // lateral resistance
    double tult, z50;     // shaft friction
    double qult, z50q;    // toe resistance

    // setup switch
    bool inSetupState = true;

};

#endif // MAINWINDOW_H