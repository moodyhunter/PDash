#pragma once

#include "Base/PDBaseModel.hpp"

#include <QColor>

class AppThemeModel : public PDBaseModel
{
    Q_OBJECT
  public:
    explicit AppThemeModel(QObject *parent = nullptr);
    virtual void LoadData() override;

    Q_PROPERTY(QColor background READ getBackground WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(QColor dark READ getDark WRITE setDark NOTIFY darkChanged)
    Q_PROPERTY(QColor highlight READ getHighlight WRITE setHighlight NOTIFY highlightChanged)
    Q_PROPERTY(QColor highlightText READ getHighlightText WRITE setHighlightText NOTIFY highlightTextChanged)
    Q_PROPERTY(QColor text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QColor warn READ getWarn WRITE setWarn NOTIFY warnChanged)
    Q_PROPERTY(QColor shadow READ getShadow WRITE setShadow NOTIFY shadowChanged)
    Q_PROPERTY(QColor border READ getBorder WRITE setBorder NOTIFY borderChanged)
    Q_PROPERTY(QColor deep READ getDeep WRITE setDeep NOTIFY deepChanged)
    Q_PROPERTY(QColor deepText READ getDeepText WRITE setDeepText NOTIFY deepTextChanged)

    const QColor &getBackground() const;
    const QColor &getDark() const;
    const QColor &getHighlight() const;
    const QColor &getHighlightText() const;
    const QColor &getText() const;
    const QColor &getWarn() const;
    const QColor &getShadow() const;
    const QColor &getBorder() const;
    const QColor &getDeep() const;
    const QColor &getDeepText() const;

    void setBackground(const QColor &newBackground);
    void setDark(const QColor &newDark);
    void setHighlight(const QColor &newHighlight);
    void setHighlightText(const QColor &newHighlightText);
    void setText(const QColor &newText);
    void setWarn(const QColor &newWarn);
    void setShadow(const QColor &newShadow);
    void setBorder(const QColor &newBorder);
    void setDeep(const QColor &newDeep);
    void setDeepText(const QColor &newDeepText);

  signals:
    void backgroundChanged();
    void darkChanged();
    void highlightChanged();
    void highlightTextChanged();
    void textChanged();
    void warnChanged();
    void shadowChanged();
    void borderChanged();
    void deepChanged();
    void deepTextChanged();

  private:
    QColor background;
    QColor dark;
    QColor highlight;
    QColor highlightText;
    QColor text;
    QColor warn;
    QColor shadow;
    QColor border;
    QColor deep;
    QColor deepText;
    double backgroundOpacity = 0.3;
};
