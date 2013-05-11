/* 
 * File:   MainWindow.h
 * Author: Aleksey
 *
 * Created on 11 Май 2013 г., 23:22
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
    
    Q_OBJECT
    
    public:
        MainWindow();
        virtual ~MainWindow();

    private:
        Ui::MainWindow widget;
    
};

#endif	/* _MAINWINDOW_H */
