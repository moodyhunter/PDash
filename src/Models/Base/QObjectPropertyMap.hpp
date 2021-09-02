#pragma once
#include <QMetaProperty>
#include <QObject>
#include <QPair>

template<typename T>
struct QObjectPropertyMapConverter
{
    static_assert(std::is_base_of_v<QObject, T>, "T must be a subclass of QObject");
    static void Register()
    {
        bool r = true;

        r &= QMetaType::registerConverter<QVariantMap, T *>(QOverload<const QVariantMap &>::of(&QObjectPropertyMapConverter<T>::Create));
        r &= QMetaType::registerConverter<T *, QVariantMap>(QOverload<const T *>::of(&QObjectPropertyMapConverter<T>::Dump));

        r &= QMetaType::registerConverter<QVariantList, QList<T *>>(QOverload<const QVariantList &>::of(&QObjectPropertyMapConverter<T>::Create));
        r &= QMetaType::registerConverter<QList<T *>, QVariantList>(QOverload<const QList<T *>>::of(&QObjectPropertyMapConverter<T>::Dump));

        r &= QMetaType::registerConverter<QVariantPair, QPair<T *, T *>>(QOverload<const QVariantPair &>::of(&QObjectPropertyMapConverter<T>::Create));
        r &= QMetaType::registerConverter<QPair<T *, T *>, QVariantPair>(QOverload<const QPair<T *, T *>>::of(&QObjectPropertyMapConverter<T>::Dump));

        Q_ASSERT_X(r, Q_FUNC_INFO, "Type converter function registration failed.");
    }

    static T *Create(const QVariantMap &map)
    {
        return Create(map, nullptr);
    }

    static T *Create(const QVariantMap &map, QObject *parent)
    {
        auto self = new T{ parent };
        for (qsizetype i = 1; i < ((QObject *) self)->metaObject()->propertyCount(); i++)
        {
            const auto p = ((QObject *) self)->metaObject()->property(i);
            const auto name = QString::fromLatin1(p.name());
            if (!map.contains(name))
                continue;
            bool r = true;
            auto propvalue = map[name];
            if (p.metaType().id() >= QMetaType::User)
                r &= propvalue.convert(p.metaType());
            r &= p.write(self, propvalue);
            Q_ASSERT_X(r, Q_FUNC_INFO, "Type conversion failed.");
        }
        return self;
    }

    static QVariantMap Dump(const T *self)
    {
        QVariantMap map;
        if (!self)
            return map;
        for (qsizetype i = 1; i < ((QObject *) self)->metaObject()->propertyCount(); i++)
        {
            const auto p = ((QObject *) self)->metaObject()->property(i);
            const auto name = QString::fromLatin1(p.name());
            map[name] = p.read(self);
            if (p.metaType().id() >= QMetaType::User)
            {
                if (QMetaType::canConvert(p.metaType(), QMetaType{ QMetaType::QVariantMap }))
                    map[name].convert(QMetaType::fromType<QVariantMap>());
                else if (QMetaType::canConvert(p.metaType(), QMetaType{ QMetaType::QVariantList }))
                    map[name].convert(QMetaType::fromType<QVariantList>());
            }
        }
        return map;
    }

    static QList<T *> Create(const QVariantList &self)
    {
        QList<T *> list;
        for (const auto &val : self)
            list << Create(val.toMap());
        return list;
    }
    static QVariantList Dump(const QList<T *> self)
    {
        QVariantList list;
        for (const auto &ptr : self)
            list << Dump(ptr);
        return list;
    }

    static QPair<T *, T *> Create(const QVariantPair &self)
    {
        return QPair<T *, T *>{ Create(self.first.toMap()), Create(self.second.toMap()) };
    }
    static QVariantPair Dump(const QPair<T *, T *> self)
    {
        return QVariantPair{ Dump(self.first), Dump(self.second) };
    }
};

///
/// \brief Register type T to QMetaType converter
///
template<typename T>
constexpr auto qpmRegisterType = &QObjectPropertyMapConverter<T>::Register;

// For T* and QVariantMap
template<typename T>
constexpr auto qpmCreateObject = QOverload<const QVariantMap &, QObject *>::of(&QObjectPropertyMapConverter<T>::Create);

template<typename T>
constexpr auto qpmDumpObject = QOverload<const T *>::of(&QObjectPropertyMapConverter<T>::Dump);

// For QList<T*> and QVariantList
template<typename T>
constexpr auto qpmCreateObjectList = QOverload<const QVariantList &>::of(&QObjectPropertyMapConverter<T>::Create);

template<typename T>
constexpr auto qpmDumpObjectList = QOverload<const QList<T *> &>::of(&QObjectPropertyMapConverter<T>::Dump);

// For QPair<T*, T*> and QVariantPair
template<typename T>
constexpr auto qpmCreateObjectPair = QOverload<const QVariantPair &>::of(&QObjectPropertyMapConverter<T>::Create);

template<typename T>
constexpr auto qpmDumpObjectPair = QOverload<const QPair<T *, T *>>::of(&QObjectPropertyMapConverter<T>::Dump);
