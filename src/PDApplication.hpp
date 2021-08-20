#pragma once

#include <QGuiApplication>

class AppThemeModel;
class MainWindowModel;
class DBManager;

class PDApplication : public QGuiApplication
{
    Q_OBJECT

  public:
    explicit PDApplication(int &argc, char *argv[]);
    void initialize();
    int exec();

  private:
    AppThemeModel *appTheme;
    MainWindowModel *mainWindowModel;
    DBManager *dbManager;
};
