#pragma once

#include "Base/PDBaseModel2.hpp"

namespace PD::Models
{
    class ActivityModel : public Base::PDBaseModel<ActivityModel>
    {
        Q_OBJECT

      public:
        static PDModelInfo TypeInfo;
        static QString TableName;
        static PDModelOptions ModelOptions;

      public:
        explicit ActivityModel(QObject *parent = nullptr);
        virtual ~ActivityModel() = default;
    };
} // namespace PD::Models
