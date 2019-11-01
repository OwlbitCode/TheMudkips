#ifndef NBASOUVENIRS_H
#define NBASOUVENIRS_H

#include <QWidget>

namespace Ui {
class nbaSouvenirs;
}

class nbaSouvenirs : public QWidget
{
    Q_OBJECT

public:
    explicit nbaSouvenirs(QWidget *parent = nullptr);
    ~nbaSouvenirs();

private:
    Ui::nbaSouvenirs *ui;
};

#endif // NBASOUVENIRS_H
