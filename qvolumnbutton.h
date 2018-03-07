#ifndef QVOLUMEBUTTON_H
#define QVOLUMEBUTTON_H

#include <QToolButton>
#include <QBoxLayout>
#include <QWidgetAction>

QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)

class QVolumeButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    QVolumeButton(QWidget *parent = 0);

    int volume() const;

public slots:
    void increaseVolume();
    void descreaseVolume();
    void setVolume(int volume);
    void stylize();

signals:
    void volumeChanged(int volume);

private:
    QMenu *menu;
    QLabel *label;
    QSlider *slider;
};

#endif // QVOLUMEBUTTON_H
