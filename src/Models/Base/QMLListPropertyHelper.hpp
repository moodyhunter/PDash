#pragma once

#define QMLListFunctions(name, Name, thisClass, ModelClass, varname)                                                                                                     \
  public:                                                                                                                                                                \
    void append##Name(ModelClass *p)                                                                                                                                     \
    {                                                                                                                                                                    \
        varname.append(p);                                                                                                                                               \
    }                                                                                                                                                                    \
    qsizetype name##Count() const                                                                                                                                        \
    {                                                                                                                                                                    \
        return varname.count();                                                                                                                                          \
    }                                                                                                                                                                    \
    ModelClass *name(qsizetype index) const                                                                                                                              \
    {                                                                                                                                                                    \
        return varname.at(index);                                                                                                                                        \
    }                                                                                                                                                                    \
    void clear##Name##s()                                                                                                                                                \
    {                                                                                                                                                                    \
        varname.clear();                                                                                                                                                 \
    }                                                                                                                                                                    \
    void replace##Name(qsizetype index, ModelClass *p)                                                                                                                   \
    {                                                                                                                                                                    \
        varname[index] = p;                                                                                                                                              \
    }                                                                                                                                                                    \
    void removeLast##Name()                                                                                                                                              \
    {                                                                                                                                                                    \
        varname.removeLast();                                                                                                                                            \
    }                                                                                                                                                                    \
    QQmlListProperty<ModelClass> name##s()                                                                                                                               \
    {                                                                                                                                                                    \
        return QQmlListProperty<ModelClass>{                                                                                                                             \
            this,                                                                                                                                                        \
            this,                                                                                                                                                        \
            &thisClass::append##Name,                                                                                                                                    \
            &thisClass::name##Count,                                                                                                                                     \
            &thisClass::name,                                                                                                                                            \
            &thisClass::clear##Name##s,                                                                                                                                  \
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
    static void clear##Name##s(QQmlListProperty<ModelClass> *list)                                                                                                       \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->clear##Name##s();                                                                                                     \
    }                                                                                                                                                                    \
    static void replace##Name(QQmlListProperty<ModelClass> *list, qsizetype i, ModelClass *p)                                                                            \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->replace##Name(i, p);                                                                                                  \
    }                                                                                                                                                                    \
    static void removeLast##Name(QQmlListProperty<ModelClass> *list)                                                                                                     \
    {                                                                                                                                                                    \
        reinterpret_cast<thisClass *>(list->data)->removeLast##Name();                                                                                                   \
    }
