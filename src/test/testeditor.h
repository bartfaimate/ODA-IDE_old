#ifndef TESTEDITOR_H
#define TESTEDITOR_H

#include <QObject>

class TestEditor : public QObject
{
    Q_OBJECT
public:
    explicit TestEditor(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TESTEDITOR_H