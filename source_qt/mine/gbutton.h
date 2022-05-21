#ifndef GBUTTON_H
#define GBUTTON_H
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
// game buttons
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
class ThemeButton : public QPushButton {
        Q_OBJECT;
        int texId;
    public:
        ThemeButton(QWidget *parent = NULL);
        ~ThemeButton();
        int getTexId();
        void setTexId(int texId);
        int changeTheme(QPixmap* spr1, QPixmap* spr2, QPixmap* spr3, int themeId);
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
