#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "QProcess"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect signals and slots for QProcess events
    connect(&zipper, &QProcess::readyReadStandardOutput, this, &MainWindow::readyToRead);
    connect(&zipper, &QProcess::stateChanged, this, &MainWindow::zippingStatus);
    connect(&zipper, &QProcess::errorOccurred, this, &MainWindow::errorOcccured);
    connect(&zipper, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), this, &MainWindow::processFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Add files button
void MainWindow::on_btn_addfiles_clicked()
{
    // Open file browser dialog and get selected files
    filelist = QFileDialog::getOpenFileNames(this, "File Browser", "", "*.*");

    // Display selected files in text edit
    for(int i = 0 ;i < filelist.length(); i++) {
        ui->textEdit->append(filelist[i]);
    }
}

// Remove files button
void MainWindow::on_btn_removefiles_clicked()
{
    // Clear text edit
    ui->textEdit->clear();
}

// Browse button for selecting output directory
void MainWindow::on_btn_browse_clicked()
{
    // Open directory browser dialog and get selected directory
    directory = QFileDialog::getSaveFileName(this, "Output directory", "", "*.7z *.zip *.rar *.gzip");

    // Display selected directory in line edit
    ui->lineEdit->setText(directory);
}

// Compress files button
void MainWindow::on_btn_compress_clicked()
{
    // Set working directory to application directory
    zipper.setWorkingDirectory(QCoreApplication::applicationDirPath());

    // Set parameters for 7zip command
    QStringList a; a << "a" << directory << filelist;

    // Start QProcess with 7zip command and parameters
    zipper.start("7za", a);
}

// Slot for handling QProcess state changes
void MainWindow::zippingStatus(QProcess::ProcessState state)
{
    switch(state){
    case QProcess::NotRunning:
        ui->lbl_status->setText("Status: Ready");
        break;

    case QProcess::Running:
    case QProcess::Starting:
        ui->lbl_status->setText("Status: Loading...");
        break;

    default:
        break;
    }
}

// Slot for handling QProcess errors
void MainWindow::errorOcccured(QProcess::ProcessError error)
{
    QMessageBox::critical(this,tr("Echo wrapper"), tr("Error %1 has occured").arg(error));
}

// Slot for handling QProcess finish
void MainWindow::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    switch (exitStatus){

        case QProcess::CrashExit:
            // Display error message if 7zip crashed
            QMessageBox::critical(this, tr("Zipper"), tr("7zip has crashed"));
            break;

        case QProcess::NormalExit:
            // Display warning message if 7zip exited with non-zero code
            QMessageBox::warning(this, tr("Zipper"), QString("7zip has exited with code %1").arg(exitCode));
            break;

        default:
            break;
    }
}


// Slot for handling QProcess
void MainWindow::readyToRead(){

    QMessageBox::warning(this, tr("Zipper"),zipper.readAllStandardOutput());
}

