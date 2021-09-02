#pragma once

#include "Base/PDBaseModel2.hpp"

namespace PD::Models
{
    class PanelModel : public Base::PDBaseModel<PanelModel>
    {
        Q_OBJECT

      public:
        static PDModelInfo TypeInfo;
        static QString TableName;

      public:
        explicit PanelModel(QObject *parent = nullptr);
        virtual ~PanelModel() = default;
    };
} // namespace PD::Models
