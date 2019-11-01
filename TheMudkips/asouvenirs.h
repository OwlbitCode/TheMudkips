#ifndef ASOUVENIRS_H
#define ASOUVENIRS_H

#include <QWidget>

namespace Ui {
class aSouvenirs;
}

class aSouvenirs : public QWidget
{
    Q_OBJECT

public:
    explicit aSouvenirs(QWidget *parent = nullptr);
    ~aSouvenirs();

private:
    Ui::aSouvenirs *ui;
};

#endif // ASOUVENIRS_H
