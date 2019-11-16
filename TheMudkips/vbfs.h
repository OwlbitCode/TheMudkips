#ifndef VBFS_H
#define VBFS_H

#include <QWidget>

namespace Ui {
class vBFS;
}

class vBFS : public QWidget
{
    Q_OBJECT

public:
    explicit vBFS(QWidget *parent = nullptr);
    ~vBFS();

private:
    Ui::vBFS *ui;
};

#endif // VBFS_H
