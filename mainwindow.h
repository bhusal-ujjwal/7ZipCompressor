#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slots for handling user interface events (close and quit linked on UI)
    void on_btn_addfiles_clicked();
    void on_btn_removefiles_clicked();
    void on_btn_compress_clicked();
    void on_btn_browse_clicked();

    // Slots for handling QProcess events
    void zippingStatus(QProcess::ProcessState state);
    void errorOcccured(QProcess::ProcessError error);
    void readyToRead();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    // Private member variables
    Ui::MainWindow *ui;
    QStringList filelist;  // List of files to be compressed
    QString directory;  // Directory where compressed file will be saved
    QProcess zipper;  // QProcess object for compressing files
};

#endif // MAINWINDOW_H

