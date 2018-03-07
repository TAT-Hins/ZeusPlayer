#include "qvolumnbutton.h"
#include <QtWinExtras>
#include <QLabel>
#include <QMenu>
#include <QSlider>
#include <QStyle>

QVolumeButton::QVolumeButton(QWidget *parent) :
    QToolButton(parent), menu(0), label(0), slider(0)
{
    setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    setStyleSheet("border-style: flat;");
    setPopupMode(QToolButton::InstantPopup);

    QWidget *popup = new QWidget(this);

    slider = new QSlider(Qt::Horizontal, popup);
    slider->setRange(0, 100);
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));

    label = new QLabel(popup);
    label->setAlignment(Qt::AlignCenter);
    label->setNum(100);
    label->setMinimumWidth(label->sizeHint().width());
    connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));

    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(slider);
    popupLayout->addWidget(label);

    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);

    stylize();
}

void QVolumeButton::increaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepAdd);
}

void QVolumeButton::descreaseVolume()
{
    slider->triggerAction(QSlider::SliderPageStepSub);
}

int QVolumeButton::volume() const
{
    return slider->value();
}

void QVolumeButton::setVolume(int volume)
{
    slider->setValue(volume);
}

void QVolumeButton::stylize()
{
    if (QtWin::isCompositionEnabled()) {
        QtWin::enableBlurBehindWindow(menu);
        QString css("QMenu { border: 1px solid %1; border-radius: 2px; background: transparent; }");
        menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
    } else {
        QtWin::disableBlurBehindWindow(menu);
        QString css("QMenu { border: 1px solid black; background: %1; }");
        menu->setStyleSheet(css.arg(QtWin::realColorizationColor().name()));
    }
}
