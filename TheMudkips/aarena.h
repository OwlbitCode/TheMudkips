#ifndef AARENA_H
#define AARENA_H

#include <QWidget>

namespace Ui {
class aArena;
}

class aArena : public QWidget
{
    Q_OBJECT

public:
    explicit aArena(QWidget *parent = nullptr);
    ~aArena();

private:
    Ui::aArena *ui;
};

#endif // AARENA_H
