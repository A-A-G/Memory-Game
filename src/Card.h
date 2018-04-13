#ifndef MEMORYQT_CARD_H
#define MEMORYQT_CARD_H

#include <QPushButton>
#include <QColor>

class Card : public QPushButton
{
    Q_OBJECT

    public:
        Card(int value, QWidget* parent = 0, int width = 50, int height = 70, int fontSize = 16, QColor backColor = Qt::darkGray, QColor frontColor = Qt::gray, QColor errorColor = Qt::red, QColor hitColor = Qt::cyan);

    int getValue() const;

    public slots:
        void setHit();
        void setFalse();
        void setNeutral();
        void setTurned();

    private:
        void changeBGColor(const QColor& color);

        int _value;
        QColor _backColor;
        QColor _frontColor;
        QColor _errorColor;
        QColor _hitColor;
};


#endif //MEMORYQT_CARD_H