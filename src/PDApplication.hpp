#pragma once
#include <SingleApplication>

// clang-format off
namespace PD::Database { class PDDatabaseManager; }
namespace PD::Core { class PDPluginManager; }
namespace PD { class PDMainWindow; }
// clang-format on

QT_BEGIN_NAMESPACE
class QQmlApplicationEngine;
QT_END_NAMESPACE

namespace PD
{
    class PDApplication : public SingleApplication
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
        QQmlApplicationEngine *m_engine;
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
