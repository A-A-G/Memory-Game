#include "memory.h"

#include "Card.h"
#include "FlowLayout.h"

#include <QLabel>
#include <QSignalMapper>
#include <QStatusBar>
#include <QMenuBar>

#include <QDebug>

#include <algorithm>
#include <random>

Memory::Memory(int numberOfPairs, QWidget *parent)
        :QMainWindow(parent),
         _flowLayout(new FlowLayout(new QWidget(this), 10, 20, 20)),
         _selectedCards(),
         _signalMapper(new QSignalMapper(this)),
         _numberOfPairs(numberOfPairs),
         _clickCounter(0)
{
    setWindowTitle("Memory");

    setCentralWidget(_flowLayout->parentWidget());

    //Menu
    QMenu* gameMenu = menuBar()->addMenu(tr("&Game"));
    QAction *newGame = new QAction(tr("&New Game"), gameMenu);
    //connect(newGame, SIGNAL(triggered(bool)), this, SLOT(newGame())); //old syntax
    connect(newGame, &QAction::triggered, this, &Memory::newGame);
    gameMenu->addAction(newGame);

    //Status Bar
    statusBar()->showMessage("Click a card for start.");

    this->resize(300, 400);

    connect(_signalMapper, QOverload<QWidget*>::of(&QSignalMapper::mapped), this, &Memory::clicked);

    Memory::newGame();
}

void Memory::newGame()
{
    _selectedCards.clear();
    _clickCounter = 0;
    statusBar()->showMessage(QString("Clicks: %1").arg(_clickCounter));

    //Clear layout and delete all cards
    QLayoutItem *child;
    while ((child = _flowLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }

    //Generate Cards
    QList<Card*> cards;
    for (int i = 0; i < _numberOfPairs; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            Card *card = new Card(i, this);
            //connect(card, SIGNAL(clicked()), _signalMapper, SLOT(map())); //old syntax, no check at compile time, warning message(!) at runtime
            //connect(card, &Card::clicked, _signalMapper, qOverload<>(&QSignalMapper::map));
            connect(card, &Card::clicked, _signalMapper, QOverload<>::of(&QSignalMapper::map));
             _signalMapper->setMapping(card, card);
            cards.append(card);
        }
    }

    //Shuffle Cards
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(std::chrono::steady_clock::now().time_since_epoch().count()));

    //Layout Cards
    foreach(Card* card, cards)
    {
        _flowLayout->addWidget(card);
    }
}

void Memory::clicked(QWidget *widget)
{
    Card* card = dynamic_cast<Card*>(widget);
    if (nullptr != card)
    {
        if (_selectedCards.size() == 2)
        {
            _selectedCards[0]->setNeutral();
            _selectedCards[1]->setNeutral();
            _selectedCards.clear();
            _selectedCards.append(card);
            card->setTurned();
        }
        else if (_selectedCards.size() == 1)
        {
            if (card->getValue() == _selectedCards[0]->getValue())
            {
                card->setHit();
                _selectedCards[0]->setHit();
                _selectedCards.clear();
            }
            else
            {
                card->setFalse();
                _selectedCards[0]->setFalse();
                _selectedCards.append(card);
            }
        }
        else
        {
            _selectedCards.append(card);
            card->setTurned();
        }
        _clickCounter++;
        statusBar()->showMessage(QString("Clicks: %1").arg(_clickCounter));
    }
    else
    {
        qDebug() << "Something wrong!";
    }
}

Memory::~Memory()
{

}