#pragma once

#include <QObject>

class PDBaseModel : public QObject
{
    Q_OBJECT

  public:
    PDBaseModel(QObject *parent = nullptr) : QObject(parent){};
    virtual ~PDBaseModel(){};
    virtual void LoadData() = 0;
};
