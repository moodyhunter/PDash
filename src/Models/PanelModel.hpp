#pragma once

#include "Core/PDBaseListModel.hpp"

namespace PD::Models
{
    class PanelModel : public Base::PDBaseListModel<PanelModel>
    {
        Q_OBJECT

      public:
        static PDModelInfo TypeInfo;
        static QString TableName;
        static PDModelOptions ModelOptions;

      public:
        explicit PanelModel(QObject *parent = nullptr);
        virtual ~PanelModel() = default;
    };
} // namespace PD::Models
