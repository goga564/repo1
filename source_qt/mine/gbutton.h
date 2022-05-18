#ifndef GBUTTON_H
#define GBUTTON_H
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
class GameMainButton : public QPushButton {
        Q_OBJECT;
        int texId;
    public:
        GameMainButton(QWidget *parent = NULL);
        ~GameMainButton();
        int getTexId();
        void setTexId(int texId);
        QPixmap* sprite;
    // paint event
        virtual void paintEvent(QPaintEvent *event) override;
    // mouse events
        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
    signals:
        void LMBpressed();
        void LMBreleased();
};
#endif
