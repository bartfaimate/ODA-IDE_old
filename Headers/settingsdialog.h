#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private:
    Ui::SettingsDialog *ui;

    QString settingsPath = "configs/settings.ini";

signals:
    void okClicked();

public slots:
    void saveSettings();
    void loadSettings();
};

#endif // SETTINGSDIALOG_H
