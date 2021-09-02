#pragma once

#define PD_PROPERTY_PTR(type, name, Name)                                                                                                                                \
    Q_PROPERTY(type *name READ get##Name WRITE set##Name)                                                                                                                \
  private:                                                                                                                                                               \
    type *m_##name = nullptr;                                                                                                                                            \
                                                                                                                                                                         \
  public:                                                                                                                                                                \
    type *get##Name() const                                                                                                                                              \
    {                                                                                                                                                                    \
        return m_##name;                                                                                                                                                 \
    }                                                                                                                                                                    \
    void set##Name(type *o)                                                                                                                                              \
    {                                                                                                                                                                    \
        if (m_##name)                                                                                                                                                    \
            delete m_##name;                                                                                                                                             \
        m_##name = o;                                                                                                                                                    \
        if (m_##name)                                                                                                                                                    \
            m_##name->setParent(this);                                                                                                                                   \
    }                                                                                                                                                                    \
                                                                                                                                                                         \
  private:

#define PD_PROPERTY(type, name, Name)                                                                                                                                    \
    Q_PROPERTY(type name READ get##Name WRITE set##Name NOTIFY on##Name##Changed)                                                                                        \
  private:                                                                                                                                                               \
    type m_##name;                                                                                                                                                       \
                                                                                                                                                                         \
  public:                                                                                                                                                                \
    type get##Name() const                                                                                                                                               \
    {                                                                                                                                                                    \
        return m_##name;                                                                                                                                                 \
    }                                                                                                                                                                    \
    void set##Name(const type &newValue)                                                                                                                                 \
    {                                                                                                                                                                    \
        if (m_##name == newValue)                                                                                                                                        \
            return;                                                                                                                                                      \
        m_##name = newValue;                                                                                                                                             \
        Q_EMIT on##Name##Changed(m_##name);                                                                                                                              \
    }                                                                                                                                                                    \
    Q_SIGNAL void on##Name##Changed(const type &v);                                                                                                                      \
                                                                                                                                                                         \
  private:

#define PD_PROPERTY_QMLLIST(ModelClass, name, Name, thisClass)                                                                                                           \
  private:                                                                                                                                                               \
    QList<ModelClass *> m_##name##_list;                                                                                                                                 \
                                                                                                                                                                         \
  public:                                                                                                                                                                \
    Q_SIGNAL void name##ListChanged();                                                                                                                                   \
    void append##Name(ModelClass *p)                                                                                                                                     \
    {                                                                                                                                                                    \
        m_##name##_list.append(p);                                                                                                                                       \
        Q_EMIT name##ListChanged();                                                                                                                                      \
    }                                                                                                                                                                    \
    qsizetype name##Count() const                                                                                                                                        \
    {                                                                                                                                                                    \
        return m_##name##_list.count();                                                                                                                                  \
    }                                                                                                                                                                    \
    ModelClass *name(qsizetype index) const                                                                                                                              \
    {                                                                                                                                                                    \
        return m_##name##_list.at(index);                                                                                                                                \
    }                                                                                                                                                                    \
    void clear##name##_list()                                                                                                                                            \
    {                                                                                                                                                                    \
        m_##name##_list.clear();                                                                                                                                         \
        Q_EMIT name##ListChanged();                                                                                                                                      \
    }                                                                                                                                                                    \
    void replace##Name(qsizetype index, ModelClass *p)                                                                                                                   \
    {                                                                                                                                                                    \
        m_##name##_list[index] = p;                                                                                                                                      \
        Q_EMIT name##ListChanged();                                                                                                                                      \
    }                                                                                                                                                                    \
    void removeLast##Name()                                                                                                                                              \
    {                                                                                                                                                                    \
        m_##name##_list.removeLast();                                                                                                                                    \
        Q_EMIT name##ListChanged();                                                                                                                                      \
    }                                                                                                                                                                    \
    QQmlListProperty<ModelClass> name##_list()                                                                                                                           \
    {                                                                                                                                                                    \
        return QQmlListProperty<ModelClass>{                                                                                                                             \
            this,                                                                                                                                                        \
            this,                                                                                                                                                        \
            &thisClass::append##Name,                                                                                                                                    \
            &thisClass::name##Count,                                                                                                                                     \
            &thisClass::name,                                                                                                                                            \
            &thisClass::clear##name##_list,                                                                                                                              \
            &thisClass::replace##Name,                                                                                                                                   \
            &thisClass::removeLast##Name,                                                                                                                                \
        };                                                                                                                                                               \
    }                                                                                                                                                                    \
                                                                                                                                                                         \
  private:                                                                                                                                                               \
    static void append##Name(QQmlListProperty<ModelClass> *list, ModelClass *p)                                                                                          \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->append##Name(p);                                                                                                      \
    }                                                                                                                                                                    \
    static qsizetype name##Count(QQmlListProperty<ModelClass> *list)                                                                                                     \
    {                                                                                                                                                                    \
        return reinterpret_cast<thisClass *>(list->data)->name##Count();                                                                                                 \
    }                                                                                                                                                                    \
    static ModelClass *name(QQmlListProperty<ModelClass> *list, qsizetype i)                                                                                             \
    {                                                                                                                                                                    \
        return reinterpret_cast<thisClass *>(list->data)->name(i);                                                                                                       \
    }                                                                                                                                                                    \
    static void clear##name##_list(QQmlListProperty<ModelClass> *list)                                                                                                   \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->clear##name##_list();                                                                                                 \
    }                                                                                                                                                                    \
    static void replace##Name(QQmlListProperty<ModelClass> *list, qsizetype i, ModelClass *p)                                                                            \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->replace##Name(i, p);                                                                                                  \
    }                                                                                                                                                                    \
    static void removeLast##Name(QQmlListProperty<ModelClass> *list)                                                                                                     \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->removeLast##Name();                                                                                                   \
    }
