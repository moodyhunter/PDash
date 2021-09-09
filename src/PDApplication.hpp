#pragma once

#if PD_DEBUG_MODEL
#define PD_APP_CLASS QApplication
#include <QApplication>
#else
#define PD_APP_CLASS QGuiApplication
#include <QGuiApplication>
#endif

// clang-format off
namespace PD::Database { class PDDatabaseManager; }
namespace PD::Core { class PDPluginManager; }
// clang-format on

namespace PD
{
    class PDApplication : public PD_APP_CLASS
    {
        Q_OBJECT

      public:
        explicit PDApplication(int &argc, char *argv[]);
        virtual ~PDApplication();
        void initialize();
        int exec();

        PD::Database::PDDatabaseManager *DatabaseManager() const;
        PD::Core::PDPluginManager *PluginManager() const;

      private:
        PD::Database::PDDatabaseManager *m_dbManager;
        PD::Core::PDPluginManager *m_pluginManager;
    };
} // namespace PD

#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<PD::PDApplication *>(QCoreApplication::instance()))

#if defined(pdApp)
#undef pdApp
#endif
#define pdApp (static_cast<PD::PDApplication *>(QCoreApplication::instance()))
