#pragma once

#include <QMap>
#include <QObject>
#include <QVariant>

namespace PD::Database
{
    Q_NAMESPACE
    enum class DBFieldType
    {
        INTEGER = QMetaType::LongLong,
        REAL = QMetaType::Double,
        TEXT = QMetaType::QString,
        BLOB = QMetaType::QByteArray,
    };
    Q_ENUM_NS(DBFieldType)

    struct ModelDBField
    {
        QString dbName;
        DBFieldType dbType;
        QVariant dbDefaultValue;
        ModelDBField(const QString &name, DBFieldType type, const QVariant &val = QVariant{})
            : dbName(name), //
              dbType(type), //
              dbDefaultValue(val){};
    };

    void pdRegisterDBTable(const QString &tableName, const QList<ModelDBField> &fields);

    class PDDatabaseManager : public QObject
    {
        Q_OBJECT
        friend void pdRegisterDBTable(const QString &tableName, const QList<ModelDBField> &fields);

      public:
        PDDatabaseManager(QObject *parent = nullptr);
        virtual ~PDDatabaseManager();

        Q_INVOKABLE bool openDatabase(const QString &dbName, const QString &password);
        qlonglong GetTableSize(const QString &table);
        QMap<int, QVariantMap> Select(const QString &table, const QStringList &fields, int offset = 0, int limit = 0);
        void Update(const QString &table, int id, const QStringList &fields, const QVariantList &fieldData);

      signals:
        void OnDatabaseOpened();

      private:
        bool CheckAndCreateTable();
        static inline QMap<QString, QList<ModelDBField>> tableFields;
        bool m_isDatabaseOpened = false;
    };

} // namespace PD::Database
