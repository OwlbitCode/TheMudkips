#ifndef VDFS_H
#define VDFS_H

#include <QWidget>

namespace Ui {
class vDFS;
}

class vDFS : public QWidget
{
    Q_OBJECT

public:
    explicit vDFS(QWidget *parent = nullptr);
    ~vDFS();

private:
    Ui::vDFS *ui;
};

#endif // VDFS_H
