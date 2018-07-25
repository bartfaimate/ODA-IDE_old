#ifndef INTELLISENSE_H
#define INTELLISENSE_H

#include <QObject>

class Intellisense : public QObject
{
    Q_OBJECT
public:
    explicit Intellisense(QObject *parent = nullptr);

    QSet *setOfKeyWords;    /* holds the keywords */
signals:

public slots:
};

#endif // INTELLISENSE_H
