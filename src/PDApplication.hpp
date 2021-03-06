#pragma once
#include <SingleApplication>

// clang-format off
namespace PD::Database { class PDDatabaseManager; }
namespace PD::Core { class PDPluginManager; }
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
        int run();

        PD::Database::PDDatabaseManager *DatabaseManager() const;
        PD::Core::PDPluginManager *PluginManager() const;
        static QStringList GetAssetsPath(const QString &dirName);

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
