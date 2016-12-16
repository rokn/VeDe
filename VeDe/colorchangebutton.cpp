#include "colorchangebutton.h"
#include <QPalette>
#include <QColorDialog>

ColorChangeButton::ColorChangeButton(const QColor& color, QWidget *parent)
    :QPushButton(parent), m_color(color)
{
    setFlat(true);
    setAutoFillBackground(true);
    changeColor(m_color);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(onClick(bool)));
}

void ColorChangeButton::onClick(bool checked)
{
    QColor newColor = QColorDialog::getColor(m_color, this, "Pick a color", QColorDialog::ShowAlphaChannel);

    if(!newColor.isValid()) return;

    m_color = newColor;
    changeColor(m_color);
    emit colorChanged(m_color);
}

void ColorChangeButton::changeColor(const QColor &color)
{
    QPalette pal = this->palette();
    pal.setColor(backgroundRole(), color);
    setPalette(pal);
}

