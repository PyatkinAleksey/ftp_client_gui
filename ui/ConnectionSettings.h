/* 
 * File:   ConnectionSettings.h
 * Author: Aleksey Pyatkin
 *
 * Created on 12.05.2013, 0:17
 */

#ifndef _CONNECTIONSETTINGS_H
#define	_CONNECTIONSETTINGS_H

#include "../Options.h"
#include "ui_ConnectionSettings.h"

using namespace std;

class ConnectionSettings : public QDialog {
    
    Q_OBJECT

    public:
        ConnectionSettings();
        virtual ~ConnectionSettings();
        void getValues();
        
    private slots:
        void accept();

    private:
        Options options;
        Ui::ConnectionSettings widget;

};

#endif	/* _CONNECTIONSETTINGS_H */
