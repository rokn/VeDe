#ifndef COLORCHANGEBUTTON_H
#define COLORCHANGEBUTTON_H

#include <QPushButton>
#include <QColor>

class ColorChangeButton : public QPushButton
{
    Q_OBJECT
public:
    ColorChangeButton(const QColor &color, QWidget* parent = 0);

public slots:
    void onClick(bool checked);

signals:
    void colorChanged(const QColor& color);

private:
    QColor m_color;

    void changeColor(const QColor& color);
};

#endif // COLORCHANGEBUTTON_H
