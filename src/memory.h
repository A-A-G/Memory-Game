#ifndef HELLOWORLDQT_H
#define HELLOWORLDQT_H

#include <QMainWindow>
#include <QList>

class Card;
class FlowLayout;
class QSignalMapper;

class Memory : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Memory(int numberOfPairs = 8, QWidget *parent = 0);
        ~Memory();

    private slots:
        void clicked(QWidget* widget);
        void newGame();

    private:
        FlowLayout* _flowLayout;
        QList<Card*> _selectedCards;
        QSignalMapper* _signalMapper;
        int _numberOfPairs;
        int _clickCounter;

};

#endif // HELLOWORLDQT_H
