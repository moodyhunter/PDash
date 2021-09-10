#pragma once

#include <QQuickView>

class QResizeEvent;

namespace PD
{
    class PDMainWindow : public QQuickView
    {
        Q_OBJECT
      public:
        PDMainWindow();

        void Open();

      private slots:
        void p_QmlImportPathAdded(const QString &path);

#ifdef Q_OS_MACOS
      protected:
        void resizeEvent(QResizeEvent *ev);

      private:
        QWindow *m_effectsBackgroundWindow;
#endif

      private:
        QQuickView *quickWindow;
    };
} // namespace PD
