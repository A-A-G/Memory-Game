#include "Card.h"

Card::Card(int value, QWidget *parent, int width, int height, int fontSize, QColor backColor, QColor frontColor, QColor errorColor, QColor hitColor)
    :QPushButton(parent),
     _value(value),
     _backColor(backColor),
     _frontColor(frontColor),
     _errorColor(errorColor),
     _hitColor(hitColor)
{
    this->setFixedSize(width, height);

    //change font size
    QFont font = this->font();
    font.setPointSize(fontSize);
    setFont(font);
    setNeutral();
}

void Card::changeBGColor(const QColor& color) //doesn't work on windows
{
    this->setBackgroundRole(QPalette::Background);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Button, color);
    setAutoFillBackground(true);
    setPalette(pal);
    update();
}

void Card::setHit()
{
    disconnect();
    setText(QString::number(_value));
#ifdef Q_OS_WIN32
    setStyleSheet(QString("background-color:%1;").arg(_hitColor.name()));
#else
    changeBGColor(_hitColor);
#endif
}

void Card::setFalse()
{
    setText(QString::number(_value));
#ifdef Q_OS_WIN32
    setStyleSheet(QString("background-color:%1;").arg(_errorColor.name()));
#else
    changeBGColor(_errorColor);
#endif
}

void Card::setTurned()
{
    setText(QString::number(_value));
#ifdef Q_OS_WIN32
    setStyleSheet(QString("background-color:%1;").arg(_frontColor.name()));
#else
    changeBGColor(_frontColor);
#endif
}

void Card::setNeutral()
{
    setText("X");
#ifdef Q_OS_WIN32
    setStyleSheet(QString("background-color:%1;").arg(_backColor.name()));
#else
    changeBGColor(_backColor);
#endif
}

int Card::getValue() const
{
    return _value;
}