/* 
 * File:   AboutProgram.h
 * Author: Aleksey
 *
 * Created on 25 Май 2013 г., 20:23
 */

#ifndef _ABOUTPROGRAM_H
#define	_ABOUTPROGRAM_H

#include "ui_AboutProgram.h"

class AboutProgram : public QDialog {
    Q_OBJECT
public:
    AboutProgram();
    virtual ~AboutProgram();
private:
    Ui::AboutProgram widget;
};

#endif	/* _ABOUTPROGRAM_H */
