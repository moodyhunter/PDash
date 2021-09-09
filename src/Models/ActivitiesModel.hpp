#pragma once

#include "Core/PDBaseListModel.hpp"

namespace PD::Models
{
    class ActivityModel : public Base::PDBaseListModel<ActivityModel>
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
