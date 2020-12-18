#ifndef DIALOGPAWNPROMOTION_H
#define DIALOGPAWNPROMOTION_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class DialogPawnPromotion;
}

class DialogPawnPromotion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPawnPromotion(QWidget *parent = nullptr);
    ~DialogPawnPromotion();
    QString election = "";
    QPushButton* pieces[4];
    void createIcons(QString);
public slots:
    void queen();
    void bishop();
    void knight();
    void rook();
private:
    Ui::DialogPawnPromotion *ui;
};

#endif // DIALOGPAWNPROMOTION_H
