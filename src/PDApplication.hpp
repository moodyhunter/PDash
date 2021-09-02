#pragma once

#if PD_DEBUG_MODEL
#define PD_APP_CLASS QApplication
#include <QApplication>
#else
#define PD_APP_CLASS QGuiApplication
#include <QGuiApplication>
#endif

namespace PD::Database
{
    class PDDatabaseManager;
}

class PDApplication : public PD_APP_CLASS
{
    Q_OBJECT

  public:
    explicit PDApplication(int &argc, char *argv[]);
    virtual ~PDApplication();
    void initialize();
    int exec();

    PD::Database::PDDatabaseManager *DatabaseManager() const;

  private:
    PD::Database::PDDatabaseManager *m_dbManager;
};

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<PDApplication *>(QCoreApplication::instance()))

#if defined(pdApp)
#undef pdApp
#endif
#define pdApp (static_cast<PDApplication *>(QCoreApplication::instance()))
